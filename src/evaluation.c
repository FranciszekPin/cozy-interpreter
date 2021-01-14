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

int get_operator_priority(char operator) {
    int result;

    switch (operator) {
        case '*':
            result = 10;
            break;
        case '+':
            result = 9;
            break;
        default:
            result = -1;
            break;
    }
}

bool equal(char *string_a, char *string_b) {
    return strcmp(string_a, string_b) == 0;
}

bool is_operator(char operator) {
    return operator == '+' || operator == '*';
}

void expression_to_ONP(char *expression, char *ONP) {
    stack_t stack = create_stack();

    while (*expression != '\0') {
        expression = skip_whitespace(expression);
        if (isdigit(*expression)) {
            printf("%c", *expression);
            expression++;
        }
        else if (is_operator(*expression)) {
            while (!is_empty(stack) && is_operator(get_top(stack).word[0])) {
                stack_val_t act_val;
                stack = pop(stack, &act_val);
                printf("%s", act_val.word);
            }

            stack_val_t value_to_push;
            char operator_to_add[LINE_LENGTH];
            operator_to_add[0] = *expression;
            strcpy(value_to_push.word, operator_to_add);
            stack = push(stack, value_to_push);

            expression++;
        }
        else if (is_bracket(*expression)) {
            if (*expression == '(') {
                stack_val_t value_to_push;
                strcpy(value_to_push.word, "(");
                stack = push(stack, value_to_push);
            }
            else {
                stack_val_t act_val;
                do {
                    stack = pop(stack, &act_val);
                    if (!equal(act_val.word, "(")) {
                        printf("%s", act_val.word);
                    }
                } while (!equal(act_val.word, "("));
            }

            expression++;
        }
    }

    while (!is_empty(stack)) {
        stack_val_t act_val;
        stack = pop(stack, &act_val);
    }
}