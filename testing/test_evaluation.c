#include <string.h>
#include "../evaluation.h"

bool test_if_equal_remove_unnecessary_brackets(char *argument, char *expected_value) {
    remove_unnecessary_brackets(argument);
    bool result = false;
    if (strcmp(argument, expected_value) == 0)
        result = true;

    return result;
}

