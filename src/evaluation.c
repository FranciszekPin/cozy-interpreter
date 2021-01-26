#include "evaluation.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"
#include "error_manager.h"
#include "string_operations.h"


Operation choose_proper_operation(char operator) {
    Operation result = NOT_DEFINED;
    switch (operator) {
        case '*':
            result = MULTIPLY;
            break;
        case '+':
            result = ADD;
            break;
        case '/':
            result = DIVIDE;
            break;
        case '-':
            result = SUBTRACT;
            break;
        default:
            result = NOT_DEFINED;
    }

    return result;
}


bool is_bracket(char c) {
    return (c == '(') || (c == ')');
}


int get_operator_priority(char *operator) {
    int result = -1;

    if (strcmp(operator, "*") == 0 || strcmp(operator, "/") == 0 || strcmp(operator, "%") == 0)
        result = 10;
    else if (strcmp(operator, "+") == 0 || strcmp(operator, "-") == 0)
        result = 9;
    else if (strcmp(operator, ">") == 0 || strcmp(operator, ">=") == 0 || strcmp(operator, "<") == 0 ||
             strcmp(operator, "<=") == 0)
        result = 8;
    else if (strcmp(operator, "==") == 0 || strcmp(operator, "!=") == 0)
        result = 7;
    else if (strcmp(operator, "&&") == 0)
        result = 6;
    else if (strcmp(operator, "||") == 0)
        result = 5;
    else
        result = -1;

    return result;
}


bool is_operator(char operator) {
    return operator == '+' || operator == '*';
}


lexical_unit_t detect_to_which_lexical_unit_string_belongs(char *lexical_unit) {
    char first_character = *lexical_unit;
    if ((first_character >= 'a' && first_character <= 'z') || (first_character >= 'A' && first_character <= 'Z'))
        return VARIABLE;

    if (first_character >= '0' && first_character <= '9')
        return NUMBER;

    if (first_character == '=' || first_character == '<' || first_character == '>' || first_character == '!' ||
        first_character == '+' || first_character == '-' || first_character == '*' || first_character == '/' ||
        first_character == '|' || first_character == '&')
        return OPERATOR;

    if (first_character == '(')
        return OPENING_BRACKET;

    if (first_character == ')')
        return CLOSING_BRACKET;

    return NOT_A_LEXICAL_UNIT;
}


char *read_lexical_unit(char *source, char *word) {
    source = skip_whitespace(source);

    lexical_unit_t act_lexical_unit = detect_to_which_lexical_unit_string_belongs(source);

    if (act_lexical_unit == VARIABLE || act_lexical_unit == NUMBER || act_lexical_unit == OPERATOR) {
        while (*source != '\0' && detect_to_which_lexical_unit_string_belongs(source) == act_lexical_unit) {
            *word = *source;
            source++, word++;
        }
    } else if (act_lexical_unit == OPENING_BRACKET || act_lexical_unit == CLOSING_BRACKET) {
        *word = *source;
        source++, word++;
    } else {
        source++;
        throw_error(ILLEGAL_CHARACTER_USAGE);
    }

    source = skip_whitespace(source);

    *word = '\0';

    return source;
}


bool end_of_string(const char *string) {
    return *string == '\0';
}


int insert_new_lexical_unit_to_string(char *destination, char *source, size_t index) {
    while (!end_of_string(source)) {
        *(destination + index) = *source;
        source++;
        index++;
    }

    *(destination + index) = ONP_SEPARATOR;
    index++;

    return index;
}

void convert_expression_to_separated_form(char *destination, char *expression) {
    char lexical_unit[LINE_LENGTH];
    size_t index_of_destination = 0;
    while (!end_of_string(expression)) {
        expression = read_lexical_unit(expression, lexical_unit);
        index_of_destination = insert_new_lexical_unit_to_string(destination, lexical_unit, index_of_destination);
    }

    if (index_of_destination > 0) {
        *(destination + index_of_destination - 1) = '\0';
    } else {
        *destination = '\0';
    }
}

error_t check_if_lexical_unit_is_correct(char *lexical_unit) {
    lexical_unit_t type_of_lexical_unit = detect_to_which_lexical_unit_string_belongs(lexical_unit);

    error_t result = NO_ERROR;

    switch (type_of_lexical_unit) {
        case NUMBER:
        case VARIABLE:
        case OPENING_BRACKET:
        case CLOSING_BRACKET:
            result = NO_ERROR;
            break;
        case OPERATOR: {
            if (get_operator_priority(lexical_unit) >= 0)
                result = NO_ERROR;
            else
                result = WRONG_OPERATOR_USAGE;
        }
            break;
        case NOT_A_LEXICAL_UNIT:
            result = ILLEGAL_CHARACTER_USAGE;
            break;
        default:
            printf("Zly typ L_T\n");
            break;
    }

    return result;
}

