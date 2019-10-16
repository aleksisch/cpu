#include "main_proc.h"
#include "onegin.h"

int make_binary_file(char* input_name, char* binary_file)
{
    int size = 0, countline = 0;
    pointer* lineptr = nullptr;
    char* text = "";
    work_file(&size, &lineptr, &text, input_name, &countline);

    int* asm_command = (int*) calloc(2*countline, sizeof(int));
    int writed_el = 0;
    for (int line = 0; line < countline; line++)
    {
        int cur_num = 0;
        char cur_cmd[S_LENGTH];
        int readed = sscanf(lineptr[line].start, "%s %d", cur_cmd, &cur_num);
        if (readed < 1)
            break;
        if (0) ;
        #define DEF(name, num, elements, code)                   \
        else if (strcmp(cur_cmd, #name) == 0)                    \
        {                                                        \
            asm_command[writed_el++] = num;                      \
            if (readed == 2) asm_command[writed_el++] = cur_num; \
        }

        #include "proc_commands.h"

        #undef DEF

        else
        {
            printf("BAD COMMAND %s", cur_cmd);
            return 1;
        }
    }
    FILE *output_file = fopen(binary_file, "w+b");
    if (output_file == nullptr)
        return 1;
    fwrite(asm_command, sizeof(int), writed_el, output_file);
    fclose(output_file);
}

int disassembler(char* asm_file, char* disasm_file)
{
    int size = 0;
    int *elem = (int*) readFile (asm_file, &size, "r+b");
    FILE *output_file = fopen(disasm_file, "w");
    if (output_file == nullptr)
        return 1;
//    char* res_text = (char*) calloc(size, sizeof(char));

    size /= 4;
    int i = 0;
    while (i < size)
    {
        if (0) ;
        #define DEF(name, num, elements, code)                        \
        else if (elem[i] == num)                                      \
        {                                                             \
            fprintf(output_file, "%s ", #name);                       \
            i++;                                                      \
            if (elements != 0) fprintf(output_file, "%d", elem[i++]); \
            fprintf(output_file, "\n");                               \
        }

        #include "proc_commands.h"

        #undef DEF
        else
        {
            printf("ERROR elem: %d iter %d\n", elem[i], i);
            fclose(output_file);
            return 1;
        }
    }

    fclose(output_file);
}
