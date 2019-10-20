#include "main_proc.h"

void test_line_split()
{
    char* test_string1 = "command1 command2 command3 command4 12 456 789";
    char* cmd_name = {};
    elem_t* cmd_array = {};
    int count = 0;

    pointer_on_line pointer = {};
    pointer.start = test_string1;
    pointer.end = test_string1 + 46;

    split_line(pointer, cmd_name, cmd_array, &count);
    if (strcmp("command1command2command3command4", cmd_name) != 0)
        printf("test failed");

    if (cmd_array[0] != 12 || cmd_array[1] != 456 || cmd_array[2] != 789)
        printf("test failed");
    char* test_string2 = "PUSH AX 12 456 789";
    pointer.start = test_string2;
    pointer.end = test_string2 + 18;
    split_line(pointer, cmd_name, cmd_array, &count);
    if (strcmp("PUSHAX", cmd_name) != 0)
        printf("test failed");
    if (cmd_array[0] != 12 || cmd_array[1] != 456 || cmd_array[2] != 789)
        printf("test failed");
}


void unit_tests()
{
    test_line_split();
}
