#include "parser.h"
#include "source_code_reader.h"
#include "string_operations.h"
#include "variable_register.h"



void load_defined_variables(source_code_t *source_code, variable_register_t variable_register) {
    skip_empty_lines(source_code);

    if (!are_lines_to_read(source_code)) {
        // TODO: handling when file is empty
    }

    char *act_line = get_code_line(source_code);
    char word[LINE_LENGTH];
    act_line = read_first_word_after_whitespace(act_line, word);

    if (!equal(word, "define:")) {
        // TODO: handling when there is no define clasule
    }

    // TODO: handling when there is word after define clasule

    move_to_next_line(source_code);
    skip_empty_lines(source_code);
    read_first_word_after_whitespace(get_code_line(source_code), word);

    while (are_lines_to_read(source_code) && !equal("program:", word)) {
        load_variable(source_code, variable_register);

        move_to_next_line(source_code);
        skip_empty_lines(source_code);
        // TODO: handling end of file
        read_first_word_after_whitespace(get_code_line(source_code), word);
    }

    // TODO: handling when there is word after program clausule

    move_to_next_line(source_code);
    skip_empty_lines(source_code);
}

void load_variable(source_code_t *source_code, variable_register_t variable_register) {
    char *act_line = get_code_line(source_code);
    char word[LINE_LENGTH];
    act_line = read_first_word_after_whitespace(act_line, word);
    variable_type_t variable_type = detect_variable_type(word);

    if (variable_type == NOT_A_TYPE) {
        // TODO: handling bad type name
    }

    act_line = read_first_word_after_whitespace(act_line, word);

    variable_register = define_variable(variable_register, word);
}

void parse_program(source_code_t *source_code) {
    ;
}