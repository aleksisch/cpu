#ifndef MAIN_PROC_H_INCLUDED
#define MAIN_PROC_H_INCLUDED

#include <stdio.h>
#include <iostream>

#include "stack.h"
#include "constants.h"
#include "onegin.h"

int make_binary_file(char* input_name = INPUT_FILE, char* binary_file = ASSEMBLER_FILE);

int disassembler(char* asm_file = ASSEMBLER_FILE, char* disasm_file = DISASSEMBLER_FILE);

int get_array_commands(char* text, pointer* lineptr, int size, int countline,  char* array_commands, int** array_int);

int read_command_file(int** command_array, int *size, char* binary_file);

int CPU(cpu_struct *processor, char* binary_file = ASSEMBLER_FILE, char* result_file = OUTPUT_FILE);

#endif // MAIN_PROC_H_INCLUDED
