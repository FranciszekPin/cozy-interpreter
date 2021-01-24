#ifndef COZY_INTERPRETER_INSTRUCTION_H
#define COZY_INTERPRETER_INSTRUCTION_H

#include "constants.h"
#include <stdlib.h>

typedef enum {
    ASSIGN,
    IF,
    WHILE,
    PRINT
} type_of_instruction_t;

typedef struct ins {
    type_of_instruction_t type_of_instruction;
    char ONP_expression[LINE_LENGTH];
    int variable_id;
    struct ins *instruction_if_true;
    struct ins *instruction_if_false;
} instruction_t;

typedef instruction_t *instruction_tree_t;

instruction_t * create_instruction(type_of_instruction_t type_of_instruction, char *ONP_expression);

instruction_tree_t remove_instruction_tree(instruction_tree_t instruction_tree);

#endif //COZY_INTERPRETER_INSTRUCTION_H
