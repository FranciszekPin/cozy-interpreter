#include <string.h>
#include "parser.h"


bool are_remain_characters(char *line) {
    return (*line != '\n' && *line != '\0');
}

bool is_define_clause(line_str_t word) {
    return equal(word, "define:");
}

bool is_program_clause(line_str_t word) {
    return equal(word, "program:");
}

char *read_first_word_skipping_empty_lines(instruction_tree_t instruction_tree, variable_register_t variable_register,
                                           source_code_t *source_code, line_str_t word) {
    skip_empty_lines(source_code, instruction_tree, variable_register);
    char *result = read_first_word_after_whitespace(get_act_code_line(source_code, instruction_tree, variable_register),
                                                    word);
    return result;
}

void load_defined_variables(source_code_t *source_code, variable_register_t variable_register,
                            instruction_tree_t instruction_tree) {
    line_str_t word;
    char *act_line = NULL;
    if (are_lines_to_read(source_code))
        act_line = read_first_word_skipping_empty_lines(instruction_tree, variable_register, source_code, word);

    if (!are_lines_to_read(source_code)) {
        throw_error(EMPTY_FILE, get_act_line_number(source_code) + 1, instruction_tree, variable_register);
    }

    if (!is_define_clause(word)) {
        if (!is_program_clause(word))
            throw_error(NO_PROGRAM_CLAUSE, get_act_line_number(source_code) + 1, instruction_tree, variable_register);
        go_to_next_line(source_code);

    } else {
        if (are_remain_characters(act_line)) {
            throw_error(NO_NEW_LINE_AFTER_CLAUSE, get_act_line_number(source_code) + 1, instruction_tree,
                        variable_register);
        }

        go_to_next_line(source_code);
        if (are_lines_to_read(source_code)) {
            read_first_word_skipping_empty_lines(instruction_tree, variable_register, source_code, word);
        }

        while (are_lines_to_read(source_code) && !is_program_clause(word)) {
            load_variable(source_code, variable_register, instruction_tree);

            go_to_next_line(source_code);

            if (are_lines_to_read(source_code)) {
                read_first_word_skipping_empty_lines(instruction_tree, variable_register, source_code, word);
            }
        }

        if (are_lines_to_read(source_code)) {
            act_line = read_first_word_after_whitespace(
                    get_act_code_line(source_code, instruction_tree, variable_register), word);
            if (is_program_clause(word) && are_remain_characters(act_line))
                throw_error(NO_NEW_LINE_AFTER_CLAUSE, get_act_line_number(source_code) + 1, instruction_tree,
                            variable_register);

        }

        go_to_next_line(source_code);
        if (are_lines_to_read(source_code))
            skip_empty_lines(source_code, instruction_tree, variable_register);
    }
}

