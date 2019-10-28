#define VAR_POP(tmp) elem_t tmp = 0; stack_pop (&(processor->cpu_stack), &tmp);
#define PUSH_STACK(tmp)    stack_push(&(processor->cpu_stack), (tmp));

DEF(PUSH, ELEM_T,
   {
        PUSH_STACK(*((elem_t*) (asm_text + counter_byte)));

        counter_byte += sizeof(elem_t);
   })
DEF(ADD, NO_ARG,
    {
        VAR_POP(tmp1);
        VAR_POP(tmp2);

        PUSH_STACK(tmp1 + tmp2);
    })
DEF(MUL, NO_ARG,
    {
        VAR_POP(tmp1);
        VAR_POP(tmp2);

        PUSH_STACK(tmp1 * tmp2);
    })
DEF(SUB, NO_ARG,
    {
        VAR_POP(tmp1);
        VAR_POP(tmp2);

        PUSH_STACK(tmp1 - tmp2);
    })
DEF(DIV, NO_ARG,
    {
        VAR_POP(tmp1);
        VAR_POP(tmp2);

        PUSH_STACK(tmp1 / tmp2);
    })
DEF(PUSH, REG,
    {
        int cmd = (int) *((elem_t*) (asm_text + counter_byte));

        counter_byte += sizeof(elem_t);

        elem_t* ptr_reg = get_reg_num(cmd, processor);

        PUSH_STACK(*ptr_reg);
    })
DEF(POP, REG,
    {
        int cmd = (int) *((elem_t*) (asm_text + counter_byte));

        counter_byte += sizeof(elem_t);

        elem_t* ptr_reg = get_reg_num(cmd, processor);

        stack_pop(&(processor->cpu_stack), ptr_reg);
    })
DEF(IN, NO_ARG,
    {
        elem_t tmp = 0;

        scanf(CONST_FOR_ELEM_T, &tmp);

        PUSH_STACK(tmp);
    })
DEF(OUT, NO_ARG,
    {
        VAR_POP(tmp);

        printf(CONST_FOR_ELEM_T"\n", tmp);
    })
DEF(SQRT, NO_ARG,
    {
        VAR_POP(tmp);

        PUSH_STACK(sqrt(tmp));
    })
DEF(JMP, LABEL,
    {
        counter_byte = (int) *((elem_t*) (asm_text + counter_byte));
    })
DEF(JA, LABEL,
    {
        VAR_POP(first);

        VAR_POP(second);

        if (first - second > 0)
            counter_byte = (int) *((elem_t*) (asm_text + counter_byte));

        else
            counter_byte += sizeof(elem_t);
    })
DEF(JAE, LABEL,
    {
        VAR_POP(first);

        VAR_POP(second);

        if (first == second)
            counter_byte = (int) *((elem_t*) (asm_text + counter_byte));

        else
            counter_byte += sizeof(elem_t);
    })
DEF(END, NO_ARG, {})

DEF(PUSH, RAM,
    {
        int cmd = (int) *((elem_t*) (asm_text + counter_byte));

        counter_byte += sizeof(elem_t);

        PUSH_STACK(processor->RAM[cmd % RAM_LENGTH]);
    })

DEF(POP, RAM,
    {
        int cmd = (int) *((elem_t*) (asm_text + counter_byte));

        counter_byte += sizeof(elem_t);

        VAR_POP(temp);

        if (cmd > RAM_LENGTH) printf("OVERFLOW IN RAM\n");

        processor->RAM[cmd % RAM_LENGTH] = temp;
    })

DEF(PUSH, (RAM | REG),
    {
        int cmd = (int) *((elem_t*) (asm_text + counter_byte));

        counter_byte += sizeof(elem_t);

        int reg = (int) *(get_reg_num(cmd, processor));

        if (reg > RAM_LENGTH || reg < 0) printf("OWERFLOW IN RAM || BAD REG");

        else stack_push(&(processor->cpu_stack), (processor->RAM)[reg % RAM_LENGTH]);
    })

DEF(POP, (RAM | REG),
    {
        int cmd = (int) *((elem_t*) (asm_text + counter_byte));

        counter_byte += sizeof(elem_t);

        int reg = (int) *(get_reg_num(cmd, processor));

        if (reg > RAM_LENGTH || reg < 0) printf("OWERFLOW IN RAM\n");

        else stack_pop(&(processor->cpu_stack), processor->RAM + (reg % RAM_LENGTH));
    })
DEF(CALL, LABEL,
    {
        stack_push(&(processor->func_stack), (elem_t) counter_byte);

        counter_byte = (int) *((elem_t*) (asm_text + counter_byte));
    })
DEF(RET, NO_ARG,
    {
        elem_t stk = 0;

        stack_pop(&(processor->func_stack), &stk);

        counter_byte = ((int) stk) + sizeof(elem_t);
    })
DEF(DUMP, NO_ARG,
    {
        stack_dump(&(processor->cpu_stack));
    })
