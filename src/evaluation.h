#ifndef COZY_INTERPRETER_EVALUATION_H
#define COZY_INTERPRETER_EVALUATION_H

#include <stdbool.h>
#include "binary_tree.h"

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
void expression_to_ONP(char *expression, char *ONP);
bool end_of_string(const char *string);
lexical_unit_t detect_to_which_lexical_unit_string_belongs(char *lexical_unit);
void convert_expression_to_separated_form(char *destination, char *expression);

#endif //COZY_INTERPRETER_EVALUATION_H
