#ifndef DECLARE_H
#define DECLARE_H


#define STACK_CONSTRUCT(name) stack_construct(name, #name)

//#define NDEBUG

#ifdef NDEBUG
#define STACK_DUMP(this)

#else
#define STACK_DUMP(this_) stack_dump(this_)
#endif


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
typedef long long int elem_t;           //set default stack type
const int STD_LENGTH_STACK = 20;            //default stack length
const int POISON_BYTE      = 127;           //poison for memset
const int POISON_STACK     = 2354678786532; //canary in stack

struct stack_t
{
    int           canary_start;
    elem_t*       data;                  //pointer on stack data
    const char*   name;                  //struct name
    int           counter;               //pointer on last element
    elem_t*       pointer;               //reserve pointer on data
    int           stk_size;              //max current stack size
    long long int hash_array;            //hash of data
    int           canary_end;
    long long int hash_struct;           //hash of all element in struct
};

enum err_list
{
    UNDERFLOW_           = 1 << 0,                       //1
    STACK_OK             = 1 << 1,                       //2
    OVERFLOW_            = 1 << 2,                        //4
    NULL_STACK           = 1 << 3,                       //8
    CANARY_ERROR         = 1 << 4,                       //16
    HASH_ERROR           = 1 << 5,                      //32
    REALLOC_ERROR        = 1 << 6,                       //64
    BAD_POINTER          = 1 << 7,                      //128
    HASH_STRUCT_ERROR    = 1 << 8,                     //256
    ERROR_IN_CHANGE_SIZE = 1 << 9                      //512
};

int   stack_empty        (stack_t* this_);
void  stack_dump         (stack_t* this_);
int   stack_destroy      (stack_t* this_);
int   stack_up_size      (stack_t* this_);
int   stack_down_size    (stack_t* this_);
int   stack_construct    (stack_t* this_, char* this_name = "Unknown");
int   stack_push         (stack_t* this_, elem_t element);
int   stack_pop          (stack_t* this_, elem_t* element);


void   error                  (stack_t* this_, char* er);
void   stack_perror           (stack_t* this_, int error);
bool   chek_stack_canary      (stack_t* this_);
int    stack_ok                (stack_t* this_);
long long int get_hash_array  (stack_t* this_);
long long int get_hash_struct (stack_t* this_);

int    update_hash_struct (stack_t* this_);
long long int hash_bytes (char* pointer_start, char* pointer_end);
int    test();
#endif // DECLARE_H
