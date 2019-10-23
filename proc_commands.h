DEF(PUSH, 1,
   {
        stack_push(&(processor->cpu_stack), *((elem_t*) (asm_text + counter_byte)));
        counter_byte += sizeof(elem_t);
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
DEF(MUL, 0,
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
DEF(S_PUSH, 1,
    {
        int cmd = (int) *((elem_t*) (asm_text + counter_byte));
        counter_byte += sizeof(elem_t);
        elem_t* ptr_reg = nullptr;
        if (cmd == 0) ptr_reg = &(processor->reg_a);
        if (cmd == 1) ptr_reg = &(processor->reg_b);
        if (cmd == 2) ptr_reg = &(processor->reg_c);
        if (cmd == 3) ptr_reg = &(processor->reg_d);

        stack_push(&(processor->cpu_stack), *ptr_reg);
    })
DEF(S_POP, 1,
    {
        int cmd = (int) *((elem_t*) (asm_text + counter_byte));
        counter_byte += sizeof(elem_t);
        elem_t* ptr_reg = nullptr;
        if (cmd == 0) ptr_reg = &(processor->reg_a);
        if (cmd == 1) ptr_reg = &(processor->reg_b);
        if (cmd == 2) ptr_reg = &(processor->reg_c);
        if (cmd == 3) ptr_reg = &(processor->reg_d);

        stack_pop(&(processor->cpu_stack), ptr_reg);
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
DEF(JMP, 1,
    {
        counter_byte = *((elem_t*) (asm_text + counter_byte));
    })
DEF(JA, 1,
    {
        elem_t first = 0;
        elem_t second = 0;
        stack_pop(&(processor->cpu_stack), &first);
        stack_pop(&(processor->cpu_stack), &second);

        if (first - second > 0)
            counter_byte = *((elem_t*) (asm_text + counter_byte));
        else
            counter_byte += sizeof(elem_t);
    })
DEF(END, 0, {})



