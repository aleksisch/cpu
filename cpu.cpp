#include "main_proc.h"
#include "onegin.h"

int CPU(cpu_struct *processor, const char* binary_file, const char* result_file)
{
    int size = 0;
    int *elem = (int*) readFile (binary_file, &size, "r+b");
    size /= 4;

    FILE *output_file = fopen(result_file, "w");
    if (output_file == nullptr)
        return 1;
    int counter = 0;

    #define DEF(name, num, elements, code)  \
    else if (num == elem[counter])          \
    {                                       \
        code                                \
        counter++;                          \
    }

    while (counter < size)
    {
        if (0);

        #include "proc_commands.h"
        else printf("ERROR in command number %d", elem[counter++]);
    }
    #undef DEF
    int result = 0;
    stack_pop(&processor->cpu_stack, &result);
    fprintf(output_file, "%d", result);
}
