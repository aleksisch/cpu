#include "main_proc.h"
#include "onegin.h"

int CPU(cpu_struct *processor, const char* binary_cmd,
                               const char* binary_arg,
                               const char* result_file)
{
    int size_cmd = 0;
    int size_arg = 0;

    char   *asm_commands  = (char*)   readFile (binary_cmd, &size_cmd, "r+b");
    elem_t *asm_arguments = (elem_t*) readFile (binary_arg, &size_arg, "r+b");

    size_arg /= sizeof(elem_t);

    int counter_cmd = 0;
    int counter_arg = 0;

    #define DEF(name, elements, code)            \
    else if (name == asm_commands[counter_cmd])  \
    {                                            \
        code                                     \
    }

    while (counter_cmd < size_cmd)
    {
        if (0);

        #include "proc_commands.h"
        else printf("ERROR in command number %d", asm_commands[counter_cmd]);
        counter_cmd++;
    }
    #undef DEF
    elem_t result = 0;
    stack_pop(&processor->cpu_stack, &result);

    FILE *output_file = fopen(result_file, "w");
    if (output_file == nullptr)
        return 1;

    fprintf(output_file, CONST_FOR_ELEM_T, result);
    fclose(output_file);
}
