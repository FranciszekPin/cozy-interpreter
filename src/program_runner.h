#ifndef COZY_INTERPRETER_PROGRAM_RUNNER_H
#define COZY_INTERPRETER_PROGRAM_RUNNER_H

#include "instruction.h"
#include "variable_register.h"

void run_program(instruction_tree_t instruction_tree, variable_register_t variableRegister);

#endif //COZY_INTERPRETER_PROGRAM_RUNNER_H
