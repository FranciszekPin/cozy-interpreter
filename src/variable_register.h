#ifndef COZY_INTERPRETER_VARIABLE_REGISTER_H
#define COZY_INTERPRETER_VARIABLE_REGISTER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "constants.h"
#include "source_code_reader.h"

typedef enum {
    INT,
    NOT_A_TYPE
} variable_type_t;

typedef struct nod {
    int value;
    bool defined;
    struct nod * next_node[NUMBER_OF_LETTERS];
} node_t;

typedef node_t * variable_register_t;

int get_letter_code(char letter);

node_t * create();

bool is_letter_code_proper_for_variable_name(int letter_code);

variable_register_t define_variable(variable_register_t variable_register, char *name, int line_number);

variable_register_t set_val(variable_register_t variable_register, char *name, int val, int line_number);

bool is_variable_defined(variable_register_t variable_register, char *name, int line_number);

int get_variable_val(variable_register_t variable_register, char *name, int line_number);

variable_type_t detect_variable_type(char *name);

variable_register_t remove_variable_register(variable_register_t variable_register);

#endif //COZY_INTERPRETER_VARIABLE_REGISTER_H
