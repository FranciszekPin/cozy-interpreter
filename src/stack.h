#ifndef COZY_INTERPRETER_STACK_H
#define COZY_INTERPRETER_STACK_H

#include <stdbool.h>

typedef int stack_val;
typedef struct element *stack_t;

stack_t create_stack();
stack_t push(stack_t stack, stack_val val);
stack_t pop(stack_t stack, stack_val *val);

#endif //COZY_INTERPRETER_STACK_H
