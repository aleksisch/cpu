#include "main_proc.h"
#include "onegin.h"
#include <cstdlib>
#include <string>

struct labels
{
    int num;
    char name[S_LENGTH];
};
int make_binary_file(const char* input_name, const char* assembler)
{
    int size = 0, countline = 0;
    pointer_on_line* lineptr = nullptr;
    char* text = nullptr;
    work_file(&size, &lineptr, &text, input_name, &countline);

    int size_buf   = countline + sizeof(elem_t);

    char* asm_text = (char*) calloc(size_buf, sizeof(char));

    int writed = 0;

    labels labels_arr[LABELS_LENGTH] = {};
    labels jump_bytes[LABELS_LENGTH] = {};
    int jump_num = 0;
    int num_labels = 0;

    for (int line = 0; line < countline; line++)
    {
        char* cmd_name = (char*) calloc(S_LENGTH, sizeof(char));
        char* jump_name = (char*) calloc(S_LENGTH, sizeof(char));

        elem_t arg = 0;

        split_line(lineptr[line], cmd_name, arg, jump_name);
        printf("%s %d %s\n", cmd_name, arg, jump_name);
        if (writed * 2  > size_buf)
        {
            size_buf += countline + sizeof(elem_t);
            asm_text = (char*) realloc(asm_text, size_buf);
        }

        if (cmd_name[0] == ':')
        {
            bool flag = true;
            for (int i = 0; i < LABELS_LENGTH; i++)
            {
                if (strcmp(cmd_name+1, labels_arr[i].name) == 0)
                {
                    labels_arr[i].num = writed;
                    flag = false;
                }
            }
            if (flag && ++num_labels < 8)
            {
                labels_arr[num_labels].num = writed;
                strcpy(labels_arr[num_labels].name, cmd_name+1);
            }
        }

        #define DEF(str_name, elements, code)                       \
        else if (strcmp(cmd_name, #str_name) == 0)                  \
        {                                                           \
            asm_text[writed++] = (char) str_name;                   \
            if (elements == 1)                                      \
            {                                                       \
                elem_t* ptr = (elem_t*) (asm_text + writed);        \
                *ptr = arg;                                         \
                writed += sizeof(elem_t);                           \
            }                                                       \
        }

        #include "proc_commands.h"

        #undef DEF

        #define DEF(str_name, elements, code)                                      \
        else if (strcmp(cmd_name, "S_" #str_name) == 0)                            \
        {                                                                          \
            asm_text[writed++] = (char) str_name;                                  \
            jump_bytes[jump_num].num = writed;                                     \
            strcpy(jump_bytes[jump_num++].name, jump_name);                        \
            writed += sizeof(elem_t);                                              \
        }                                                                          // only for label

        #include "proc_commands.h"

        #undef DEF

        else
            printf("BAD COMMAND %s, skipped it line is %d\n", cmd_name, line);
    }

    for (int i = 0; i < jump_num; i++)

        for (int l = 0; l < LABELS_LENGTH; l++)

            if (strcmp(jump_bytes[i].name, labels_arr[l].name) == 0)

                *((elem_t*) (asm_text + jump_bytes[i].num)) = (elem_t) labels_arr[l].num;

    FILE *asm_file = fopen(assembler, "w+b");
    if (asm_file == nullptr)
        return 1;

    fwrite(asm_text, sizeof(char), writed, asm_file);
    free(asm_text);
    fclose(asm_file);
}

int disassembler(const char* disasm_file, const char* assembler_file)
{
    char* result_txt = nullptr;

    bin_to_txt(assembler_file, result_txt);

    FILE *output_file = fopen(disasm_file, "w");

    if (output_file == nullptr)
        return 1;

    fprintf(output_file, result_txt);

    fclose(output_file);

    free(result_txt);
}

int split_line(pointer_on_line pointer, char *&cmd_name, elem_t &arg, char* jump_name)
{
    char* cur_txt = pointer.start;
    int readed = 0;
    int tmp1 = 0;
    char tmp_char[S_LENGTH] = {};

    sscanf(cur_txt, "%s %n", cmd_name, &readed);

    if (sscanf(cur_txt + readed, CONST_FOR_ELEM_T" %n", &arg, &tmp1) == 0)
    {
        char arg_s[255] = {0};
        cmd_name[1] = 'S';
        cmd_name[2] = '_';
        sscanf(cur_txt, "%s %n", cmd_name + 3, &readed);
        cmd_name++;
        if (sscanf(cur_txt + readed, "%s %n", arg_s, &tmp1) == 0)
            return NO_ARGS;
        if (arg_s[0] == ';')                            //ignore text after ";"
            cmd_name += 2;
        else if (arg_s[0] == '[')                       //check is this RAM cmd
        {
            if (sscanf(arg_s + 1, "%d", &arg) == 0)
                cmd_name--;
            cmd_name[0] = 'R';
        }
        else
        {
            arg = my_stoi(arg_s);
            strcpy(jump_name, arg_s);
        }
    }

    if (sscanf(cur_txt + readed + tmp1, "%s", tmp_char) == 1 && tmp_char[0] != ';')
        return EXTRA_ARG;
    return OK;

}

int bin_to_txt(const char* assembler_file, char* &result_txt)
{
    int readed = 0;

    int size_asm = 0;
    char *assembler  = (char*) readFile (assembler_file, &size_asm, "r+b");
    int size_buf = size_asm;
    result_txt = (char*) calloc(size_buf, sizeof(char));
    int i = 0;
    int writed = 0;
    #define DEF(name, elements, code)                                   \
    else if ((int) assembler[readed] == name)                           \
    {                                                                   \
        int cur_write = 0;                                              \
        readed++;                                                       \
        sprintf(result_txt + writed, "%s%n", #name, &cur_write);        \
        writed += cur_write;                                            \
        elem_t* tmp = (elem_t*) (assembler + readed);                   \
        elem_t next = *tmp;                                             \
        char cmd_name[S_LENGTH] = #name;                                \
        int num_el = elements;                                          \
        if (strcmp("S_JMP", cmd_name) == 0)                            \
            ;                                                           \
        else if (cmd_name[0] == 'S' && cmd_name[1] == '_' ||            \
                 cmd_name[1] == 'S' && cmd_name[2] == '_')              \
        {                                                               \
            cur_write = 0;                                              \
            sprintf(result_txt + writed, " %s%n", my_itos(next), &cur_write);  \
            readed += sizeof(elem_t);                                   \
            writed += cur_write;                                        \
            num_el--;                                                   \
        }                                                               \
        for (;num_el != 0; num_el--)                                    \
        {                                                               \
            sprintf(result_txt + writed, " "CONST_FOR_ELEM_T"%n",       \
                    *((elem_t*) (assembler+readed)), &cur_write);       \
            writed += cur_write;                                        \
            readed += sizeof(elem_t);                                   \
        }                                                               \
        sprintf(result_txt + writed++, "\n");                             \
    }
    while (readed < size_asm)
    {
        if (writed*2 > size_buf)
        {
            int temp = size_buf;
            size_buf += size_asm + 100;
            result_txt = (char*) realloc(result_txt, size_buf * sizeof(char));
            memset(result_txt + temp, 0, size_buf - temp);
        }
        if (0) ;

        #include "proc_commands.h"

        else
        {
            printf("ERROR elem in asm file: " CONST_FOR_ELEM_T " iter %d\n", *((elem_t*) (assembler+readed)), i);
            return 1;
        }
    }
    #undef DEF
    free(assembler);
}

int my_stoi(char* str)
{
    #define STR_COMMANDS(str1, name_reg) if (strcmp(str, #str1) == 0) return str1;

    #include "string_define.h"

    #undef STR_COMMANDS

    printf("%s unknow in stoi\n", str);
    return -1;
}

char* my_itos(int c)
{
    #define STR_COMMANDS(str1, name_reg) if (str1 == c) return #str1;

    #include "string_define.h"

    #undef STR_COMMANDS

    return 0;
}
