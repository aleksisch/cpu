#include <iostream>
#include <cmath>

/*int split_line(pointer_on_line cur_ptr, char *&cmd_name, int *&cmd_array)
{
    cmd_name  = calloc (S_LENGTH, sizeof(char));
    cmd_array = calloc (AVG_COMMAND, sizeof(int));

    int readed = 0;
    int num = 0;
    int count_number = 0;

    while (sscanf("%d", &num) == 0)
    {
        sscanf(cur_ptr, "%s %n", cmd_name+readed, &num);
        readed += num + 1;
        if (readed >= 200) cmd_name = realloc(2*S_LENGTH, sizeof(char));
    }
    while (sscanf("%d %n", readed+count_number, &num) == 2)
    {
        readed += num;
        count_number++;
    }
}*/

int main()
{
    FILE* input = fopen("hello.bin", "w+b");
    fwrite("sdfsdf", 1,6,input);
    system("pause");
}
