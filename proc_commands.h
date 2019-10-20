DEF(PUSH, 1, 1,
   {
        stack_push(&(processor->cpu_stack), asm_arguments[counter_arg++]);
   })
DEF(POP, 2, 0,
    {
        stack_pop (&(processor->cpu_stack), &(processor->reg_a));
        stack_push(&(processor->cpu_stack),   processor->reg_a);
    })
DEF(ADD, 3, 0,
    {
        elem_t tmp1 = 0;
        elem_t tmp2 = 0;
        stack_pop (&(processor->cpu_stack), &tmp1);
        stack_pop (&(processor->cpu_stack), &tmp2);
        stack_push(&(processor->cpu_stack), tmp1 + tmp2);
    })
DEF(MULTIPLY, 4, 0,
    {
        elem_t tmp1 = 0;
        elem_t tmp2 = 0;
        stack_pop (&(processor->cpu_stack), &tmp1);
        stack_pop (&(processor->cpu_stack), &tmp2);
        stack_push(&(processor->cpu_stack),  tmp1 * tmp2);
    })
DEF(SUB, 5, 0,
    {
        elem_t tmp1 = 0;
        elem_t tmp2 = 0;
        stack_pop (&(processor->cpu_stack), &tmp1);
        stack_pop (&(processor->cpu_stack), &tmp2);
        stack_push(&(processor->cpu_stack),  tmp1 - tmp2);
    })
DEF(DIV, 6, 0,
    {
        elem_t tmp1 = 0;
        elem_t tmp2 = 0;
        stack_pop (&(processor->cpu_stack), &tmp1);
        stack_pop (&(processor->cpu_stack), &tmp2);
        stack_push(&(processor->cpu_stack),  tmp1 / tmp2);
    })
DEF(PUSHAX, 7, 0,
    {
        stack_push(&(processor->cpu_stack), processor->reg_a);
    })
DEF(PUSHBX, 8, 0,
    {
        stack_push(&(processor->cpu_stack), processor->reg_b);
    })
DEF(PUSHCX, 9, 0,
    {
        stack_push(&(processor->cpu_stack), processor->reg_c);
    })
DEF(PUSHDX, 10, 0,
    {
        stack_push(&(processor->cpu_stack), processor->reg_d);
    })
DEF(POPAX, 11, 0,
    {
        stack_pop(&(processor->cpu_stack), &processor->reg_a);
    })
DEF(POPBX, 12, 0,
    {
        stack_pop(&(processor->cpu_stack), &processor->reg_b);
    })
DEF(POPCX, 13, 0,
    {
        stack_pop(&(processor->cpu_stack), &processor->reg_c);
    })
DEF(POPDX, 14, 0,
    {
        stack_pop(&(processor->cpu_stack), &processor->reg_d);
    })
DEF(IN, 15, 0,
    {
        elem_t tmp = 0;
        scanf(CONST_FOR_ELEM_T, &tmp);
        stack_push(&(processor->cpu_stack), tmp);
    })
DEF(OUT, 16, 0,
    {
        elem_t tmp = 0;
        stack_pop(&(processor->cpu_stack), &tmp);
        printf(CONST_FOR_ELEM_T"\n", tmp);
    })
DEF(SQRT, 17, 0,
    {
        elem_t tmp = 0;
        stack_pop(&(processor->cpu_stack), &tmp);
        stack_push(&(processor->cpu_stack), sqrt(tmp));
    })
