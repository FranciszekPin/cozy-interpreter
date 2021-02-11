#ifndef COZY_INTERPRETER_SOURCE_CODE_READER_H
#define COZY_INTERPRETER_SOURCE_CODE_READER_H

#include <stdbool.h>
#include "variable_register.h"
#include "constants.h"
#include "string_operations.h"
#include "instruction.h"



typedef struct {
    char code[MAX_NUMBER_OF_LINES][LINE_LENGTH];
    int number_of_lines;
    int act_line_number;
} source_code_t;

void create_source_code_reader(source_code_t * source_code);

char *get_act_code_line(source_code_t *source_code, instruction_tree_t instruction_tree, variable_register_t variable_register);

bool are_lines_to_read(source_code_t *sourceCode);

void skip_empty_lines(source_code_t *source_code, instruction_tree_t instruction_tree, variable_register_t variable_register);

int get_number_of_lines(source_code_t *sourceCode);

bool read_line(char *destination, FILE * file, int line_number);

int get_act_line_number(source_code_t *source_code);

void go_to_next_line(source_code_t *source_code);

void load_source_code(source_code_t *source_code, char *file_name);

#endif //COZY_INTERPRETER_SOURCE_CODE_READER_H
