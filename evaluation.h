#ifndef COZY_INTERPRETER_EVALUATION_H
#define COZY_INTERPRETER_EVALUATION_H

#include <stdbool.h>
#include "binary_tree.h"

char * readNumber(char *expression, int* number);
char *find_first_operation(char *expression);
bool check_if_brackets_are_correct(char *expression);

#endif //COZY_INTERPRETER_EVALUATION_H
