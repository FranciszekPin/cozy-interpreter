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

bool remove_unnecessary_brackets(char *expression) {
    char copy[100];
    strcpy(copy, expression);
    char *test_expression = expression+1;
    int i = 0;
    while (expression[i+1] != '\0')
        i++;

    test_expression[i-1] = '\0';

    if (!brackets_are_correct(test_expression)) {
        strcpy(expression, copy);
        return false;
    } else {
        strcpy(expression, test_expression);
        return true;
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