#ifndef MAIN_PROC_H_INCLUDED
#define MAIN_PROC_H_INCLUDED

#include <iostream>
#include <cmath>

#include "stack.h"
#include "constants.h"
#include "onegin.h"

#ifndef STACK_CONSTRUCT
#define STACK_CONSTRUCT(name) stack_construct(name, #name)
#endif

enum commands
{
    #define DEF(name, elements, code) name,

    #include "proc_commands.h"

    #undef DEF
};

enum str_to_i
{
    #define STR_COMMANDS(str, name) str,

    #include "string_define.h"

    #undef STR_COMMANDS
};
enum errors
{
    OK = 0,
    BAD_INPUT_DATA,
    EXTRA_ARG,
    NO_ARGS
};

struct cpu_struct
{
    stack_t cpu_stack;
    stack_t func_stack;
    elem_t reg_a;
    elem_t reg_b;
    elem_t reg_c;
    elem_t reg_d;
    elem_t RAM[RAM_LENGTH] = {};             //alloc 1mb array to ram
    cpu_struct(): reg_a(0),
                  reg_b(0),
                  reg_c(0),
                  reg_d(0)
        {
            STACK_CONSTRUCT(&cpu_stack);
            STACK_CONSTRUCT(&func_stack);
        }
};


void unit_tests();

int split_line(pointer_on_line pointer, char *&cmd_name, elem_t &arg, char* jump_name);
int make_binary_file                   (const char* input_name = INPUT_FILE,
                                        const char* assembler = ASSEMBLER_FILE);
int disassembler                       (const char* disasm_file = DISASSEMBLER_FILE,
                                        const char* assembler_file = ASSEMBLER_FILE);
int bin_to_txt                         (const char* assembler_file, char* &result_txt);

int CPU (cpu_struct *processor,         const char* result_file = OUTPUT_FILE,
                                        const char* binary_file = ASSEMBLER_FILE);
int my_stoi(char* str);

const char* my_itos(int c);

int realloc_buffer(int* size_buf, char** asm_text, int writed, int resize_b);

#endif // MAIN_PROC_H_INCLUDED
