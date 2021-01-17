#ifndef COZY_INTERPRETER_STACK_H
#define COZY_INTERPRETER_STACK_H

#include <stdbool.h>
#include "constants.h"

typedef char * stack_val_t;

typedef struct element *stack_t;

stack_t create_stack();
stack_t push(stack_t stack, stack_val_t val);
stack_t pop(stack_t stack, stack_val_t val);
char * get_top(stack_t stack);
bool is_empty(stack_t stack);

#endif //COZY_INTERPRETER_STACK_H
