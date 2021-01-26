//
// Created by learning-account on 24.01.2021.
//

#ifndef COZY_INTERPRETER_STRING_OPERATIONS_H
#define COZY_INTERPRETER_STRING_OPERATIONS_H

#include <stdbool.h>
#include "binary_tree.h"
#include "error_manager.h"

char *skip_whitespace(char *source);

char * read_word(char *separated_form, char *word);

bool equal(char *string_a, char *string_b);

char *read_first_word_after_whitespace(char *text, char *word);

#endif //COZY_INTERPRETER_STRING_OPERATIONS_H
