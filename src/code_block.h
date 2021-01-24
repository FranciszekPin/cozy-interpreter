#ifndef COZY_INTERPRETER_CODE_BLOCK_H
#define COZY_INTERPRETER_CODE_BLOCK_H

#include <stdlib.h>
#include "instruction.h"

typedef struct nd {
    instruction_tree_t instruction_tree;
    struct nd *next;
} node;

typedef node * code_block_t;

code_block_t create_new_code_block();
code_block_t insert_instruction(code_block_t code_block, instruction_t *instruction);
code_block_t remove_code_block(code_block_t code_block);

#endif //COZY_INTERPRETER_CODE_BLOCK_H
