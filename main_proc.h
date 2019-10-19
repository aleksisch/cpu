#ifndef MAIN_PROC_H_INCLUDED
#define MAIN_PROC_H_INCLUDED

#include <iostream>

#include "stack.h"
#include "constants.h"
#include "onegin.h"

void unit_tests();

int split_line(pointer_on_line pointer, char *&cmd_name, int *&cmd_array, int *count_number);

int make_binary_file(const char* input_name = INPUT_FILE,
                     const char* binary_file = ASSEMBLER_FILE);

int disassembler(const char* asm_file = ASSEMBLER_FILE,
                 const char* disasm_file = DISASSEMBLER_FILE);

int get_array_commands(char* text, pointer_on_line* lineptr, int size, int countline,
                       char* array_commands, int** array_int);

int read_command_file(int** command_array, int *size, char* binary_file);

int CPU(cpu_struct *processor, const char* binary_file = ASSEMBLER_FILE,
                               const char* result_file = OUTPUT_FILE);

#endif // MAIN_PROC_H_INCLUDED
