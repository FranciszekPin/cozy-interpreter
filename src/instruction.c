#include "instruction.h"
#include "string_operations.h"
#include <stdlib.h>
#include <string.h>

type_of_instruction_t detect_type_of_instruction(char *word) {
    type_of_instruction_t typeOfInstruction = ASSIGN;
    if (equal(word, "if"))
        typeOfInstruction = IF;
    else if (equal(word, "while"))
        typeOfInstruction = WHILE;
    else if (equal(word, "end"))
        typeOfInstruction = END;
    else if (equal(word, "else"))
        typeOfInstruction = ELSE;
    else if (equal(word, "printStr"))
        typeOfInstruction = PRINT_STRING;
    else if (equal(word, "printVar"))
        typeOfInstruction = PRINT_VARIABLE;
    else if (equal(word, "read"))
        typeOfInstruction = READ;

    return typeOfInstruction;
}

instruction_tree_t create_instruction(type_of_instruction_t type_of_instruction, instruction_tree_t upper_instruction, char *ONP_expression, int line_number) {
    instruction_t * new_instruction = malloc(sizeof (instruction_t));
    new_instruction->type_of_instruction = type_of_instruction;
    strcpy(new_instruction->ONP_expression, ONP_expression);
    new_instruction->variable_name[0] = '\0';
    new_instruction->in_instruction_if_true = true;
    new_instruction->upper_instruction = upper_instruction;
    new_instruction->instruction_if_true = NULL;
    new_instruction->instruction_if_false = NULL;
    new_instruction->next_instruction = NULL;
    new_instruction->line_number = line_number;

    return new_instruction;
}

instruction_t * create_instruction_assignment(type_of_instruction_t type_of_instruction,instruction_tree_t upper_instruction, char *variable_name, char *ONP_expression, int line_number) {
    instruction_t * new_instruction = create_instruction(type_of_instruction, upper_instruction, ONP_expression, line_number);

    strcpy(new_instruction->variable_name, variable_name);

    return new_instruction;
}

instruction_tree_t insert_instruction(instruction_tree_t instruction_tree, instruction_t* instruction) {
    if (instruction_tree == NULL)
        instruction_tree = instruction;
    else {

        instruction_tree_t act_instruction = instruction_tree;
        while (act_instruction->next_instruction != NULL)
            act_instruction = act_instruction->next_instruction;

        act_instruction->next_instruction = instruction;
    }

    return instruction_tree;
}

instruction_tree_t remove_instruction_tree(instruction_tree_t instruction_tree) {
    if (instruction_tree == NULL)
        return NULL;

    instruction_tree_t instruction_if_true = instruction_tree->instruction_if_true;
    if (instruction_if_true != NULL)
        instruction_tree->instruction_if_true = remove_instruction_tree(instruction_if_true);


    instruction_tree_t instruction_if_false = instruction_tree->instruction_if_false;
    if (instruction_if_false != NULL)
        instruction_tree->instruction_if_false = remove_instruction_tree(instruction_if_false);

    instruction_tree_t next_instruction = instruction_tree->next_instruction;
    if (next_instruction != NULL)
        instruction_tree->next_instruction = remove_instruction_tree(next_instruction);

    free(instruction_tree);
    return NULL;
}