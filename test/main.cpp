#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,b;
    sscanf("hui123 123", "%s %d", &a,&b);
    printf("%d %d", a, b);
    system("pause");
    FILE* bin;
    bin = fopen("input.bin", "w+b");

    fclose(bin);
    system("pause");
}
