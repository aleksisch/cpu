#include "main_proc.h"

int make_binary_file(char* input_name, char* binary_filename)
{
    FILE *input_file = fopen (input_name, "r");
    if (input_file == nullptr)
        return 1;
    FILE *output_file = fopen(binary_filename, "w+b");
    if (output_file == nullptr)
        return 1;
/*
    fseek (input_file, 0L, SEEK_END);

    *size = (int) ftell(input_file);

    char *text = (char *) calloc(*size, sizeof(char));

    fseek (input_file, 0L, SEEK_SET);

    fread (text, sizeof(char), *size, fp);
*/
    while (true)
    {
        char str[10] = "";

        if (fscanf(input_file, "%s", str) <= 0)
            break;

        if (0) ;
        #define DEF(name, num, elements, code)\
        else if (strcmp(str, #name) == 0)\
        {\
            int elem = elements+1;\
            int temp[elem] = {0};\
            temp[0] = num;\
            for (int i = 1; i < elem; i++)\
                fscanf(input_file, "%d", temp+i);\
            fwrite(temp, sizeof(int), elem, output_file);\
        }

        #include "proc_commands.h"

        #undef DEF
        else
        {
            printf("BAD %s", str);
            return 1;
        }
    }
    fclose(input_file);
    fclose(output_file);
}

int disassembler(char* asm_filename, char* disasm_filename)
{
    FILE *input_file = fopen (asm_filename, "r+b");
    if (input_file == nullptr)
        return 1;
    FILE *output_file = fopen(disasm_filename, "w");
    if (output_file == nullptr)
        return 1;
    while (true)
    {
        int current_number = 0;
        if (fread(&current_number, sizeof(int), 1, input_file) != 1)
            break;
        if (0) ;
        #define DEF(name, num, elements, code)\
        else if (current_number == num)\
        {\
            int temp[elements];\
            fread(temp, sizeof(int), elements, input_file);\
            fprintf(output_file, "%s ", #name);\
            for (int i = 0; i < elements; i++)\
                fprintf(output_file, "%d ", temp[i]);\
            fprintf(output_file, "\n");\
        }

        #include "proc_commands.h"

        #undef DEF
        else
        {
            printf("ERROR");
            return 1;
        }
    }
    fclose(input_file);
    fclose(output_file);
    system("pause");
}
