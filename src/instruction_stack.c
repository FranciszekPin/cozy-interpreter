#include "instruction_stack.h"
#include <stdlib.h>
#include <string.h>


struct element {
    instruction_stack_val_t val;
    instruction_stack_t next;
};

instruction_stack_t create_instruction_stack() {
    return NULL;
}

instruction_stack_t instruction_stack_push(instruction_stack_t stack, instruction_stack_val_t val) {
    instruction_stack_t new_element = (instruction_stack_t) malloc(sizeof (struct element));
    new_element->val = val;
    new_element->next = NULL;

    if (stack == NULL) {
        stack = new_element;
    }
    else {
        new_element->next = stack;
        stack = new_element;
    }

    return stack;
}

instruction_stack_t instruction_stuck_pop(instruction_stack_t stack, instruction_stack_val_t * val) {
    *val = stack->val;
    instruction_stack_t new_top = stack->next;
    free(stack);

    return new_top;
}

bool instruction_stuck_is_empty(instruction_stack_t stack) {
    return stack == NULL;
}

instruction_stack_val_t instruction_stuck_get_top(instruction_stack_t stack) {
    return stack->val;
}