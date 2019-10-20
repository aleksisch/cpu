DEF(PUSH, 1,
   {
        stack_push(&(processor->cpu_stack), asm_arguments[counter_arg++]);
   })
DEF(POP, 0,
    {
        stack_pop (&(processor->cpu_stack), &(processor->reg_a));
        stack_push(&(processor->cpu_stack),   processor->reg_a);
    })
DEF(ADD, 0,
    {
        elem_t tmp1 = 0;
        elem_t tmp2 = 0;
        stack_pop (&(processor->cpu_stack), &tmp1);
        stack_pop (&(processor->cpu_stack), &tmp2);
        stack_push(&(processor->cpu_stack), tmp1 + tmp2);
    })
DEF(MULTIPLY, 0,
    {
        elem_t tmp1 = 0;
        elem_t tmp2 = 0;
        stack_pop (&(processor->cpu_stack), &tmp1);
        stack_pop (&(processor->cpu_stack), &tmp2);
        stack_push(&(processor->cpu_stack),  tmp1 * tmp2);
    })
DEF(SUB, 0,
    {
        elem_t tmp1 = 0;
        elem_t tmp2 = 0;
        stack_pop (&(processor->cpu_stack), &tmp1);
        stack_pop (&(processor->cpu_stack), &tmp2);
        stack_push(&(processor->cpu_stack),  tmp1 - tmp2);
    })
DEF(DIV, 0,
    {
        elem_t tmp1 = 0;
        elem_t tmp2 = 0;
        stack_pop (&(processor->cpu_stack), &tmp1);
        stack_pop (&(processor->cpu_stack), &tmp2);
        stack_push(&(processor->cpu_stack),  tmp1 / tmp2);
    })
DEF(PUSHAX, 0,
    {
        stack_push(&(processor->cpu_stack), processor->reg_a);
    })
DEF(PUSHBX, 0,
    {
        stack_push(&(processor->cpu_stack), processor->reg_b);
    })
DEF(PUSHCX, 0,
    {
        stack_push(&(processor->cpu_stack), processor->reg_c);
    })
DEF(PUSHDX, 0,
    {
        stack_push(&(processor->cpu_stack), processor->reg_d);
    })
DEF(POPAX, 0,
    {
        stack_pop(&(processor->cpu_stack), &processor->reg_a);
    })
DEF(POPBX, 0,
    {
        stack_pop(&(processor->cpu_stack), &processor->reg_b);
    })
DEF(POPCX, 0,
    {
        stack_pop(&(processor->cpu_stack), &processor->reg_c);
    })
DEF(POPDX, 0,
    {
        stack_pop(&(processor->cpu_stack), &processor->reg_d);
    })
DEF(IN, 0,
    {
        elem_t tmp = 0;
        scanf(CONST_FOR_ELEM_T, &tmp);
        stack_push(&(processor->cpu_stack), tmp);
    })
DEF(OUT, 0,
    {
        elem_t tmp = 0;
        stack_pop(&(processor->cpu_stack), &tmp);
        printf(CONST_FOR_ELEM_T"\n", tmp);
    })
DEF(SQRT, 0,
    {
        elem_t tmp = 0;
        stack_pop(&(processor->cpu_stack), &tmp);
        stack_push(&(processor->cpu_stack), sqrt(tmp));
    })
