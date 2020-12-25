#include "binary_tree.h"
#include <stdlib.h>

void create_new_node_operation(tree_node **node_ptr, Operation operation) {
    *node_ptr = (tree_node *) malloc(sizeof(tree_node));
    (*node_ptr)->operation = operation;
    (*node_ptr)->value = 0;
    (*node_ptr)->left = (*node_ptr)->right = NULL;
}

void create_new_node_value(tree_node **node_ptr, int value) {
    *node_ptr = malloc(sizeof(tree_node));
    (*node_ptr)->value = value;
    (*node_ptr)->operation = NOT_DEFINED;
    (*node_ptr)->left = (*node_ptr)->right = NULL;
}
