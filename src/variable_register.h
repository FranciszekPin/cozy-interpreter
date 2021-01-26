#ifndef COZY_INTERPRETER_VARIABLE_REGISTER_H
#define COZY_INTERPRETER_VARIABLE_REGISTER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "constants.h"

typedef enum {
    INT,
    NOT_A_TYPE
} variable_type_t;

typedef struct nd {
    int value;
    bool defined;
    struct nd * next_node[NUMBER_OF_LETTERS];
} node_t;

typedef node_t * variable_register_t;

int get_letter_code(char letter);

node_t * create();

variable_register_t define_variable(variable_register_t variable_register, char *name);

variable_register_t set_val(variable_register_t variable_register, char *name, int val);

bool is_variable_defined(variable_register_t variable_register, char *name);

int get_variable_val(variable_register_t variable_register, char *name);

variable_type_t detect_variable_type(char *name);

variable_register_t remove_variable_register(variable_register_t variable_register);

// TODO: detect using undefined variable
// TODO: add detecting forbidden variable names
// TODO: detecting declaring variable twice

#endif //COZY_INTERPRETER_VARIABLE_REGISTER_H
