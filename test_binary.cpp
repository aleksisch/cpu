#include <stdio.h>

int main()
{
    FILE* bin;
    bin = fopen("input.bin", "wb");
    int a = 1923614;
    fwrite(&a, sizeof(int), 1, bin );
}
