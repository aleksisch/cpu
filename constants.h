#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED
static const char* INPUT_FILE        = "input.txt";
static const char* ASSEMBLER_FILE     = "assembler.bin";
static const char* OUTPUT_FILE       = "output.txt";
static const char* DISASSEMBLER_FILE = "disassembler.txt";
static int S_LENGTH            = 255;                //maximum string length
static int AVG_COMMAND         = 3;                  //average argument in command

#define CONST_FOR_ELEM_T "%lf"
typedef double elem_t;                                  //set default stack type

const int STD_LENGTH_STACK     = 20;                     //default stack length
const int POISON_BYTE          = 127;                    //poison for memset
const int POISON_STACK         = 2354686532;             //canary in stack

#endif // CONSTANTS_H_INCLUDED
