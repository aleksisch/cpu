#ifndef MAIN_PROC_H_INCLUDED
#define MAIN_PROC_H_INCLUDED

#include <iostream>

#include "stack.h"
#include "constants.h"
#include "onegin.h"

#ifndef STACK_CONSTRUCT
#define STACK_CONSTRUCT(name) stack_construct(name, #name)
#endif

enum commands
{
    #define DEF(name,num,elements,code) CMD_##name = num,
    #include "proc_commands.h"
    #undef DEF
};

enum errors
{
    OK = 0,
    BAD_INPUT_DATA,
};

struct cpu_struct
{
    stack_t cpu_stack;
    elem_t reg_a;
    elem_t reg_b;
    elem_t reg_c;
    elem_t reg_d;
    cpu_struct(): reg_a(0),
                  reg_b(0),
                  reg_c(0),
                  reg_d(0)
        {
            STACK_CONSTRUCT(&cpu_stack);
        }
};


void unit_tests();

int split_line             (pointer_on_line pointer, char *cmd_name,
                            elem_t *&cmd_array, int *count_number);

int make_binary_file       (const char* input_name = INPUT_FILE,
                            const char* asm_cmd = ASSEMBLER_CMD,
                            const char* asm_arg = ASSEMBLER_ARG);

int disassembler           (const char* asm_cmd = ASSEMBLER_CMD,
                            const char* asm_arg = ASSEMBLER_ARG,
                            const char* disasm_file = DISASSEMBLER_FILE);
int bin_to_txt(const char* assembler_arg, const char* disasm_file, char* &result_txt);

int CPU                    (cpu_struct *processor, const char* binary_cmd = ASSEMBLER_CMD,
                                                   const char* binary_arg = ASSEMBLER_ARG,
                                                   const char* result_file = OUTPUT_FILE);
#endif // MAIN_PROC_H_INCLUDED
