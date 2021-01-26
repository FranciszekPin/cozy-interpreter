//
// Created by learning-account on 24.01.2021.
//

#include "error_manager.h"
#include "stack.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "evaluation.h"
#include "string_operations.h"



char *skip_whitespace(char *source) {
    while (*source != '\0' && isspace(*source)) {
        source++;
    }

    return source;
}

bool equal(char *string_a, char *string_b) {
    return strcmp(string_a, string_b) == 0;
}

char *read_word(char *separated_form, char *word) {
    while (*separated_form != '\0' && !isspace(*separated_form)) {
        *word = *separated_form;
        word++, separated_form++;
    }

    *word = '\0';
    if (*separated_form == ONP_SEPARATOR)
        separated_form++;

    return separated_form;
}

char *read_first_word_after_whitespace(char *text, char *word) {
    text = skip_whitespace(text);
    text = read_word(text, word);

    return text;
}