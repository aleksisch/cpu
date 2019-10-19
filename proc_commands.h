DEF(PUSH, 1, 1,
   {
        stack_push(&(processor->cpu_stack), elem[++counter]);
   })
DEF(POP, 2, 0,
    {
        stack_pop (&(processor->cpu_stack), &(processor->reg_a));
        stack_push(&(processor->cpu_stack),   processor->reg_a);
    })
DEF(ADD, 3, 0,
    {
        stack_pop (&(processor->cpu_stack), &(processor->reg_a));
        stack_pop (&(processor->cpu_stack), &(processor->reg_b));
        stack_push(&(processor->cpu_stack),   processor->reg_a + processor->reg_b);
    })
DEF(MULTIPLY, 4, 0,
    {
        stack_pop (&(processor->cpu_stack), &(processor->reg_a));
        stack_pop (&(processor->cpu_stack), &(processor->reg_b));
        stack_push(&(processor->cpu_stack),   processor->reg_a * processor->reg_b);
    })
DEF(SUB, 5, 0,
    {
        stack_pop (&(processor->cpu_stack), &(processor->reg_a));
        stack_pop (&(processor->cpu_stack), &(processor->reg_b));
        stack_push(&(processor->cpu_stack),   processor->reg_a - processor->reg_b);
    })
DEF(DIV, 6, 0,
    {
        stack_pop (&(processor->cpu_stack), &(processor->reg_a));
        stack_pop (&(processor->cpu_stack), &(processor->reg_b));
        stack_push(&(processor->cpu_stack),   processor->reg_a / processor->reg_b);
    })
DEF(PUSHAX, 7, 1,
    {
        processor->reg_a = elem[++counter];
    })
DEF(PUSHBX, 8, 1,
    {
        processor->reg_b = elem[++counter];
    })
DEF(PUSHCX, 9, 1,
    {
        processor->reg_c = elem[++counter];
    })
DEF(PUSHDX, 10, 1,
    {
        processor->reg_d = elem[++counter];
    })
DEF(GETAX, 11, 0,
    {
        stack_push(&(processor->cpu_stack), processor->reg_a);
    })
DEF(GETBX, 12, 0,
    {
        stack_push(&(processor->cpu_stack), processor->reg_b);
    })
DEF(GETCX, 13, 0,
    {
        stack_push(&(processor->cpu_stack), processor->reg_c);
    })
DEF(GETDX, 14, 0,
    {
        stack_push(&(processor->cpu_stack), processor->reg_d);
    })
