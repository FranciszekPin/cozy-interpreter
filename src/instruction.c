#include "instruction.h"
#include <stdlib.h>
#include <string.h>


instruction_t * create_instruction(type_of_instruction_t type_of_instruction, char *ONP_expression) {
    instruction_t * new_instruction = malloc(sizeof (instruction_t));
    new_instruction->type_of_instruction = type_of_instruction;
    strcpy(new_instruction->ONP_expression, ONP_expression);
    new_instruction->instruction_if_true = NULL;
    new_instruction->instruction_if_false = NULL;
    new_instruction->variable_id = 0;

    return new_instruction;
}

instruction_tree_t remove_instruction_tree(instruction_tree_t instruction_tree) {
    instruction_tree_t instruction_if_true = instruction_tree->instruction_if_true;
    if (instruction_if_true != NULL)
        instruction_tree->instruction_if_true = remove_instruction_tree(instruction_if_true);


    instruction_tree_t instruction_if_false = instruction_tree->instruction_if_false;
    if (instruction_if_false != NULL)
        instruction_tree->instruction_if_false = remove_instruction_tree(instruction_if_false);

    free(instruction_tree);
    return NULL;
}