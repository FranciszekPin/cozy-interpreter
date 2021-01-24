#include <stdlib.h>
#include "test_instruction.h"
#include "../src/instruction.h"
#include "tester_kit.h"

void test_instruction() {
    instruction_tree_t instruction_tree = create_instruction(IF, "2 3 +");
    instruction_tree->instruction_if_true = create_instruction(WHILE, "i dont know");
    instruction_tree->instruction_if_false = create_instruction(IF, "another one bites the dus");
    run_test("test instruction_tree module: type of instruction_tree", instruction_tree->type_of_instruction == IF);
    run_test("test instruction_tree module: type of instruction_tree", strcmp(instruction_tree->ONP_expression, "2 3 +") == 0);
    instruction_tree = remove_instruction_tree(instruction_tree);
}