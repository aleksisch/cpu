#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED
static char* INPUT_FILE        = "input.txt";
static char* ASSEMBLER_FILE    = "assembler.bin";
static char* OUTPUT_FILE       = "output.txt";
static char* DISASSEMBLER_FILE = "disassemble.txt";
static int S_LENGTH = 255;
enum commands
{
    #define DEF(name,num,elements,code) CMD_##name = num,
    #include "proc_commands.h"
};

enum errors
{
    OK = 0,
    BAD_INPUT_DATA,
};

struct cpu_struct
{
    stack_t cpu_stack;
    int reg_a;
    int reg_b;
    int reg_c;
    int reg_d;
    int last_register;      // if register free is true, else false
    cpu_struct(): reg_a(0),
                  reg_b(0),
                  reg_c(0),
                  reg_d(0)
        {
            STACK_CONSTRUCT(&cpu_stack);
        }
};

#endif // CONSTANTS_H_INCLUDED
