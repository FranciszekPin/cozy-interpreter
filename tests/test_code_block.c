#include "test_code_block.h"
#include "../src/code_block.h"


void test_code_block() {
    instruction_t * instruction = create_instruction(WHILE, "2 6 <");
    code_block_t code_block = NULL;
    code_block = insert_instruction(code_block, instruction);
    instruction = create_instruction(IF, "a 10 ==");
    code_block->instruction_tree->instruction_if_true = instruction;
    instruction = create_instruction(PRINT, "someVar");
    code_block = insert_instruction(code_block, instruction);

    code_block = remove_code_block(code_block);
}