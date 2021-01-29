#include <stdio.h>
#include <stdlib.h>
#include "error_manager.h"

void throw_error(error_t error_type, int line_number) {
    printf("Error in line %d: ", line_number);
    switch (error_type) {
        case EMPTY_FILE:
            printf("file is empty\n");
            break;
        case NO_PROGRAM_CLAUSE:
            printf("there is no program clause\n");
            break;
        case NO_NEW_LINE_AFTER_CLAUSE:
            printf("there should be no characters after clause\n");
            break;
        case WRONG_VARIABLE_TYPE_NAME:
            printf("specified variable type does not exist\n");
            break;
        case WRONG_ASSIGNMENT_EXPRESSION:
            printf("wrong assignment expression\n");
            break;
        case UNKNOWN_INSTRUCTION_TYPE:
            printf("wrong instruction type is passed\n");
            break;
        default: {
            printf("unknown error is thrown\n");
        }
    }
    //printf("Error: %d\n", error_type);
    exit(0);
}