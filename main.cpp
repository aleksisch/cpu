#include "main_proc.h"
using namespace std;

int main()
{
    make_binary_file();
    disassembler();
    cpu_struct proc; // auto construct
    CPU(&proc);
}
