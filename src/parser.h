#ifndef COZY_INTERPRETER_PARSER_H
#define COZY_INTERPRETER_PARSER_H

#include "source_code_reader.h"
#include "variable_register.h"
#include "instruction.h"
#include "source_code_reader.h"
#include "string_operations.h"
#include "variable_register.h"
#include "instruction.h"
#include "evaluation.h"
#include "instruction_stack.h"

void load_defined_variables(source_code_t *source_code, variable_register_t variable_register, instruction_tree_t instruction_tree);

void load_variable(source_code_t *source_code, variable_register_t variable_register, instruction_tree_t instruction_tree);

instruction_tree_t parse_program(source_code_t *source_code, instruction_tree_t instruction_tree, variable_register_t variable_register);

#endif //COZY_INTERPRETER_PARSER_H
