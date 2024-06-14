#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int uint;
typedef unsigned char uchar;

typedef struct HTNode
{
	uchar value;
	uint weight;
	struct HTNode * lchild;
	struct HTNode * rchild;
} HTNode;
typedef HTNode * HuffmanTree;

// 编码数据 
typedef struct CodePair
{
	uchar value;    // 源码
	char * code;   // 编码
} CodePair;
typedef CodePair * CodeTable;

typedef struct HeapStruct
{
	uint capacity;
	uint size;
	HuffmanTree * data;
} HeapStruct;
typedef HeapStruct * Heap;

/* 以下是关于heap的一些函数 */

Heap Heap_init(uint maxSize);
void Heap_push(Heap H, HuffmanTree HT); 
HuffmanTree Heap_top(Heap H);
void Heap_pop(Heap H);
void Heap_free(Heap H);

/* 以下是涉及huffman树的函数 */

HuffmanTree HuffmanTree_build(HTNode nodes[], int n);
  
void generateCodes(HuffmanTree HT, char * str, int strSize, CodeTable * codes, int n);

void encode(char * _Dst, char * _Src, CodeTable codes, int n);

void decode(char * _Dst, char * _Src, HuffmanTree HT, int n);

#define CODESIZE (128)
#define BUFSIZE (1000)
int main(int argc, char const * argv[])
{
	char data[] = "Huffman coding is a compression algorithm.";
	int strSize = strlen(data);
	int weights[CODESIZE] = {0};
	for (int i = 0; i < strSize; ++i)
		++weights[(int) data[i]];
	
	int n = 0;
	for (int i = 0; i < CODESIZE; ++i)
		if (weights[i])
			++n;
	HTNode * nodes = (HTNode *) malloc(sizeof (HTNode) * n);
	for (int i = 0, j = 0; i < CODESIZE; ++i)
		if (weights[i])
		{
			nodes[j].value = (uchar) i;
			nodes[j].weight = (uint) weights[i];
			nodes[j].lchild = nodes[j].rchild = NULL;
			j++;
		}

	HuffmanTree HT = HuffmanTree_build(nodes, n);
	CodeTable codes = (CodePair *) malloc(sizeof (CodePair) * n);
	char * encodedData = (char *) malloc(sizeof (char) * BUFSIZE);
	memset(encodedData, '\0', sizeof (char) * BUFSIZE);
	char * decodedData = (char *) malloc(sizeof (char) * BUFSIZE);
	memset(decodedData, 0, sizeof (char) * BUFSIZE);

	generateCodes(HT, "", 0, &codes, n);

	encode(encodedData, data, codes, n);
	puts(encodedData);

	decode(decodedData, encodedData, HT, n);
	puts(decodedData);

	free(decodedData);
	free(encodedData);
	free(nodes);
	free(codes);
	return 0;
}

HuffmanTree HuffmanTree_build(HTNode nodes[], int n)
{
	Heap H = Heap_init(n);
	HuffmanTree HT = NULL;
	if (H)
	{
		HuffmanTree left, right, newN;
		for (int i = 0; i < n; i++)
			Heap_push(H, &nodes[i]);
		while (H->size != 1)
		{
			left = Heap_top(H); Heap_pop(H);
			right = Heap_top(H); Heap_pop(H);
			newN = (HuffmanTree) malloc(sizeof (HTNode));
			newN->value = '\0';
			newN->weight = left->weight + right->weight;
			newN->lchild = left;
			newN->rchild = right;
			Heap_push(H, newN);
		}
		HT = Heap_top(H);
	}
	Heap_free(H);
	return HT;
}

void generateCodes(HuffmanTree HT, char * str, int strSize, CodeTable * codes, int n)
{
	static int i = 0;
	if (!strSize) i = 0;
	if (HT)
	{
		if (HT->value && i < n)
		{
			(*codes)[i].code = (char *) malloc(sizeof (char) * (strSize + 1));
			strcpy((*codes)[i].code, str);
			(*codes)[i++].value = HT->value;
		}

		char * newStr = (char *) malloc(sizeof (char) * (++strSize + 1));
		strcpy(newStr, str);
		newStr[strSize] = '\0';

		newStr[strSize - 1] = '0';
		generateCodes(HT->lchild, newStr, strSize, codes, n);
		
		newStr[strSize - 1] = '1';
		generateCodes(HT->rchild, newStr, strSize, codes, n);

		free(newStr);
	}
}

void encode(char * _Dst, char * _Src, CodeTable codes, int n)
{
	int i;
	for (char * ptr = _Src; *ptr; ptr++)
	{
		for (i = 0; i < n && codes[i].value != *ptr; i++);
		strcat(_Dst, codes[i].code);
	}
}

void decode(char * _Dst, char * _Src, HuffmanTree HT, int n)
{
	int i = 0;
	HuffmanTree cur = HT;
	for (char * ptr = _Src; *ptr; ptr++)
	{
		if (*ptr == '0')
			cur = cur->lchild;
		else
			cur = cur->rchild;

		if (cur->value)
		{
			_Dst[i++] = cur->value;
			cur = HT;
		}
	}
}

Heap Heap_init(uint maxSize)
{
	static HTNode zero = {'\0', 0, NULL, NULL};
	Heap H = NULL;
	if (maxSize > 0)
	{
		H = (Heap) malloc(sizeof (HeapStruct));
		H->capacity = maxSize;
		H->data = (HuffmanTree *) malloc((maxSize + 1) * sizeof (HuffmanTree));
		H->size = 0;
		for (int i = 0; i <= maxSize; i++)
			H->data[i] = &zero;
	}
	return H;
}

void Heap_push(Heap H, HuffmanTree HT)
{
	if (H->size < H->capacity)
	{
		uint child = ++H->size;
		while (H->data[child / 2]->weight > HT->weight)
		{
			H->data[child] = H->data[child / 2];
			child /= 2;
		}
		H->data[child] = HT;
	}
}

HuffmanTree Heap_top(Heap H)
{
	return H->data[1];
}

void Heap_pop(Heap H)
{
	if (H->size > 0)
	{
		HTNode * last;
		uint child = 1, i = 1;
		last = H->data[H->size--];
		for (i = 1; i * 2 <= H->size; i = child)
		{
			child = i * 2;
			if (child != H->size && H->data[child]->weight > H->data[child + 1]->weight)
				++child;
			
			if (H->data[child]->weight < last->weight)
				H->data[i] = H->data[child];
			else
				break;

		}
		H->data[i] = last;
	}
}

void Heap_free(Heap H)
{
	free(H->data);
	free(H);
}


