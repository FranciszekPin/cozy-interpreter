#include <string.h>
#include "../src/constants.h"
#include "test_evaluation.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int exit_val = 1;

    char function_name[LINE_LENGTH];
    strcpy(function_name, argv[1]);

    char operation[LINE_LENGTH];
    strcpy(operation, argv[2]);

    char function_arguments[argc-2][LINE_LENGTH];
    for (int i=0; i<argc-4; i++)
        strcpy(function_arguments[i], argv[i+3]);

    char value_to_check[LINE_LENGTH];
    strcpy(value_to_check, argv[argc-1]);
    if (strcmp(function_name, "remove_unnecessary_brackets") == 0) {
        if (test_if_equal_remove_unnecessary_brackets(function_arguments[0], value_to_check))
            exit_val = 0;
    }
    if (strcmp(function_name, "brackets_are_correct") == 0) {
        if (test_if_equal_brackets_are_correct(function_arguments[0], atoi(value_to_check)))
            exit_val = 0;
    }
    return exit_val;
}