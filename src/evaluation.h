#ifndef COZY_INTERPRETER_EVALUATION_H
#define COZY_INTERPRETER_EVALUATION_H

#include <stdbool.h>
#include "binary_tree.h"

tree_node * parse(char *expression);
void remove_character_from_end(char *expression);
void remove_unnecessary_brackets(char *expression);
bool brackets_are_correct(char *expression);
char *skip_whitespace(char *source);
char * read_word(char *source, char *word);
void expression_to_ONP(char *expression, char *ONP);

#endif //COZY_INTERPRETER_EVALUATION_H
