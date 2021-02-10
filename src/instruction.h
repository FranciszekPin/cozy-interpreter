#ifndef COZY_INTERPRETER_INSTRUCTION_H
#define COZY_INTERPRETER_INSTRUCTION_H

#include "constants.h"
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    ASSIGN,
    IF,
    ELSE,
    END,
    WHILE,
    PRINT_STRING,
    PRINT_VARIABLE,
    READ,
    START_PROGRAM
} type_of_instruction_t;

typedef struct ins {
    type_of_instruction_t type_of_instruction;
    char ONP_expression[LINE_LENGTH];
    char variable_name[LINE_LENGTH];
    struct ins *upper_instruction;
    struct ins *next_instruction;
    struct ins *instruction_if_true;
    struct ins *instruction_if_false;
    bool in_instruction_if_true;
    int line_number;
} instruction_t;

typedef instruction_t *instruction_tree_t;

type_of_instruction_t detect_type_of_instruction(char *word);

instruction_tree_t create_instruction_tree();

instruction_tree_t create_instruction(type_of_instruction_t type_of_instruction, instruction_tree_t upper_instruction,
                                      char *ONP_expression, int line_number);

instruction_t *
create_instruction_assignment(type_of_instruction_t type_of_instruction, instruction_tree_t upper_instruction,
                              char *variable_name, char *ONP_expression, int line_number);

instruction_tree_t insert_instruction(instruction_tree_t instruction_tree, instruction_t *instruction);

instruction_tree_t remove_instruction_tree(instruction_tree_t instruction_tree);

#endif //COZY_INTERPRETER_INSTRUCTION_H
