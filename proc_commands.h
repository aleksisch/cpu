#define VAR_POP(tmp) elem_t tmp = 0; stack_pop (&(processor->cpu_stack), &tmp);
#define PUSH_STACK(tmp)    stack_push(&(processor->cpu_stack), (tmp));

DEF(PUSH, Type_arg::ELEM_T,
   {
        PUSH_STACK(*((elem_t*) (asm_text + counter_byte)));

        counter_byte += sizeof(elem_t);
   })
DEF(ADD, Type_arg::NO_ARG,
    {
        VAR_POP(tmp1);
        VAR_POP(tmp2);

        PUSH_STACK(tmp1 + tmp2);
    })
DEF(MUL, Type_arg::NO_ARG,
    {
        VAR_POP(tmp1);
        VAR_POP(tmp2);

        PUSH_STACK(tmp1 * tmp2);
    })
DEF(SUB, Type_arg::NO_ARG,
    {
        VAR_POP(tmp1);
        VAR_POP(tmp2);

        PUSH_STACK(tmp1 - tmp2);
    })
DEF(DIV, Type_arg::NO_ARG,
    {
        VAR_POP(tmp1);
        VAR_POP(tmp2);

        PUSH_STACK(tmp1 / tmp2);
    })
DEF(PUSH, Type_arg::REG,
    {
        int cmd = (int) *((elem_t*) (asm_text + counter_byte));

        counter_byte += sizeof(elem_t);

        elem_t* ptr_reg = get_reg_num(cmd, processor);

        PUSH_STACK(*ptr_reg);
    })
DEF(POP, Type_arg::REG,
    {
        int cmd = (int) *((elem_t*) (asm_text + counter_byte));

        counter_byte += sizeof(elem_t);

        elem_t* ptr_reg = get_reg_num(cmd, processor);

        stack_pop(&(processor->cpu_stack), ptr_reg);
    })
DEF(IN, Type_arg::NO_ARG,
    {
        elem_t tmp = 0;

        scanf(CONST_FOR_ELEM_T, &tmp);

        PUSH_STACK(tmp);
    })
DEF(OUT, Type_arg::NO_ARG,
    {
        VAR_POP(tmp);

        printf(CONST_FOR_ELEM_T"\n", tmp);
    })
DEF(SQRT, Type_arg::NO_ARG,
    {
        VAR_POP(tmp);

        PUSH_STACK(sqrt(tmp));
    })
DEF(JMP, Type_arg::LABEL,
    {
        counter_byte = *((elem_t*) (asm_text + counter_byte));
    })
DEF(JA, Type_arg::LABEL,
    {
        VAR_POP(first);

        VAR_POP(second);

        if (first - second > 0)
            counter_byte = *((elem_t*) (asm_text + counter_byte));
        else
            counter_byte += sizeof(elem_t);
    })
DEF(END, Type_arg::NO_ARG, {})

DEF(PUSH, Type_arg::RAM,
    {
        int cmd = (int) *((elem_t*) (asm_text + counter_byte));

        counter_byte += sizeof(elem_t);

        PUSH_STACK(processor->RAM[cmd]);
    })

DEF(POP, Type_arg::RAM,
    {
        int cmd = (int) *((elem_t*) (asm_text + counter_byte));

        counter_byte += sizeof(elem_t);

        VAR_POP(temp);

        if (cmd > RAM_LENGTH) printf("OVERFLOW IN RAM\n");

        processor->RAM[cmd % RAM_LENGTH] = temp;
    })

DEF(PUSH, (Type_arg::RAM | Type_arg::REG),
    {
        int cmd = (int) *((elem_t*) (asm_text + counter_byte));

        counter_byte += sizeof(elem_t);

        int reg = (int) *(get_reg_num(cmd, processor));

        if (reg > RAM_LENGTH) printf("OWERFLOW IN RAM");

        stack_push(&(processor->cpu_stack), (processor->RAM)[reg%RAM_LENGTH]);
    })

DEF(POP, (Type_arg::RAM | Type_arg::REG),
    {
        int cmd = (int) *((elem_t*) (asm_text + counter_byte));

        counter_byte += sizeof(elem_t);

        int reg = (int) *(get_reg_num(cmd, processor));

        if (reg > RAM_LENGTH) printf("OWERFLOW IN RAM\n");

        stack_pop(&(processor->cpu_stack), processor->RAM + (reg));      //% to avoid
    })
DEF(CALL, Type_arg::LABEL,
    {
        stack_push(&(processor->func_stack), (elem_t) counter_byte);

        counter_byte = *((elem_t*) (asm_text + counter_byte));
    })
DEF(RET, Type_arg::NO_ARG,
    {
        elem_t stk = 0;

        stack_pop(&(processor->func_stack), &stk);

        counter_byte = ((int) stk) + sizeof(elem_t);
    })

