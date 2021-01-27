#include <string.h>
#include "parser.h"
#include "source_code_reader.h"
#include "string_operations.h"
#include "variable_register.h"
#include "instruction.h"


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

void add_with_respect_if(instruction_tree_t upper_instruction, instruction_tree_t instruction, bool is_in_true) {
    if (is_in_true)
        upper_instruction->instruction_if_true = insert_instruction(upper_instruction->instruction_if_true,
                                                                    instruction);
    else
        upper_instruction->instruction_if_false = insert_instruction(
                upper_instruction->instruction_if_false,
                instruction);
}

instruction_tree_t parse_program(source_code_t *source_code) {
    instruction_tree_t upper_instruction = create_instruction(START_PROGRAM, NULL, "");
    instruction_tree_t root = upper_instruction;
    char *line;
    while (are_lines_to_read(source_code)) {
        skip_empty_lines(source_code);
        char word[LINE_LENGTH];
        line = get_code_line(source_code);
        line = read_first_word_after_whitespace(line, word);
        upper_instruction->instruction_if_true;
        type_of_instruction_t type_of_instruction = detect_type_of_instruction(word);
        switch (type_of_instruction) {
            case ASSIGN: {
                char variable_name[LINE_LENGTH];
                strcpy(variable_name, word);
                line = read_first_word_after_whitespace(line, word);

                if (!equal(word, "=")) {
                    // TODO: handling when bad assigment expression is used
                }

                instruction_tree_t instruction = create_instruction_assignment(ASSIGN, upper_instruction, variable_name,
                                                                               line);
                add_with_respect_if(upper_instruction, instruction, upper_instruction->in_instruction_if_true);

            }
                break;
            case IF: {
                instruction_tree_t instruction = create_instruction(IF, upper_instruction, line);
                add_with_respect_if(upper_instruction, instruction, upper_instruction->in_instruction_if_true);
                upper_instruction = instruction;
            }
                break;

            case ELSE: {
                upper_instruction->in_instruction_if_true = false;
            }
                break;

            case END: {
                upper_instruction = upper_instruction->upper_instruction;
            }
                break;

            case WHILE: {
                instruction_tree_t instruction = create_instruction(WHILE, upper_instruction, line);
                add_with_respect_if(upper_instruction, instruction, upper_instruction->in_instruction_if_true);
                upper_instruction = instruction;
            }
                break;

            case PRINT_VARIABLE:
            case PRINT_STRING: {
                instruction_tree_t instruction = create_instruction(type_of_instruction, upper_instruction, line);
                add_with_respect_if(upper_instruction, instruction, upper_instruction->in_instruction_if_true);
            }

        }

        move_to_next_line(source_code);
    }

    return root;
}