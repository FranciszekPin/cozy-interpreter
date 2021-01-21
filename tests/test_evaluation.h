#ifndef COZY_INTERPRETER_TEST_EVALUATION_H
#define COZY_INTERPRETER_TEST_EVALUATION_H

#include "../src/evaluation.h"

void test_evaluation();

void test_expression_to_ONP(char *expression, char *expected_val);

void test_get_lexical_unit_type(char *lexical_unit, lexical_unit_t expected_val);

void test_skip_whitespace(char *expression, char *expected_val);

void test_end_of_string(char *expression, bool expected_val);

void test_read_from_separated_form(char *expression, char *expected_val);

void test_remaining_text_read_from_separated_form(char *expression, char *expected_val);

void test_check_if_lexical_unit_is_correct(char *lexical_unit, error_t expected_val);

void test_check_if_separated_form_is_correct(char *separated_form, error_t expected_val);

void test_convert_expression_to_separated_form(char *expression, char *expected_val);

void test_read_lexical_unit(char *expression, char *expected_val);

#endif //COZY_INTERPRETER_TEST_EVALUATION_H