error_t check_if_separated_form_is_correct(char *separated_form) {
    error_t result = NO_ERROR;

    char prev_lexical_unit[LINE_LENGTH];
    char act_lexical_unit[LINE_LENGTH];
    char next_lexical_unit[LINE_LENGTH];

    prev_lexical_unit[0] = '\0';
    separated_form = read_word(separated_form, act_lexical_unit);
    if (!end_of_string(separated_form)) {
        separated_form = read_word(separated_form, next_lexical_unit);

        error_t potential_error;
        lexical_unit_t type_of_lexical_unit;
        while (!end_of_string(act_lexical_unit)) {
            potential_error = check_if_lexical_unit_is_correct(act_lexical_unit);
            if (potential_error != NO_ERROR) {
                result = potential_error;
                break;
            }

            type_of_lexical_unit = detect_to_which_lexical_unit_string_belongs(act_lexical_unit);
            switch (type_of_lexical_unit) {
                case NUMBER:
                case VARIABLE:
                case OPERATOR: {
                    if (*prev_lexical_unit != '\0' &&
                        detect_to_which_lexical_unit_string_belongs(prev_lexical_unit) == type_of_lexical_unit) {
                        result = ILLEGAL_EXPRESSION_FORM;
                        break;
                    }
                    if (*next_lexical_unit != '\0' &&
                        detect_to_which_lexical_unit_string_belongs(next_lexical_unit) == type_of_lexical_unit) {
                        result = ILLEGAL_EXPRESSION_FORM;
                        break;
                    }
                }
                    break;
                case OPENING_BRACKET: {
                    if (*prev_lexical_unit != '\0' &&
                        (detect_to_which_lexical_unit_string_belongs(prev_lexical_unit) == VARIABLE ||
                         detect_to_which_lexical_unit_string_belongs(prev_lexical_unit) == NUMBER)) {
                        result = ILLEGAL_EXPRESSION_FORM;
                        break;
                    }

                    if (*next_lexical_unit != '\0' &&
                        detect_to_which_lexical_unit_string_belongs(next_lexical_unit) == OPERATOR) {
                        result = ILLEGAL_EXPRESSION_FORM;
                        break;
                    }
                }
                    break;

                case CLOSING_BRACKET: {
                    if (*prev_lexical_unit != '\0' &&
                        detect_to_which_lexical_unit_string_belongs(prev_lexical_unit) == OPERATOR) {
                        result = ILLEGAL_EXPRESSION_FORM;
                        break;
                    }

                    if (*next_lexical_unit != '\0' &&
                        (detect_to_which_lexical_unit_string_belongs(next_lexical_unit) == VARIABLE ||
                         detect_to_which_lexical_unit_string_belongs(next_lexical_unit) == NUMBER)) {
                        result = ILLEGAL_EXPRESSION_FORM;
                        break;
                    }
                }
                    break;

                case NOT_A_LEXICAL_UNIT:
                    printf("cos poszlo nie tak...\n");
                    break;
            }

            strcpy(prev_lexical_unit, act_lexical_unit);
            strcpy(act_lexical_unit, next_lexical_unit);
            separated_form = read_word(separated_form, next_lexical_unit);

        }
    } else {
        result = check_if_lexical_unit_is_correct(act_lexical_unit);
    }

    return result;
}


void separated_form_to_ONP(char *separated_form, char *ONP) {
    stack_t stack = create_stack();
    char lexical_unit[LINE_LENGTH];
    lexical_unit_t type_of_lexical_unit = NOT_A_LEXICAL_UNIT;
    size_t index_of_ONP = 0;

    while (!end_of_string(separated_form)) {
        separated_form = read_word(separated_form, lexical_unit);
        type_of_lexical_unit = detect_to_which_lexical_unit_string_belongs(lexical_unit);

        if (type_of_lexical_unit == NUMBER || type_of_lexical_unit == VARIABLE)
            index_of_ONP = insert_new_lexical_unit_to_string(ONP, lexical_unit, index_of_ONP);

        else if (type_of_lexical_unit == OPERATOR) {
            while (!is_empty(stack) && get_operator_priority(get_top(stack)) >= get_operator_priority(lexical_unit)) {
                char act_val[LINE_LENGTH];
                stack = pop(stack, act_val);
                index_of_ONP = insert_new_lexical_unit_to_string(ONP, act_val, index_of_ONP);
            }
            stack = push(stack, lexical_unit);

        } else if (type_of_lexical_unit == OPENING_BRACKET) {
            stack = push(stack, "(");
        } else if (type_of_lexical_unit == CLOSING_BRACKET) {
            char act_val[LINE_LENGTH];


            while (!is_empty(stack) && !equal(get_top(stack), "(")) {
                stack = pop(stack, act_val);
                index_of_ONP = insert_new_lexical_unit_to_string(ONP, act_val, index_of_ONP);
            }

            stack = pop(stack, act_val);

        } else {
            printf("error in separated_form!!\n");
        }
    }

    while (!is_empty(stack)) {
        char act_val[LINE_LENGTH];

        stack = pop(stack, act_val);
        if (detect_to_which_lexical_unit_string_belongs(act_val) != OPENING_BRACKET)
            index_of_ONP = insert_new_lexical_unit_to_string(ONP, act_val, index_of_ONP);
    }

    if (index_of_ONP > 0)
        *(ONP + index_of_ONP - 1) = '\0';
    else
        *ONP = '\0';
}

