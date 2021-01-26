#ifndef COZY_INTERPRETER_SOURCE_CODE_READER_H
#define COZY_INTERPRETER_SOURCE_CODE_READER_H

#include <stdbool.h>
#include "constants.h"

typedef struct {
    char code[MAX_NUMBER_OF_LINES][LINE_LENGTH];
    int number_of_lines;
    int act_line_number;
} source_code_t;

void create_source_code_reader(source_code_t * source_code);

char *get_code_line(source_code_t *source_code);

bool are_lines_to_read(source_code_t *sourceCode);

void skip_empty_lines(source_code_t *source_code);

int get_number_of_lines(source_code_t *sourceCode);

int get_act_line_number(source_code_t *source_code);

void move_to_next_line(source_code_t *source_code);

void load_source_code(char *file_name, source_code_t *source_code);

#endif //COZY_INTERPRETER_SOURCE_CODE_READER_H
