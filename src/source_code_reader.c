#include "source_code_reader.h"
#include <stdlib.h>
#include <stdio.h>
#include "instruction.h"
#include "error_manager.h"


void create_source_code_reader(source_code_t * source_code) {
    source_code->act_line_number = 0;
    source_code->number_of_lines = 0;
}

void load_source_code(char *file_name, source_code_t* source_code) {
    FILE *file;

    file = fopen(file_name, "r");
    if (file == NULL) {
        printf("File with given name doesn't exist.\n");
        exit(EXIT_FAILURE);
    }

    int line_number = 0;
    while (read_line(source_code->code[line_number], file, line_number))
        line_number++;

    source_code->number_of_lines = line_number;

    fclose(file);
}

bool read_line(char *destination, FILE * file, int line_number) {
    int n = 0;
    int c;
    while ((c = fgetc(file)) != EOF && (c != '\n'))
    {
        if (n == CHARACTER_LIMIT) {
            throw_error(TOO_LONG_LINE, line_number+1, NULL, NULL);
        }
        destination[n++] = (char) c;
    }

    destination[n] = '\0';

    bool result = true;
    if (c == EOF && n == 0)
        result = false;

    return result;
}

char *get_code_line(source_code_t *source_code, instruction_tree_t instruction_tree, variable_register_t variable_register) {
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

void move_to_next_line(source_code_t *source_code) {
    source_code->act_line_number++;
}

bool are_lines_to_read(source_code_t *sourceCode) {
    return get_act_line_number(sourceCode) < get_number_of_lines(sourceCode);
}

void skip_empty_lines(source_code_t *source_code, instruction_tree_t instruction_tree, variable_register_t variable_register) {
    char *act_line = get_code_line(source_code, instruction_tree, variable_register);
    act_line = skip_whitespace(act_line);
    while (are_lines_to_read(source_code) && *act_line == '\0') {
        move_to_next_line(source_code);
        if (are_lines_to_read(source_code)) {
            act_line = get_code_line(source_code, instruction_tree, variable_register);
            act_line = skip_whitespace(act_line);
        }
    }
}

