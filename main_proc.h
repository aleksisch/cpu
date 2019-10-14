#ifndef MAIN_PROC_H_INCLUDED
#define MAIN_PROC_H_INCLUDED

#include <stdio.h>
#include <iostream>

#include "stack.h"
#include "constants.h"

int make_binary_file(char* input_name = INPUT_FILE, char* binary_filename = ASSEMBLER_FILE);

int disassembler(char* asm_filename = ASSEMBLER_FILE, char* disasm_filename = DISASSEMBLER_FILE);

int read_command_file(int** command_array, int *size, char* binary_filename);

int CPU(char* binary_filename = ASSEMBLER_FILE, char* result_file = OUTPUT_FILE);

#endif // MAIN_PROC_H_INCLUDED
