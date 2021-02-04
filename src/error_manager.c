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
        case ILLEGAL_VARIABLE_NAME:
            printf("variable with given name does not exist \n");
            break;
        case ILLEGAL_EXPRESSION_FORM:
            printf("expression format is wrong \n");
            break;
        case VARIABLE_DECLARED_TWICE:
            printf("variable is declared second time \n");
            break;
        case READ_FROM_END_OF_FILE:
            printf("attemp to read end of file\n");
            break;
        case WRONG_PROGRAM_STRUCTURE:
            printf("wrong program structure\n");
            break;
        default: {
            printf("unknown error is thrown\n");
        }
    }
    //printf("Error: %d\n", error_type);
    exit(error_type);
}