int evaluate_operator(char *operator, int operand_a, int operand_b) {
    int result = 0;
    if (strcmp(operator, "*") == 0)
        result = operand_a * operand_b;
    else if (strcmp(operator, "/") == 0)
        result = operand_a / operand_b;
    else if (strcmp(operator, "%") == 0)
        result = operand_a % operand_b;
    else if (strcmp(operator, "+") == 0)
        result = operand_a + operand_b;
    else if (strcmp(operator, "-") == 0)
        result = operand_a - operand_b;
    else if (strcmp(operator, ">") == 0)
        result = operand_a > operand_b;
    else if (strcmp(operator, ">=") == 0)
        result = operand_a >= operand_b;
    else if (strcmp(operator, "<") == 0)
        result = operand_a < operand_b;
    else if (strcmp(operator, "<=") == 0)
        result = operand_a <= operand_b;
    else if (strcmp(operator, "==") == 0)
        result = operand_a == operand_b;
    else if (strcmp(operator, "!=") == 0)
        result = operand_a != operand_b;
    else if (strcmp(operator, "&&") == 0)
        result = operand_a && operand_b;
    else if (strcmp(operator, "||") == 0)
        result = operand_a || operand_b;

    return result;
}

int evaluate_number(char *unit) {
    return atoi(unit);
}

int evaluate_variable(char *unit) {
    return 1;
}

int calculate_ONP_val(char *ONP_expression) {
    stack_t stack = create_stack();
    char lexical_unit[LINE_LENGTH];
    lexical_unit_t type_of_lexical_unit = NOT_A_LEXICAL_UNIT;
    size_t index_of_ONP = 0;

    while (!end_of_string(ONP_expression)) {
        ONP_expression = read_word(ONP_expression, lexical_unit);
        type_of_lexical_unit = detect_to_which_lexical_unit_string_belongs(lexical_unit);

        if (type_of_lexical_unit != OPERATOR)
            stack = push(stack, lexical_unit);
        else {
            char operand1[LINE_LENGTH];
            char operand2[LINE_LENGTH];
            stack = pop(stack, operand2);
            stack = pop(stack, operand1);

            int operand1_val;
            int operand2_val;

            lexical_unit_t operand1_type = detect_to_which_lexical_unit_string_belongs(operand1);
            if (operand1_type == VARIABLE)
                operand1_val = evaluate_variable(operand1);
            else
                operand1_val = evaluate_number(operand1);

            lexical_unit_t operand2_type = detect_to_which_lexical_unit_string_belongs(operand2);
            if (operand2_type == VARIABLE)
                operand2_val = evaluate_variable(operand2);
            else
                operand2_val = evaluate_number(operand2);
            int result = evaluate_operator(lexical_unit, operand1_val, operand2_val);

            char result_as_string[LINE_LENGTH];
            sprintf(result_as_string, "%d", result);
            stack = push(stack, result_as_string);
        }
    }
    char result_as_string[LINE_LENGTH];
    stack = pop(stack, result_as_string);
    int result;
    lexical_unit_t result_unit_type = detect_to_which_lexical_unit_string_belongs(result_as_string);
    if (result_unit_type == VARIABLE)
        result = evaluate_variable(result_as_string);
    else
        result = evaluate_number(result_as_string);

    return result;
}

int evaluate_expression(char *expression) {
    char separated_form[LINE_LENGTH];
    convert_expression_to_separated_form(separated_form, expression);

    int result = 0;
    error_t potential_error = check_if_separated_form_is_correct(separated_form);
    if (potential_error == NO_ERROR) {
        char ONP[LINE_LENGTH];
        separated_form_to_ONP(separated_form, ONP);
        result = calculate_ONP_val(ONP);
    }
    else {
        throw_error(potential_error);
    }

    return result;
}