#include "main_proc.h"

int CPU(char* binary_filename, char* result_file)
{
    int* command_array = nullptr;
    int size = 0;
    read_command_file(&command_array, &size, binary_filename);
    int counter = 0;
    printf("%d", command_array);
    while (size > counter)
    {
        #define DEF(name, num, elements, code) code
    }
}

int read_command_file(int** command_array, int *size, char* binary_filename)
{
    FILE *input_file = fopen (binary_filename, "r+b");

    if (input_file == nullptr)
        return 1;

    fseek (input_file, 0L, SEEK_END);

    *size = ((int) ftell(input_file)) / sizeof(int);

    *command_array = (int *) calloc(*size, sizeof(int));

    fseek (input_file, 0L, SEEK_SET);

    fread (*command_array, sizeof(int), *size, input_file);
}
