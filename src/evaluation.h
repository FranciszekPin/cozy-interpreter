#ifndef COZY_INTERPRETER_EVALUATION_H
#define COZY_INTERPRETER_EVALUATION_H

#include <stdbool.h>
#include "binary_tree.h"
#include "error_manager.h"

typedef enum {
    NUMBER,
    VARIABLE,
    OPERATOR,
    OPENING_BRACKET,
    CLOSING_BRACKET,
    NOT_A_LEXICAL_UNIT
} lexical_unit_t;

char *skip_whitespace(char *source);
char * read_lexical_unit(char *source, char *word);
void separated_form_to_ONP(char *separated_form, char *ONP);
bool end_of_string(const char *string);
lexical_unit_t detect_to_which_lexical_unit_string_belongs(char *lexical_unit);
void convert_expression_to_separated_form(char *destination, char *expression);
error_t check_if_separated_form_is_correct(char *separated_form);
int calculate_ONP_val(char *ONP_expression);
error_t check_if_lexical_unit_is_correct(char *lexical_unit);
char * read_from_separated_form(char *separated_form, char *word);

#endif //COZY_INTERPRETER_EVALUATION_H
