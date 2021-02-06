#ifndef COZY_INTERPRETER_STRING_OPERATIONS_H
#define COZY_INTERPRETER_STRING_OPERATIONS_H

#include <stdbool.h>

char *skip_whitespace(char *source);

char *read_word(char *separated_form, char *word);

bool equal(char *string_a, char *string_b);

void lower_word(char *word);

char *read_first_word_after_whitespace(char *text, char *word);

#endif //COZY_INTERPRETER_STRING_OPERATIONS_H
