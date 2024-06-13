/*BF 编译器 -- copied from GLM4*/
#include <stdio.h>
#include <stdlib.h>

// 词法分析器
void lexer(const char * bfcode, char ** tokens, int * num_tokens)
{
    *num_tokens = 0;
    for (int i = 0; bfcode[i]; i++)
    {
        switch (bfcode[i])
        {
            case '>':
            case '<':
            case '+':
            case '-':
            case '.':
            case ',':
            case '[':
            case ']':
                tokens[*num_tokens] = (char *)&bfcode[i];
                (*num_tokens)++;
            default:    break;
            
        }
    }
}

// 语法分析器和代码生成器
void parser_and_codegen(FILE * _File, char ** tokens, int num_tokens)
{
    fprintf(_File, "#include <stdio.h>\n"
                "int main()\n{\n"
                "   char tape[30000] = {0};\n"
                "   char *ptr = tape;\n");
    
    for (int i = 0; i < num_tokens; i++)
    {
        switch (tokens[i][0])
        {
            case '>':
                fprintf(_File, "    ptr++;\n"); break;
            case '<':
                fprintf(_File, "    ptr--;\n"); break;
            case '+':
                fprintf(_File, "    (*ptr)++;\n"); break;
            case '-':
                fprintf(_File, "    (*ptr)--;\n"); break;
            case '.':
                fprintf(_File, "    putchar(*ptr);\n"); break;
            case ',':
                fprintf(_File, "    *ptr = getchar();\n"); break;
            case '[':
                fprintf(_File, "    while (*ptr)\n{\n"); break;
            case ']':
                fprintf(_File, "    }\n"); break;
            default : break;
        }
    }

    fprintf(_File, "    return 0;\n}\n");
}

int main(int argc, char const * argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: bfc <file.bf>\n");
        return 1;
    }

    // 读取BF文件
    FILE * bf_file = fopen(argv[1], "r");
    if (!bf_file)
    {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    // 获取文件大小
    fseek(bf_file, 0, SEEK_END);
    long bf_size = ftell(bf_file);
    rewind(bf_file);

    // 读取文件内容
    char * bf_code = (char *) malloc(bf_size + 1);
    fread(bf_code, 1, bf_size, bf_file);
    fclose(bf_file);
    bf_code[bf_size] = '\0';

    // 词法分析
    char ** tokens = (char **) malloc(bf_size * sizeof (char *));
    int num_tokens = 0;
    lexer(bf_code, tokens, &num_tokens);

    // 生成输出文件
    FILE * out = fopen("a.c", "w");

    // 语法分析与代码生成
    parser_and_codegen(out, tokens, num_tokens);

    fclose(out);

    // 释放内存
    free(bf_code);
    free(tokens);

    return 0;
}