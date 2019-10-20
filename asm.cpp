#include "main_proc.h"
#include "onegin.h"

int make_binary_file(const char* input_name, const char* assembler_cmd, const char* assembler_arg)
{
    int size = 0, countline = 0;
    pointer_on_line* lineptr = nullptr;
    char* text = nullptr;
    work_file(&size, &lineptr, &text, input_name, &countline);

    char*   asm_commands = (char*)     calloc(countline, sizeof(char));
    elem_t* asm_arguments = (elem_t*) calloc(countline, sizeof(elem_t));

    int size_buf   = countline;
    int writed_cmd = 0;
    int writed_arg = 0;

    #define DEF(name, elements, code)                           \
    else if (strcmp(cmd_name, #name) == 0)                      \
    {                                                           \
        asm_commands[writed_cmd++] = (char) name;               \
        for (int read = 0; read < elements; read++)             \
            asm_arguments[writed_arg++] = cmd_array[read];      \
    }
    for (int line = 0; line < countline; line++)
    {
        char cmd_name[S_LENGTH] = "";
        elem_t* cmd_array = (elem_t*) calloc (AVG_COMMAND, sizeof(elem_t));
        int   count_cmd = 0;
        split_line(lineptr[line], cmd_name, cmd_array, &count_cmd);

        if (writed_arg / 2  > size_buf)
        {
            size_buf *= 2;
            asm_arguments = (elem_t*) realloc(asm_arguments, size_buf);
        }
        if (0) ;

        #include "proc_commands.h"
        else
            printf("BAD COMMAND %s, skipped it\n", cmd_name);
        free(cmd_array);
    }
    #undef DEF
    FILE *cmd_file = fopen(assembler_cmd, "w+b");
    FILE *arg_file = fopen(assembler_arg, "w+b");
    if (cmd_file == nullptr || arg_file == nullptr)
        return 1;
    fwrite(asm_arguments, sizeof(elem_t), writed_arg, arg_file);
    fwrite(asm_commands,  sizeof(char), writed_cmd, cmd_file);

    free(asm_commands);
    free(asm_arguments);

    fclose(arg_file);
    fclose(cmd_file);
}

int disassembler(const char* assembler_cmd, const char* assembler_arg, const char* disasm_file)
{
    char* result_txt = nullptr;
    bin_to_txt(assembler_cmd, assembler_arg, result_txt);

    FILE *output_file = fopen(disasm_file, "w");

    if (output_file == nullptr)
        return 1;

    fprintf(output_file, result_txt);

    fclose(output_file);

    free(result_txt);
}

int split_line(pointer_on_line pointer, char *cmd_name, elem_t *&cmd_array, int *count_number)
{
    char* cur_txt = pointer.start;
    int readed = 0;
    int writed = 0;
    int num = 0;
    elem_t temp_var = 0;
    *count_number = 0;
    while (sscanf(cur_txt + readed, CONST_FOR_ELEM_T,  &temp_var) == 0 && cur_txt + readed < pointer.end)
    {
        sscanf(cur_txt + readed, "%s%n", cmd_name+writed, &num);
        readed += num + 1;
        writed += num;
    }
    while (sscanf(cur_txt + readed, CONST_FOR_ELEM_T " %n", cmd_array+*count_number, &num) == 1 &&
                  cur_txt + readed < pointer.end)
    {
        readed += num;
        (*count_number)++;
        if ((*count_number)%AVG_COMMAND == 0)
            cmd_array = (elem_t*) realloc(cmd_array, (*count_number + AVG_COMMAND) * sizeof(elem_t));
    }
}

int bin_to_txt(const char* assembler_cmd, const char* assembler_arg, char* &result_txt)
{
    int size_cmd = 0;
    int size_arg = 0;

    char   *asm_commands  = (char*)   readFile (assembler_cmd, &size_cmd, "r+b");
    elem_t *asm_arguments = (elem_t*) readFile (assembler_arg, &size_arg, "r+b");

    size_arg /= sizeof(elem_t);
    int cur_str_size = size_cmd + size_arg;
    result_txt = (char*) calloc(cur_str_size, sizeof(char));

    int i = 0;
    int writed_c   = 0;
    int writed_arg = 0;
    #define DEF(name, elements, code)                               \
    else if ((int) asm_commands[i] == name)                         \
    {                                                               \
        int cur_read = 0;                                           \
        sprintf(result_txt + writed_c, "%s %n", #name, &cur_read);  \
        writed_c += cur_read;                                       \
        int num_el = elements;                                      \
        for (;num_el != 0; num_el--)                                \
        {                                                           \
            sprintf(result_txt + writed_c, CONST_FOR_ELEM_T " %n",  \
                    asm_arguments[writed_arg++], &cur_read);        \
            writed_c += cur_read;                                   \
        }                                                           \
        sprintf(result_txt + writed_c, "\n");                       \
        writed_c += 1;                                              \
    }
    while (i < size_cmd)
    {
        if (writed_c*2 > cur_str_size)
        {
            cur_str_size*=2;
            result_txt = (char*) realloc(result_txt, cur_str_size);
        }

        if (0) ;

        #include "proc_commands.h"

        else
        {
            printf("ERROR elem: " CONST_FOR_ELEM_T " iter %d\n", asm_commands[i], i);
            return 1;
        }
        i++;
    }
    #undef DEF
    free(asm_commands);
    free(asm_arguments);
}
