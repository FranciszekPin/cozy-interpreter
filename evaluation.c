#include "evaluation.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

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