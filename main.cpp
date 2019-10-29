#include "main_proc.h"

int main()
{
    unit_tests();
    make_binary_file();
    disassembler();
    cpu_struct proc;
    STACK_CONSTRUCT(&(proc.cpu_stack));
    STACK_CONSTRUCT(&(proc.func_stack));
    CPU(&proc);
    system("pause");
}


