#include "main_proc.h"

void test_line_split()
{
    printf( "test 1\n");
    pointer_on_line test;
    char* t_push1 = "PUSH 12";
    test.start = t_push1;
    Commands cur_cmd1 = {};
    if (split_line(test, &cur_cmd1) != 0) printf("error != 0\n");

    if ( ((int) cur_cmd1.cmd_num) != PUSH) printf("err in cmd number push\n");

    if ( ((int) cur_cmd1.arg_num) != 12) printf("err in arg push\n");

    if ( ((int) cur_cmd1.type_arg) != ELEM_T) printf("err in type_arg push\n");

    printf( "test 2\n");
    char* t_push2 = "PUSH AX";
    test.start = t_push2;
    Commands cur_cmd2 = {};
    if (split_line(test, &cur_cmd2) != 0)
        printf("error != 0\n");

    if (cur_cmd2.cmd_num != PUSH)
        printf("err in cmd number push reg %d %d\n", PUSH, cur_cmd2.cmd_num);

    if (cur_cmd2.arg_num != AX)
        printf("err in arg push reg %d %d\n", AX, cur_cmd2.arg_num);

    if (cur_cmd2.type_arg != REG)
        printf("err in type_arg push reg %d %d\n", cur_cmd2.type_arg, REG);

    printf( "test 3\n");
    char* test_ram1 = "PUSH [12]";
    test.start = test_ram1;
    Commands cur_cmd3 = {};
    if (split_line(test, &cur_cmd3) != 0)
        printf("error != 0");

    if (cur_cmd3.cmd_num != PUSH)
        printf("err in cmd number push ram\n");

    if (cur_cmd3.arg_num != 12)
        printf("err in arg push ram\n");

    if (cur_cmd3.type_arg != RAM)
        printf("err in type_arg push ram %d %d\n", RAM | ELEM_T, cur_cmd3.type_arg);

    printf( "test 4\n");
    char* test_ram2 = "PUSH [AX]";
    test.start = test_ram2;
    Commands cur_cmd4 = {};
    if (split_line(test, &cur_cmd4) != 0)
        printf("error != 0\n");

    if (cur_cmd4.cmd_num != PUSH)
        printf("err in cmd number push ram reg\n");

    if (cur_cmd4.arg_num != AX)
        printf("err in arg push ram reg\n");

    if (cur_cmd4.type_arg !=  (RAM | REG))
        printf("111err in type_arg push ram reg %d %d\n", RAM | REG, cur_cmd4.type_arg);

    printf( "test 5\n");
    char* test_label1 = ":label";
    test.start = test_label1;
    Commands cur_cmd5 = {};
    if (split_line(test, &cur_cmd5) != 0)
        printf("error != 0\n");

    if (cur_cmd5.cmd_num != 0)
        printf("err in cmd number label\n");

    if (cur_cmd5.arg_num != 0)
        printf("err in arg label\n");

    if (cur_cmd5.type_arg != LABEL)
        printf("err in type_arg push label %d %d\n", LABEL, cur_cmd5.type_arg);

    if (strcmp(cur_cmd5.label_name, ":label"))
        printf("bad label name %s\n", cur_cmd5.label_name);

    printf( "test 6\n");
    char* test_label2 = "JMP something";
    test.start = test_label2;
    Commands cur_cmd6 = {};

    if (split_line(test, &cur_cmd6) != 0) printf("error != 0\n");

    if (cur_cmd6.cmd_num != JMP) printf("err in cmd number push\n");

    if (cur_cmd6.arg_num != 0) printf("err in arg push\n");

    if (cur_cmd6.type_arg != LABEL) printf("err in type_arg push label\n");

    if (strcmp(cur_cmd6.label_name, "something")) printf("bad label name %s\n", cur_cmd6.label_name);

        printf( "test 7\n");
    char* test_label3 = "JA something";
    test.start = test_label3;
    Commands cur_cmd7 = {};

    if (split_line(test, &cur_cmd7) != 0) printf("error != 0\n");

    if (cur_cmd7.cmd_num != JA) printf("err in cmd number push\n");

    if (cur_cmd7.arg_num != 0) printf("err in arg push\n");

    if (cur_cmd7.type_arg != LABEL) printf("err in type_arg push label\n");

    if (strcmp(cur_cmd7.label_name, "something")) printf("bad label name %s\n", cur_cmd7.label_name);


    printf("End of test line split\n----------------------------------------------------------------------------\n");

}

void unit_tests()
{
    test_line_split();
//    test_disassembler();
}

