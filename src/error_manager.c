#include <stdio.h>
#include <stdlib.h>
#include "error_manager.h"


void throw_error(error_t error_type, int line_number, instruction_tree_t instruction_tree,
                 variable_register_t variable_register) {
    if (line_number == -1)
        printf("Error: ");
    else
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
            printf("variable can not be defined with this name\n");
            break;
        case ILLEGAL_EXPRESSION_FORM:
            printf("expression format is wrong \n");
            break;
        case VARIABLE_DECLARED_TWICE:
            printf("variable is declared second time \n");
            break;
        case READ_FROM_END_OF_FILE:
            printf("atemp to read end of file\n");
            break;
        case WRONG_PROGRAM_STRUCTURE:
            printf("wrong program structure\n");
            break;
        case NO_EXPRESSION_PROVIDED:
            printf("no expression provided\n");
            break;
        case WRONG_OPERATOR_USAGE:
            printf("operator is used in wrong way\n");
            break;
        case UNDEFINED_VARIABLE:
            printf("variable with given name is undefined\n");
            break;
        case TOO_LONG_LINE:
            printf("max line length is %d characters\n", CHARACTER_LIMIT);
            break;
        case NO_FILE_PROVIDED:
            printf("no source file to interpret\n");
            break;
        case TOO_MANY_ARGUMENTS:
            printf("too many arguments provided\n");
            break;
        case FILE_DOES_NOT_EXIST:
            printf("File with given name doesn't exist.\n");
            break;

        default: {
            printf("unknown error is thrown\n");
        }
    }
    remove_variable_register(variable_register);
    remove_instruction_tree(instruction_tree);
    exit(error_type);
}