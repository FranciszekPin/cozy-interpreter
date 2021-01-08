#include <string.h>
#include "../src/evaluation.h"

bool test_if_equal_remove_unnecessary_brackets(char *argument, char *expected_value) {
    remove_unnecessary_brackets(argument);
    bool result = false;
    if (strcmp(argument, expected_value) == 0)
        result = true;

    return result;
}

bool test_if_equal_brackets_are_correct(char *argument, bool expected_value) {
    return brackets_are_correct(argument) == expected_value;
}

