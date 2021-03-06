#ifndef COZY_INTERPRETER_EVALUATION_H
#define COZY_INTERPRETER_EVALUATION_H

#include <stdbool.h>
#include "error_manager.h"
#include "parser.h"

typedef enum {
    NUMBER,
    VARIABLE,
    OPERATOR,
    OPENING_BRACKET,
    CLOSING_BRACKET,
    NOT_A_LEXICAL_UNIT
} lexical_unit_t;

char *
read_lexical_unit(char *source, char *word, instruction_tree_t instruction_tree, variable_register_t variable_register);

void separated_form_to_ONP(char *separated_form, char *ONP);

bool end_of_string(const char *string);

lexical_unit_t detect_to_which_lexical_unit_string_belongs(char *lexical_unit);

void convert_expression_to_separated_form(char *destination, char *expression, instruction_tree_t instruction_tree,
                                          variable_register_t variable_register);

error_t check_if_separated_form_is_correct(char *separated_form);

int calculate_ONP_val(char *ONP_expression, variable_register_t variable_register, int line_number,
                      instruction_tree_t instruction_tree);

error_t check_if_lexical_unit_is_correct(char *lexical_unit);

void expression_to_ONP(char *expression, char *ONP, int line_number, instruction_tree_t instruction_tree,
                       variable_register_t variable_register);

int evaluate_expression(char *expression, int line_number, instruction_tree_t instruction_tree,
                        variable_register_t variable_register);

int evaluate_variable(char *unit, variable_register_t variable_register, int line_number,
                      instruction_tree_t instruction_tree);

#endif //COZY_INTERPRETER_EVALUATION_H
