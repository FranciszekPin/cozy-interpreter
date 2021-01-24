#include "code_block.h"
#include "instruction.h"


code_block_t create_new_code_block(instruction_t *instruction) {
    code_block_t new_code_block = malloc(sizeof(struct nd));
    new_code_block->instruction_tree = instruction;
    new_code_block->next = NULL;
}

code_block_t insert_instruction(code_block_t code_block, instruction_t *instruction) {
    if (code_block != NULL) {
        code_block_t act_instruction = code_block;
        while (act_instruction->next != NULL) {
            act_instruction = act_instruction->next;
        }

        act_instruction->next = create_new_code_block(instruction);
    }
    else {
        code_block = create_new_code_block(instruction);
    }

    return code_block;
}

code_block_t remove_code_block(code_block_t code_block) {
    if (code_block->next != NULL)
        code_block->next = remove_code_block(code_block->next);

    code_block->instruction_tree = remove_instruction_tree(code_block->instruction_tree);
    free(code_block);
    return NULL;
}