void
load_variable(source_code_t *source_code, variable_register_t variable_register, instruction_tree_t instruction_tree) {
    char *act_line = get_act_code_line(source_code, instruction_tree, variable_register);
    char word[LINE_LENGTH];
    act_line = read_first_word_after_whitespace(act_line, word);
    variable_type_t variable_type = detect_variable_type(word);

    if (variable_type == NOT_A_TYPE) {
        throw_error(WRONG_VARIABLE_TYPE_NAME, get_act_line_number(source_code) + 1, instruction_tree,
                    variable_register);
    }

    act_line = read_first_word_after_whitespace(act_line, word);

    if (is_variable_name_forbidden(word))
        throw_error(ILLEGAL_VARIABLE_NAME, get_act_line_number(source_code) + 1, instruction_tree, variable_register);

    variable_register = define_variable(variable_register, word, get_act_line_number(source_code) + 1,
                                        instruction_tree);
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

instruction_tree_t
parse_program(source_code_t *source_code, instruction_tree_t instruction_tree, variable_register_t variable_register) {
    instruction_tree_t upper_instruction = create_instruction(START_PROGRAM, NULL, "", 0);
    instruction_tree_t root = upper_instruction;

    instruction_stack_t instruction_stack = create_instruction_stack();

    char *line;
    if (are_lines_to_read(source_code))
        skip_empty_lines(source_code, instruction_tree, variable_register);
    while (are_lines_to_read(source_code)) {
        line_str_t word;
        line = get_act_code_line(source_code, instruction_tree, variable_register);
        line = read_first_word_after_whitespace(line, word);
        upper_instruction->instruction_if_true;
        type_of_instruction_t type_of_instruction = detect_type_of_instruction(word);
        switch (type_of_instruction) {
            case ASSIGN: {
                char variable_name[LINE_LENGTH];
                strcpy(variable_name, word);
                line = read_first_word_after_whitespace(line, word);

                if (!equal(word, "=")) {
                    throw_error(WRONG_ASSIGNMENT_EXPRESSION, get_act_line_number(source_code) + 1, instruction_tree,
                                variable_register);
                }
                line_str_t ONP;
                expression_to_ONP(line, ONP, get_act_line_number(source_code) + 1, instruction_tree, variable_register);
                instruction_tree_t instruction = create_instruction_assignment(ASSIGN, upper_instruction, variable_name,
                                                                               ONP,
                                                                               get_act_line_number(source_code) + 1);
                add_with_respect_if(upper_instruction, instruction, upper_instruction->in_instruction_if_true);

            }
                break;
            case IF: {
                line_str_t ONP;
                expression_to_ONP(line, ONP, get_act_line_number(source_code) + 1, instruction_tree, variable_register);
                instruction_tree_t instruction = create_instruction(IF, upper_instruction, ONP,
                                                                    get_act_line_number(source_code) + 1);
                add_with_respect_if(upper_instruction, instruction, upper_instruction->in_instruction_if_true);
                upper_instruction = instruction;
                instruction_stack = instruction_stack_push(instruction_stack, IF);
            }
                break;

            case ELSE: {
                if (instruction_stuck_is_empty(instruction_stack) ||
                    instruction_stuck_get_top(instruction_stack) != IF) {
                    instruction_stack = instruction_stack_clear(instruction_stack);
                    throw_error(WRONG_PROGRAM_STRUCTURE, get_act_line_number(source_code) + 1, instruction_tree,
                                variable_register);
                }

                instruction_stack = instruction_stuck_pop(instruction_stack);
                instruction_stack = instruction_stack_push(instruction_stack, ELSE);

                upper_instruction->in_instruction_if_true = false;
            }
                break;

            case END: {
                upper_instruction = upper_instruction->upper_instruction;
                if (instruction_stuck_is_empty(instruction_stack)) {
                    throw_error(WRONG_PROGRAM_STRUCTURE, get_act_line_number(source_code) + 1, instruction_tree,
                                variable_register);
                }

                instruction_stack = instruction_stuck_pop(instruction_stack);
            }
                break;

            case WHILE: {
                line_str_t ONP;
                expression_to_ONP(line, ONP, get_act_line_number(source_code) + 1, instruction_tree, variable_register);
                instruction_tree_t instruction = create_instruction(WHILE, upper_instruction, ONP,
                                                                    get_act_line_number(source_code) + 1);
                add_with_respect_if(upper_instruction, instruction, upper_instruction->in_instruction_if_true);
                upper_instruction = instruction;
                instruction_stack = instruction_stack_push(instruction_stack, WHILE);
            }
                break;

            case PRINT_VARIABLE: {
                line_str_t ONP;
                expression_to_ONP(line, ONP, get_act_line_number(source_code) + 1, instruction_tree, variable_register);
                instruction_tree_t instruction = create_instruction(type_of_instruction, upper_instruction, ONP,
                                                                    get_act_line_number(source_code) + 1);
                add_with_respect_if(upper_instruction, instruction, upper_instruction->in_instruction_if_true);
            }
                break;

            case PRINT_STRING: {
                instruction_tree_t instruction = create_instruction(type_of_instruction, upper_instruction, line,
                                                                    get_act_line_number(source_code) + 1);
                add_with_respect_if(upper_instruction, instruction, upper_instruction->in_instruction_if_true);
            }
                break;


            case READ: {
                line_str_t ONP;
                expression_to_ONP(line, ONP, get_act_line_number(source_code) + 1, instruction_tree, variable_register);
                instruction_tree_t instruction = create_instruction(READ, upper_instruction, ONP,
                                                                    get_act_line_number(source_code) + 1);
                add_with_respect_if(upper_instruction, instruction, upper_instruction->in_instruction_if_true);
            }
                break;

            default: {
                throw_error(UNKNOWN_INSTRUCTION_TYPE, -1, instruction_tree, variable_register);
            }
        }

        go_to_next_line(source_code);
        if (are_lines_to_read(source_code))
            skip_empty_lines(source_code, instruction_tree, variable_register);
    }

    if (!instruction_stuck_is_empty(instruction_stack)) {
        instruction_stack_clear(instruction_stack);
        throw_error(WRONG_PROGRAM_STRUCTURE, get_act_line_number(source_code) + 1, instruction_tree, variable_register);
    }

    return root;
}