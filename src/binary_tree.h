#ifndef COZY_INTERPRETER_BINARY_TREE_H
#define COZY_INTERPRETER_BINARY_TREE_H

#include "constants.h"

typedef enum op {
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    ASSIGN,
    NOT_DEFINED
} Operation;

typedef struct node {
    Operation operation;
    char value[LINE_LENGTH];

    struct node* left;
    struct node* right;
} tree_node;

void create_new_node_operation(tree_node **node_ptr, Operation operation);
void create_new_node_value(tree_node **node_ptr, char* value);

#endif //COZY_INTERPRETER_BINARY_TREE_H