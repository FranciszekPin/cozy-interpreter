#include "evaluation.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"

char * readNumber(char *expression, int* number) {
    int read_number = 0;
    bool is_negative = false;

    if (*expression == '-') {
        is_negative = true;
        expression++;
    }

    if (!isdigit(*expression)) {
        return NULL;
    }

    while (isdigit(*expression)) {
        read_number = read_number*10 + (*expression - '0');
        expression++;
    }

    if (is_negative)
        read_number *= -1;

    *number = read_number;

    return expression;
}

bool brackets_are_correct(char *expression) {
    int number_of_opening_brackets = 0;
    int number_of_closing_brackets = 0;

    while (*expression != '\0') {
        char act = *expression;

        if (act == '(')
            number_of_opening_brackets++;
        else if (act == ')') {
            number_of_closing_brackets++;
            if (number_of_closing_brackets > number_of_opening_brackets)
                return false;
        }
        expression++;
    }

    return number_of_opening_brackets == number_of_closing_brackets;
}

void remove_character_from_end(char *expression) {
    int i = 0;
    while (expression[i] != '\0')
        i++;
    expression[i - 1] = '\0';
}

bool are_unnecessary_brackets(char *expression) {
    bool result = false;
    if (*expression == '(') {
        char expression_copy[100];
        strcpy(expression_copy, expression);
        char *test_expression = expression + 1;

        remove_character_from_end(test_expression);

        result = brackets_are_correct(test_expression);
        strcpy(expression, expression_copy);
    }

    return result;
}

void remove_unnecessary_brackets(char *expression) {
    while (are_unnecessary_brackets(expression)) {
        int i=0;
        while (expression[i] != '\0') {
            expression[i] = expression[i+1];
            i++;
        }
        expression[i-2] = '\0';
    }
}

char *find_first_operation(char *expression) {
    int number_of_opening_brackets = 0;
    int number_of_closing_brackets = 0;

    char *result = NULL;

    while (*expression != '\0') {
        char act = *expression;

        if (act == '(')
            number_of_opening_brackets++;
        else if (act == ')')
            number_of_closing_brackets++;
        else {
            if (number_of_opening_brackets == number_of_closing_brackets) {
                if ((act == '+' || act == '-') && result == NULL) {
                    result = expression;
                } else if ((act == '*' || act == '/') && (result == NULL || *result == '+' || *result == '-')) {
                    result = expression;
                }
            }
        }

        expression++;
    }

    return result;
}

Operation choose_proper_operation(char operator) {
    Operation result = NOT_DEFINED;
    switch (operator) {
        case '*': result = MULTIPLY; break;
        case '+': result = ADD; break;
        case '/': result = DIVIDE; break;
        case '-': result = SUBTRACT; break;
        default: result = NOT_DEFINED;
    }

    return result;
}

void copy_string(char *dest, char* begin, char *end) {
    int i=0;
    while (begin != end && *begin != '\0') {
        dest[i] = *begin;
        begin++;
        i++;
    }

    dest[i] = '\0';
}

tree_node * parse(char *expression) {
    remove_unnecessary_brackets(expression);

    tree_node *result;
    char *first_operation = find_first_operation(expression);
    if (first_operation != NULL) {
        Operation act_operation = choose_proper_operation(*first_operation);

        create_new_node_operation(&result, act_operation);

        char left[100];
        char right[100];

        copy_string(left, expression, first_operation);
        copy_string(right, first_operation+1, NULL);

        result->left = parse(left);
        result->right = parse(right);
    }
    else
        create_new_node_value(&result, expression);

    return result;
}

char *skip_whitespace(char *source) {
    while (*source != '\0' && isspace(*source)) {
        source++;
    }

    return source;
}

char * read_word(char *source, char *word) {
    source = skip_whitespace(source);

    while (*source != '\0' && !isspace(*source)) {
        *word = *source;
        source++, word++;
    }

    *word = '\0';

    return source;
}

bool is_bracket(char c) {
    return (c == '(') || (c == ')');
}

int get_operator_priority(char *operator) {
    int result = -1;

    if (strcmp(operator, "*") == 0 || strcmp(operator, "/") == 0  || strcmp(operator, "%") == 0)
        result = 10;
    else if (strcmp(operator, "+") == 0 || strcmp(operator, "-") == 0)
        result = 9;
    else if (strcmp(operator, ">") == 0 || strcmp(operator, ">=") == 0  || strcmp(operator, "<") == 0 || strcmp(operator, "<=") == 0)
        result = 8;
    else if (strcmp(operator, "==") == 0 || strcmp(operator, "!=") == 0)
        result = 7;
    else if (strcmp(operator, "&&") == 0 )
        result = 6;
    else if (strcmp(operator, "||") == 0 )
        result = 5;

    return result;
}

bool equal(char *string_a, char *string_b) {
    return strcmp(string_a, string_b) == 0;
}

bool is_operator(char operator) {
    return operator == '+' || operator == '*';
}

lexical_unit_t detect_to_which_lexical_unit_character_belongs(char c) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return VARIABLE;

    if (c >= '0' && c <= '9')
        return NUMBER;

    if (get_operator_priority(c) != -1)
        return OPERATOR;

    if (c == '(')
        return OPENING_BRACKET;

    if (c == ')')
        return CLOSING_BRACKET;

    return NOT_A_LEXICAL_UNIT;
}

char *read_lexical_unit(char *source, char *word) {
    source = skip_whitespace(source);

    lexical_unit_t act_lexical_unit = detect_to_which_lexical_unit_character_belongs(*source);

    if (act_lexical_unit == VARIABLE || act_lexical_unit == NUMBER) {
        while (*source != '\0' && detect_to_which_lexical_unit_character_belongs(*source) == act_lexical_unit) {
            *word = *source;
            source++, word++;
        }
    } else {
        *word = *source;
        source++, word++;
    }

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