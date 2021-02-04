#ifndef COZY_INTERPRETER_INSTRUCTION_STACK_H
#define COZY_INTERPRETER_INSTRUCTION_STACK_H

#include <stdbool.h>
#include "constants.h"
#include "instruction.h"

typedef type_of_instruction_t instruction_stack_val_t;

typedef struct element *instruction_stack_t;

instruction_stack_t create_instruction_stack();
instruction_stack_t instruction_stack_push(instruction_stack_t stack, instruction_stack_val_t val);
instruction_stack_t instruction_stuck_pop(instruction_stack_t stack, instruction_stack_val_t * val);
instruction_stack_val_t instruction_stuck_get_top(instruction_stack_t stack);
bool instruction_stuck_is_empty(instruction_stack_t stack);

#endif //COZY_INTERPRETER_INSTRUCTION_STACK_H
