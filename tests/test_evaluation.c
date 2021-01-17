#include "test_evaluation.h"
#include "../src/constants.h"
#include "tester_kit.h"

void test_evaluation() {
    test_detect_to_which_lexical_unit_character_belongs('a', VARIABLE);
    test_detect_to_which_lexical_unit_character_belongs('Z', VARIABLE);
    test_detect_to_which_lexical_unit_character_belongs('X', VARIABLE);
    test_detect_to_which_lexical_unit_character_belongs('0', NUMBER);
    test_detect_to_which_lexical_unit_character_belongs('9', NUMBER);
    test_detect_to_which_lexical_unit_character_belongs('+', OPERATOR);
    test_detect_to_which_lexical_unit_character_belongs('*', OPERATOR);
    test_detect_to_which_lexical_unit_character_belongs('-', NOT_A_LEXICAL_UNIT);
    test_detect_to_which_lexical_unit_character_belongs('^', NOT_A_LEXICAL_UNIT);

    test_skip_whitespace(" \n\t  some_text", "some_text");
    test_skip_whitespace(" s ome_text", "s ome_text");
    test_skip_whitespace(" \n  \t  some_text  ", "some_text  ");
    test_skip_whitespace(" \n  \t  some_text \n\t ", "some_text \n\t ");

    test_read_lexical_unit("abcd+5", "abcd");
    test_read_lexical_unit("abcd+ajs;dlfj", "abcd");
    test_read_lexical_unit("   abcd  +5", "abcd");
    test_read_lexical_unit(" +  abcd  +5", "+");
    test_read_lexical_unit("((+  abcd  +5", "(");
    test_read_lexical_unit("******((+  abcd  +5", "*");
    test_read_lexical_unit("  124******((+  abcd  +5", "124");
    test_read_lexical_unit(" 2131;1231 124******((+  abcd  +5", "2131");

    test_end_of_string("ala ma kota", false);
    test_end_of_string("", true);
    test_end_of_string("\0ala ma kota", true);

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

