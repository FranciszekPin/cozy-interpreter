#include "stack.h"
#include <stdlib.h>
#include <string.h>


struct element {
    stack_val_t val;
    stack_t next;
};

stack_t create_stack() {
    return NULL;
}

stack_t push(stack_t stack, stack_val_t val) {
    stack_t new_element = (stack_t) malloc(sizeof (struct element));
    new_element->val = (char *) malloc(sizeof (char) * LINE_LENGTH);
    strcpy(new_element->val, val);
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

stack_t pop(stack_t stack, stack_val_t val) {
    strcpy(val, stack->val);
    stack_t new_top = stack->next;
    free(stack->val);
    free(stack);

    return new_top;
}

bool is_empty(stack_t stack) {
    return stack == NULL;
}

char * get_top(stack_t stack) {
    return stack->val;
}