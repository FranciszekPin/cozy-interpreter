#include "test_evaluation.h"
#include "../src/constants.h"
#include "tester_kit.h"

void test_evaluation() {
    test_expression_to_ONP("(2+3)*5", "23+5*");
    test_expression_to_ONP("2+(3*5)", "235*+");
    test_expression_to_ONP("(2+2)*(3*5)", "22+35**");
    test_expression_to_ONP("(((2+(3*5))))", "235*+");
}

void test_detect_to_which_lexical_unit_character_belongs(char c, lexical_unit_t expected_val) {
    lexical_unit_t result;
    result = detect_to_which_lexical_unit_character_belongs(c);
    run_test("test detecting lexical unit", expected_val == result);
}

void test_skip_whitespace(char *expression, char *expected_val) {
    expression = skip_whitespace(expression);

    run_test("test skip_whitespace()", test_if_result_equals_expected(expression, expected_val));
}

void test_read_lexical_unit(char *expression, char *expected_val) {
    char word[LINE_LENGTH];
    read_lexical_unit(expression, word);

    run_test("test read_lexical_unit()", test_if_result_equals_expected(word, expected_val));
}

void test_end_of_string(char *expression, bool expected_val) {
    run_test("test end_of_string()", end_of_string(expression) == expected_val);
}

void test_expression_to_ONP(char *expression, char *expected_val) {
    char ONP[LINE_LENGTH];
    expression_to_ONP(expression, ONP);
    run_test("test expression_to_ONP()", test_if_result_equals_expected(ONP, expected_val));
}

