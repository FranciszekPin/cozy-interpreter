#include <stdlib.h>
#include "test_instruction.h"
#include "../src/instruction.h"
#include "tester_kit.h"

void test_instruction() {
    instruction_t *instruction = create_instruction(WHILE, NULL, "2 3 +");
    instruction_tree_t instruction_tree = NULL;
    instruction_tree = insert_instruction(instruction_tree, instruction);
    instruction_tree->instruction_if_true = create_instruction(WHILE, instruction, "2 3 +");
    instruction_tree->instruction_if_false = create_instruction_assignment(ASSIGN, instruction, "var", "2 3 +");
    run_test("test instruction_tree module: type of instruction_tree", instruction_tree->type_of_instruction == WHILE);
    run_test("test instruction_tree module: type of instruction_tree", strcmp(instruction_tree->ONP_expression, "2 3 +") == 0);
    instruction_tree = remove_instruction_tree(instruction_tree);

    run_test("test detecting instruciton type", detect_type_of_instruction("if") == IF);
    run_test("test detecting instruciton type", detect_type_of_instruction("while") == WHILE);
    run_test("test detecting instruciton type", detect_type_of_instruction("afaf") == ASSIGN);
}
