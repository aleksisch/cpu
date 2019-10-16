DEF(PUSH, 1, 1,
   {
        stack_push(&(processor->cpu_stack), elem[++counter]); counter++;
   })
DEF(ADD, 2, 0,
    {
        stack_pop (&(processor->cpu_stack), &(processor->reg_a));
        stack_pop (&(processor->cpu_stack), &(processor->reg_b));
        stack_push(&(processor->cpu_stack),  processor->reg_a + processor->reg_b);
        counter++;
    })
DEF(MULTIPLY, 3, 0,
    {
        stack_pop (&(processor->cpu_stack), &(processor->reg_a));
        stack_pop (&(processor->cpu_stack), &(processor->reg_b));
        stack_push(&(processor->cpu_stack),  processor->reg_a * processor->reg_b);
        counter++;
    })

