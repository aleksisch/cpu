#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED
static char* INPUT_FILE        = "input.txt";
static char* ASSEMBLER_FILE    = "assembler.bin";
static char* OUTPUT_FILE       = "output.txt";
static char* DISASSEMBLER_FILE = "disassemble.txt";

enum commands
{
    #define DEF(name,num,elements,code) CMD_##name = num,
    #include "proc_commands.h"
};

struct cpu_struct
{
    stack_t cpu_stack;
    int reg_a;
    int reg_b;
    int reg_c;
    int reg_d;
    cpu_struct(): reg_a(0),
                  reg_b(0),
                  reg_c(0),
                  reg_d(0)
        {
            STACK_CONSTRUCT(&cpu_stack);
        }
};

#endif // CONSTANTS_H_INCLUDED
