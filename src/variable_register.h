#ifndef COZY_INTERPRETER_VARIABLE_REGISTER_H
#define COZY_INTERPRETER_VARIABLE_REGISTER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "constants.h"

typedef struct nd {
    int value;
    bool defined;
    struct nd * next_node[NUMBER_OF_LETTERS];
} node_t;

typedef node_t * variable_register_t;

int get_letter_code(char letter);

node_t * create();

variable_register_t insert(variable_register_t variable_register, char *name);

variable_register_t set_val(variable_register_t variable_register, char *name, int val);

// TODO: detect using undefined variable
// TODO: add detecting forbidden variable names

#endif //COZY_INTERPRETER_VARIABLE_REGISTER_H
