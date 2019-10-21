#include "main_proc.h"

void test_line_split()
{
    char* test_string1 = "command1 12";
    char cmd_name[S_LENGTH] = {0};
    elem_t arg = 0;

    pointer_on_line pointer = {};
    pointer.start = test_string1;
    pointer.end = test_string1 + 11;
    char label[S_LENGTH] = {};
    split_line(pointer, cmd_name, arg, label);

    bool is_ok = true;
    if (strcmp("command1", cmd_name) != 0 || arg != 12)
    {
        printf("test failed");
        is_ok = false;
    }

    char* test_string2 = "PUSH DX";
    pointer.start = test_string2;
    pointer.end = test_string2 + 7;
    char cmd_name1[S_LENGTH] = {0};
    split_line(pointer, cmd_name1, arg, label);

    if (strcmp("S_PUSH", cmd_name1) != 0 || arg != stoi(test_string2 + 5))
    {
        is_ok = false;
        printf("test failed");
    }
    if (is_ok)
        printf("test passed\n");

}

void test_disassembler()
{
    make_binary_file("test_disasm.txt");
    disassembler("out_disasm.txt");


}

void unit_tests()
{
    test_line_split();
//    test_disassembler();
}
