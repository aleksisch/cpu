#include "main_proc.h"
#include "onegin.h"

elem_t* get_reg_num(int cmd, cpu_struct* processor)
{
    if (cmd == AX) return &(processor->reg_a);
    if (cmd == BX) return &(processor->reg_b);
    if (cmd == CX) return &(processor->reg_c);
    if (cmd == DX) return &(processor->reg_d);
}

int CPU(cpu_struct *processor, const char* result_file,
                               const char* binary_file)
{
    int size_bin = 0;

    char *asm_text  = (char*) readFile (binary_file, &size_bin, "r+b");

    int counter_byte = 0;
    #define DEF(name, elements, code)                   \
    else if (name == asm_text[counter_byte] &&          \
             elements == (int) asm_text[counter_byte + 1])  \
    {                                                   \
        counter_byte += 2;                              \
        code                                            \
    }
    int line = 0;
    while (counter_byte < size_bin)
    {
        line++;
        if (0);

        #include "proc_commands.h"
        else
        {
            printf("ERROR in command number %d %d\n", asm_text[counter_byte], line);
            counter_byte += 2;
        }
    }
    #undef DEF

    FILE *output_file = fopen(result_file, "w");
    if (output_file == nullptr)
        return 1;
    while( processor->cpu_stack.counter > 1)
    {
        elem_t result = 0;

        stack_pop(&processor->cpu_stack, &result);

        fprintf(output_file, CONST_FOR_ELEM_T, result);
    }
    fclose(output_file);
}
