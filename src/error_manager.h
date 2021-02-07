#ifndef COZY_INTERPRETER_ERROR_MANAGER_H
#define COZY_INTERPRETER_ERROR_MANAGER_H

#include "instruction.h"
#include "variable_register.h"


typedef enum {
    NO_ERROR,
    INCORRECT_BRACKETS,
    WRONG_OPERATOR_USAGE,
    NUMBER_AFTER_NUMBER,
    VARIABLE_AFTER_VARIABLE,
    ILLEGAL_CHARACTER_USAGE,
    ILLEGAL_VARIABLE_NAME,
    ILLEGAL_EXPRESSION_FORM,
    EMPTY_FILE,
    NO_PROGRAM_CLAUSE,
    NO_NEW_LINE_AFTER_CLAUSE,
    WRONG_VARIABLE_TYPE_NAME,
    WRONG_ASSIGNMENT_EXPRESSION,
    UNKNOWN_INSTRUCTION_TYPE,
    VARIABLE_DECLARED_TWICE,
    READ_FROM_END_OF_FILE,
    WRONG_PROGRAM_STRUCTURE,
    NO_EXPRESSION_PROVIDED,
    UNDEFINED_VARIABLE,
    TOO_LONG_LINE
} error_t;


void throw_error(error_t error_type, int line_number, instruction_tree_t instruction_tree, variable_register_t variable_register);

#endif //COZY_INTERPRETER_ERROR_MANAGER_H
