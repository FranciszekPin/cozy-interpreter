#include <stdbool.h>

#ifndef COZY_INTERPRETER_TEST_EVALUATION_H
#define COZY_INTERPRETER_TEST_EVALUATION_H

bool test_if_equal_remove_unnecessary_brackets(char *argument, char *expected_value);
bool test_if_equal_brackets_are_correct(char *argument, bool expected_value);

#endif //COZY_INTERPRETER_TEST_EVALUATION_H
