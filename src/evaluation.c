#include "evaluation.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"
#include "error_manager.h"


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


char *skip_whitespace(char *source) {
    while (*source != '\0' && isspace(*source)) {
        source++;
    }

    return source;
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

    return result;
}


bool equal(char *string_a, char *string_b) {
    return strcmp(string_a, string_b) == 0;
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
    } else {
        *word = *source;
        source++, word++;
    }

    source = skip_whitespace(source);

    *word = '\0';

    return source;
}


bool end_of_string(const char *string) {
    return *string == '\0';
}


int insert_new_lexical_unit_to_ONP(char *destination, char *source, size_t index) {
    while (!end_of_string(source)) {
        *(destination + index) = *source;
        source++;
        index++;
    }

    *(destination + index) = ONP_SEPARATOR;
    index++;

    return index;
}


void expression_to_ONP(char *expression, char *ONP) {
    stack_t stack = create_stack();
    char lexical_unit[LINE_LENGTH];
    lexical_unit_t type_of_lexical_unit = NOT_A_LEXICAL_UNIT;
    size_t index_of_ONP = 0;

    while (!end_of_string(expression)) {
        expression = read_lexical_unit(expression, lexical_unit);
        type_of_lexical_unit = detect_to_which_lexical_unit_string_belongs(lexical_unit);

        if (type_of_lexical_unit == NUMBER || type_of_lexical_unit == VARIABLE)
            index_of_ONP = insert_new_lexical_unit_to_ONP(ONP, lexical_unit, index_of_ONP);

        else if (type_of_lexical_unit == OPERATOR) {
            while (!is_empty(stack) && get_operator_priority(get_top(stack)) >= get_operator_priority(lexical_unit)) {
                char act_val[LINE_LENGTH];
                stack = pop(stack, act_val);
                index_of_ONP = insert_new_lexical_unit_to_ONP(ONP, act_val, index_of_ONP);
            }
            stack = push(stack, lexical_unit);

        } else if (type_of_lexical_unit == OPENING_BRACKET) {
            stack = push(stack, "(");
        } else if (type_of_lexical_unit == CLOSING_BRACKET) {
            char act_val[LINE_LENGTH];


            while (!is_empty(stack) && !equal(get_top(stack), "(")) {
                stack = pop(stack, act_val);
                index_of_ONP = insert_new_lexical_unit_to_ONP(ONP, act_val, index_of_ONP);
            }

            stack = pop(stack, act_val);

        } else {
            printf("error in expression!!\n");
        }
    }

    while (!is_empty(stack)) {
        char act_val[LINE_LENGTH];

        stack = pop(stack, act_val);
        if (detect_to_which_lexical_unit_string_belongs(act_val) != OPENING_BRACKET)
            index_of_ONP = insert_new_lexical_unit_to_ONP(ONP, act_val, index_of_ONP);
    }

    if (index_of_ONP > 0)
        *(ONP + index_of_ONP - 1) = '\0';
    else
        *ONP = '\0';
}