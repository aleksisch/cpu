#define VAR_POP(tmp) elem_t tmp = 0; stack_pop (&(processor->cpu_stack), &tmp);
#define PUSH_STACK(tmp)    stack_push(&(processor->cpu_stack), (tmp));

DEF(PUSH, 1,
   {
        PUSH_STACK(*((elem_t*) (asm_text + counter_byte)));

        counter_byte += sizeof(elem_t);
   })
DEF(ADD, 0,
    {
        VAR_POP(tmp1);
        VAR_POP(tmp2);

        PUSH_STACK(tmp1 + tmp2);
    })
DEF(MUL, 0,
    {
        VAR_POP(tmp1);
        VAR_POP(tmp2);

        PUSH_STACK(tmp1 * tmp2);
    })
DEF(SUB, 0,
    {
        VAR_POP(tmp1);
        VAR_POP(tmp2);

        PUSH_STACK(tmp1 - tmp2);
    })
DEF(DIV, 0,
    {
        VAR_POP(tmp1);
        VAR_POP(tmp2);

        PUSH_STACK(tmp1 / tmp2);
    })
DEF(S_PUSH, 1,
    {
        int cmd = (int) *((elem_t*) (asm_text + counter_byte));

        counter_byte += sizeof(elem_t);

        elem_t* ptr_reg = get_reg_num(cmd, processor);

        PUSH_STACK(*ptr_reg);
    })
DEF(S_POP, 1,
    {
        int cmd = (int) *((elem_t*) (asm_text + counter_byte));

        counter_byte += sizeof(elem_t);

        elem_t* ptr_reg = get_reg_num(cmd, processor);

        stack_pop(&(processor->cpu_stack), ptr_reg);
    })
DEF(IN, 0,
    {
        elem_t tmp = 0;

        scanf(CONST_FOR_ELEM_T, &tmp);

        PUSH_STACK(tmp);
    })
DEF(OUT, 0,
    {
        VAR_POP(tmp);

        printf(CONST_FOR_ELEM_T"\n", tmp);
    })
DEF(SQRT, 0,
    {
        VAR_POP(tmp);

        PUSH_STACK(sqrt(tmp));
    })
DEF(JMP, 1,
    {
        counter_byte = *((elem_t*) (asm_text + counter_byte));
    })
DEF(JA, 1,
    {
        VAR_POP(first);

        VAR_POP(second);

        if (first - second > 0)
            counter_byte = *((elem_t*) (asm_text + counter_byte));
        else
            counter_byte += sizeof(elem_t);
    })
DEF(END, 0, {})

DEF(R_PUSH, 1,
    {
        int cmd = (int) *((elem_t*) (asm_text + counter_byte));

        counter_byte += sizeof(elem_t);

        PUSH_STACK(processor->RAM[cmd]);
    })

DEF(R_POP, 1,
    {
        int cmd = (int) *((elem_t*) (asm_text + counter_byte));

        counter_byte += sizeof(elem_t);

        VAR_POP(temp);

        if (cmd > RAM_LENGTH) printf("OVERFLOW IN RAM\n");

        processor->RAM[cmd % RAM_LENGTH] = temp;
    })

DEF(RS_PUSH, 1,
    {
        int cmd = (int) *((elem_t*) (asm_text + counter_byte));

        counter_byte += sizeof(elem_t);

        int reg = (int) *(get_reg_num(cmd, processor));

        if (reg > RAM_LENGTH) printf("OWERFLOW IN RAM");

        stack_push(&(processor->cpu_stack), (processor->RAM)[reg%RAM_LENGTH]);
    })

DEF(RS_POP, 1,
    {
        int cmd = (int) *((elem_t*) (asm_text + counter_byte));

        counter_byte += sizeof(elem_t);

        int reg = (int) *(get_reg_num(cmd, processor));

        if (reg > RAM_LENGTH) printf("OWERFLOW IN RAM\n");

        stack_pop(&(processor->cpu_stack), processor->RAM + (reg));      //% to avoid
    })
DEF(CALL, 1,
    {
        stack_push(&(processor->func_stack), (elem_t) counter_byte);

        counter_byte = *((elem_t*) (asm_text + counter_byte));
    })
DEF(RET, 0,
    {
        elem_t stk = 0;

        stack_pop(&(processor->func_stack), &stk);

        counter_byte = ((int) stk) + sizeof(elem_t);
    })

