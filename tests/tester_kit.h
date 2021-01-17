#ifndef COZY_INTERPRETER_TESTER_KIT_H
#define COZY_INTERPRETER_TESTER_KIT_H

#include <string.h>
#include <stdio.h>
#include <stdbool.h>

void run_test(char *test_title, bool passed);

bool test_if_result_equals_expected(char *result, char *expected_val);

void print_test_info(bool passed);


#endif //COZY_INTERPRETER_TESTER_KIT_H
