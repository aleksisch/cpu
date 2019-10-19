#include "main_proc.h"
#include "onegin.h"
#include <string>
#include <iostream>
int make_binary_file(const char* input_name, const char* binary_file)
{
    int size = 0, countline = 0;
    pointer_on_line* lineptr = nullptr;
    char* text = "";
    work_file(&size, &lineptr, &text, input_name, &countline);

    int* asm_command = (int*) calloc((AVG_COMMAND+1)*countline, sizeof(int));
    int writed_el = 0;

    #define DEF(name, num, elements, code)                   \
    else if (strcmp(cmd_name, #name) == 0)                   \
    {                                                        \
        asm_command[writed_el++] = num;                      \
        for (int read = 0; read < count_cmd; read++)         \
            asm_command[writed_el++] = cmd_array[read];      \
    }
    for (int line = 0; line < countline; line++)
    {
        int* cmd_array = nullptr;
        char* cmd_name = nullptr;
        int  count_cmd = 0;
        split_line(lineptr[line], cmd_name, cmd_array, &count_cmd);
        if (0) ;

        #include "proc_commands.h"

        else
            printf("BAD COMMAND %s, skipped it", cmd_name);
    }
    #undef DEF

    FILE *output_file = fopen(binary_file, "w+b");
    if (output_file == nullptr)
        return 1;
    fwrite(asm_command, sizeof(int), writed_el, output_file);
    fclose(output_file);
}

int disassembler(const char* asm_file, const char* disasm_file)
{
    int size = 0;
    int *elem = (int*) readFile (asm_file, &size, "r+b");
    FILE *output_file = fopen(disasm_file, "w");

    if (output_file == nullptr)
        return 1;

    size /= 4;
    int cur_str_size = 5*size;
    char* result_string = (char*) calloc(5*cur_str_size, sizeof(char));
    int i = 0;
    int writed_c = 0;


    #define DEF(name, num, elements, code)                                    \
    else if (elem[i] == num)                                                  \
    {                                                                         \
        int cur_read = 0;                                                     \
        sprintf(result_string + writed_c, "%s %n", #name, &cur_read);         \
        writed_c += cur_read;                                                 \
        i++;                                                                  \
        int num_el = elements;                                                \
        for (; num_el != 0; num_el--)                                         \
        {                                                                     \
            sprintf(result_string + writed_c, "%d %n", elem[i++], &cur_read); \
            writed_c += cur_read;                                             \
        }                                                                     \
        sprintf(result_string + writed_c, "\n");                              \
        writed_c += 1;                                                        \
    }
    while (i < size)
    {
        if (writed_c*2 > cur_str_size)
        {
            cur_str_size*=2;
            result_string = (char*) realloc(result_string, cur_str_size);
        }
        if (0) ;

        #include "proc_commands.h"

        else
        {
            printf("ERROR elem: %d iter %d\n", elem[i], i);
            fclose(output_file);
            return 1;
        }
    }
    #undef DEF
    fprintf(output_file, result_string);
    fclose(output_file);
}

int split_line(pointer_on_line pointer, char *&cmd_name, int *&cmd_array, int *count_number)
{
    char* cur_txt = pointer.start;
    cmd_name  = (char*) calloc (S_LENGTH,   sizeof(char));
    cmd_array = (int*) calloc (AVG_COMMAND, sizeof(int));
    int readed = 0;
    int writed = 0;
    int num = 0;
    *count_number = 0;
    while (sscanf(cur_txt + readed, "%d", &num) == 0 && cur_txt + readed < pointer.end)
    {
        sscanf(cur_txt + readed, "%s%n", cmd_name+writed, &num);
        readed += num + 1;
        writed += num;
    }

    while (sscanf(cur_txt + readed, "%d %n", cmd_array+*count_number, &num) == 1 &&
                  cur_txt + readed < pointer.end)
    {
        readed += num;
        (*count_number)++;
        if (*count_number%AVG_COMMAND == 0)
            cmd_array = (int*) realloc(cmd_array, (*count_number + AVG_COMMAND) * sizeof(int));
    }
}
