#include "source_code_reader.h"
#include <stdlib.h>
#include <stdio.h>
#include "instruction.h"
#include "error_manager.h"


void create_source_code_reader(source_code_t *source_code) {
    source_code->act_line_number = 0;
    source_code->number_of_lines = 0;
}

void load_source_code(source_code_t *source_code, char *file_name) {
    FILE *file;
    file = fopen(file_name, "r");

    if (file == NULL)
        throw_error(FILE_DOES_NOT_EXIST, -1, NULL, NULL);

    int line_number = 0;
    while (read_line(source_code->code[line_number], file, line_number))
        line_number++;

    source_code->number_of_lines = line_number;

    fclose(file);
}

bool read_line(char *destination, FILE *file, int line_number) {
    int column_number = 0;
    int read_character;

    while ((read_character = fgetc(file)) != EOF && (read_character != '\n')) {
        if (column_number == CHARACTER_LIMIT) {
            throw_error(TOO_LONG_LINE, line_number + 1, NULL, NULL);
        }
        destination[column_number++] = (char) read_character;
    }

    destination[column_number] = '\0';

    bool result = true;
    if (read_character == EOF && column_number == 0)
        result = false;

    return result;
}

char *
get_act_code_line(source_code_t *source_code, instruction_tree_t instruction_tree,
                  variable_register_t variable_register) {
    if (source_code->act_line_number >= source_code->number_of_lines) {
        throw_error(READ_FROM_END_OF_FILE, 0, instruction_tree, variable_register);
    }

    return source_code->code[source_code->act_line_number];
}

int get_number_of_lines(source_code_t *sourceCode) {
    return sourceCode->number_of_lines;
}

int get_act_line_number(source_code_t *source_code) {
    return source_code->act_line_number;
}

void go_to_next_line(source_code_t *source_code) {
    source_code->act_line_number++;
}

bool are_lines_to_read(source_code_t *sourceCode) {
    return get_act_line_number(sourceCode) < get_number_of_lines(sourceCode);
}

void skip_empty_lines(source_code_t *source_code, instruction_tree_t instruction_tree,
                      variable_register_t variable_register) {
    char *act_line = get_act_code_line(source_code, instruction_tree, variable_register);
    act_line = skip_whitespace(act_line);
    while (are_lines_to_read(source_code) && *act_line == '\0') {
        go_to_next_line(source_code);
        if (are_lines_to_read(source_code)) {
            act_line = get_act_code_line(source_code, instruction_tree, variable_register);
            act_line = skip_whitespace(act_line);
        }
    }
}

