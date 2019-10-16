#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

struct pointer
{
    char* start;
    char* end;
};


static const int MAX_SIZE = 256;
void work_file(int *size, struct pointer** lineptr, char** text, char* input, int* countline);
char *readFile (char* str, int *size, char* chmod = "r");
int get_line (char* text, int size);
void get_ptr (char* text, struct pointer* lineptr, int size);

#endif // FUNC_H_INCLUDED
