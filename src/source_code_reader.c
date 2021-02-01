#include "source_code_reader.h"
#include "string_operations.h"
#include <stdlib.h>
#include <stdio.h>


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
    while (fgets(source_code->code[line_number], LINE_LENGTH, file))
        line_number++;

    source_code->number_of_lines = line_number;

    fclose(file);
}

char *get_code_line(source_code_t *source_code) {
    if (source_code->act_line_number >= source_code->number_of_lines) {
        throw_error(READ_FROM_END_OF_FILE, 0);
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

void skip_empty_lines(source_code_t *source_code) {
    char *act_line = get_code_line(source_code);
    act_line = skip_whitespace(act_line);
    while (are_lines_to_read(source_code) && *act_line == '\0') {
        move_to_next_line(source_code);
        act_line = get_code_line(source_code);
        act_line = skip_whitespace(act_line);
    }
}

