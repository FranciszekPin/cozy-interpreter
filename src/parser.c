#include <string.h>
#include "parser.h"
#include "source_code_reader.h"
#include "string_operations.h"
#include "variable_register.h"
#include "instruction.h"
#include "evaluation.h"


void load_defined_variables(source_code_t *source_code, variable_register_t variable_register) {
    skip_empty_lines(source_code);

    if (!are_lines_to_read(source_code)) {
        throw_error(EMPTY_FILE, get_act_line_number(source_code)+1);
    }

    char *act_line = get_code_line(source_code);
    char word[LINE_LENGTH];
    act_line = read_first_word_after_whitespace(act_line, word);

    if (!equal(word, "define:")) {
        if (!equal(word, "program:"))
            throw_error(NO_PROGRAM_CLAUSE, get_act_line_number(source_code)+1);
        move_to_next_line(source_code);
        return;
    }

    if (*act_line != '\n') {
        throw_error(NO_NEW_LINE_AFTER_CLAUSE, get_act_line_number(source_code)+1);
    }

    move_to_next_line(source_code);
    skip_empty_lines(source_code);
    read_first_word_after_whitespace(get_code_line(source_code), word);

    while (are_lines_to_read(source_code) && !equal("program:", word)) {
        load_variable(source_code, variable_register);

        move_to_next_line(source_code);
        skip_empty_lines(source_code);

        if (are_lines_to_read(source_code))
            read_first_word_after_whitespace(get_code_line(source_code), word);
    }

    act_line = read_first_word_after_whitespace(get_code_line(source_code), word);
    if (equal("program:", word) && *act_line != '\n') {
        throw_error(NO_NEW_LINE_AFTER_CLAUSE, get_act_line_number(source_code)+1);

    }

    move_to_next_line(source_code);
    skip_empty_lines(source_code);
}

void load_variable(source_code_t *source_code, variable_register_t variable_register) {
    char *act_line = get_code_line(source_code);
    char word[LINE_LENGTH];
    act_line = read_first_word_after_whitespace(act_line, word);
    variable_type_t variable_type = detect_variable_type(word);

    if (variable_type == NOT_A_TYPE) {
        throw_error(WRONG_VARIABLE_TYPE_NAME, get_act_line_number(source_code)+1);
    }

    act_line = read_first_word_after_whitespace(act_line, word);

    variable_register = define_variable(variable_register, word, get_act_line_number(source_code)+1);
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
    instruction_tree_t upper_instruction = create_instruction(START_PROGRAM, NULL, "", 0);
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
                    throw_error(WRONG_ASSIGNMENT_EXPRESSION, get_act_line_number(source_code)+1);
                }
                char ONP[LINE_LENGTH];
                expression_to_ONP(line, ONP, get_act_line_number(source_code)+1);
                instruction_tree_t instruction = create_instruction_assignment(ASSIGN, upper_instruction, variable_name,
                                                                               ONP, get_act_line_number(source_code)+1);
                add_with_respect_if(upper_instruction, instruction, upper_instruction->in_instruction_if_true);

            }
                break;
            case IF: {
                char ONP[LINE_LENGTH];
                expression_to_ONP(line, ONP, get_act_line_number(source_code)+1);
                instruction_tree_t instruction = create_instruction(IF, upper_instruction, ONP, get_act_line_number(source_code)+1);
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
                char ONP[LINE_LENGTH];
                expression_to_ONP(line, ONP, get_act_line_number(source_code)+1);
                instruction_tree_t instruction = create_instruction(WHILE, upper_instruction, ONP, get_act_line_number(source_code)+1);
                add_with_respect_if(upper_instruction, instruction, upper_instruction->in_instruction_if_true);
                upper_instruction = instruction;
            }
                break;

            case PRINT_VARIABLE:
            case PRINT_STRING: {
                char ONP[LINE_LENGTH];
                expression_to_ONP(line, ONP, get_act_line_number(source_code)+1);
                instruction_tree_t instruction = create_instruction(type_of_instruction, upper_instruction, ONP, get_act_line_number(source_code)+1);
                add_with_respect_if(upper_instruction, instruction, upper_instruction->in_instruction_if_true);
            }
                break;


            case READ: {
                char ONP[LINE_LENGTH];
                expression_to_ONP(line, ONP, get_act_line_number(source_code)+1);
                instruction_tree_t instruction = create_instruction(READ, upper_instruction, ONP, get_act_line_number(source_code)+1);
                add_with_respect_if(upper_instruction, instruction, upper_instruction->in_instruction_if_true);
            }
                break;

            default: {
                throw_error(UNKNOWN_INSTRUCTION_TYPE, -1);
            }
        }

        move_to_next_line(source_code);
    }

    return root;
}