#include <stdio.h>
#include <stdlib.h>

int main()
{

    FILE* bin;
    bin = fopen("input.bin", "w+b");
    int a = 1923614;
    fwrite(&a, sizeof(int), 1, bin );
    fwrite(&a, sizeof(int), 1, bin );
    fwrite(&a, sizeof(int), 1, bin );
    fwrite(&a, sizeof(int), 1, bin );
    fclose(bin);
    int b = 0;
    bin = fopen("input.bin", "r+b");
    printf("%d  ", fread(&b, sizeof(int), 1, bin));
    printf("%d is b", b);
    fclose(bin);
    system("pause");
}
