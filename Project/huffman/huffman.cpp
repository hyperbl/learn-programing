#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

// Huffman树的节点结构
struct HuffmanNode
{
    char data;
    int freq;
    HuffmanNode * left, * right;

    HuffmanNode(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

// 用于比较Huffman节点频率的比较
struct Compare
{
    bool operator()(HuffmanNode * l, HuffmanNode * r)
    {
        return l->freq > r->freq;
    }
};

// Huffman编码的实现
class Huffman
{
    public:
        // 根据输入数据构建Huffman树
        HuffmanNode * buildHuffmanTree(vector<HuffmanNode*>& nodes)
        {
            priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
            for (auto node : nodes)
                pq.push(node);

            while (pq.size() != 1)
            {
                HuffmanNode *left = pq.top(); pq.pop();
                HuffmanNode *right = pq.top(); pq.pop();

                HuffmanNode *parent = new HuffmanNode('$', left->freq + right->freq);
                parent->left = left;
                parent->right = right;

                pq.push(parent);
            }

            return pq.top();
        }

        // 根据Huffman树生成编码
        void generateCodes(HuffmanNode *root, string str, unordered_map<char, string>& codes)
        {
            if (root == nullptr) return;

            if (root->data != '$')
                codes[root->data] = str;

            generateCodes(root->left, str + "0", codes);
            generateCodes(root->right, str + "1", codes);
        }

        // 编码数据
        string encode(string data, unordered_map<char, string>& codes)
        {
            string encodedData = "";
            for (char ch : data)
                encodedData += codes[ch];

            return encodedData;
        }

        // 解码数据
        string decode(HuffmanNode * root, string encodedData)
        {
            string decodedData = "";
            HuffmanNode * current = root;
            for (char bit : encodedData)
            {
                if (bit == '0')
                    current = current->left;
                else
                    current = current->right;

                if (current->data != '$')
                {
                    decodedData += current->data;
                    current = root;
                }
            }

            return decodedData;
        }
};

/* Here is a sample program. */
int main(int argc, char const * argv[])
{
    string data = "Huffman coding is a data compression algorithms.";
    unordered_map<char, int> freq;
    for (char ch : data)
        freq[ch]++;

    vector<HuffmanNode*> nodes;
    for (auto pair : freq)
        nodes.push_back(new HuffmanNode(pair.first, pair.second));

    Huffman huffman;
    HuffmanNode * root = huffman.buildHuffmanTree(nodes);
    unordered_map<char, string> codes;
    huffman.generateCodes(root, "", codes);

    string encodedData = huffman.encode(data, codes);
    cout << "Encoded Data: " << encodedData << endl;

    string decodedData = huffman.decode(root, encodedData);
    cout << "Decoded Data: " << decodedData << endl;

    return 0;
}