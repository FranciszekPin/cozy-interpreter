#include "test_evaluation.h"
#include "../src/constants.h"
#include "tester_kit.h"
#include "../src/string_operations.h"

void test_evaluation() {
    test_get_lexical_unit_type("a", VARIABLE);
    test_get_lexical_unit_type("Z", VARIABLE);
    test_get_lexical_unit_type("X", VARIABLE);
    test_get_lexical_unit_type("0", NUMBER);
    test_get_lexical_unit_type("9", NUMBER);
    test_get_lexical_unit_type("+", OPERATOR);
    test_get_lexical_unit_type("*", OPERATOR);
    test_get_lexical_unit_type("-", OPERATOR);
    test_get_lexical_unit_type("!=", OPERATOR);
    test_get_lexical_unit_type("^", NOT_A_LEXICAL_UNIT);
    test_get_lexical_unit_type("=!", OPERATOR);
    test_get_lexical_unit_type("&&", OPERATOR);

    test_skip_whitespace(" \n\t  some_text", "some_text");
    test_skip_whitespace(" s ome_text", "s ome_text");
    test_skip_whitespace(" \n  \t  some_text  ", "some_text  ");
    test_skip_whitespace(" \n  \t  some_text \n\t ", "some_text \n\t ");

    test_read_lexical_unit("^^ abcd+5", "");
    test_read_lexical_unit("abcd+5", "abcd");
    test_read_lexical_unit("abcd+ajs;dlfj", "abcd");
    test_read_lexical_unit("==abcd+ajs;dlfj", "==");
    test_read_lexical_unit("   abcd  +5", "abcd");
    test_read_lexical_unit(" +  abcd  +5", "+");
    test_read_lexical_unit("((+  abcd  +5", "(");
    test_read_lexical_unit("******((+  abcd  +5", "******");
    test_read_lexical_unit("  124******((+  abcd  +5", "124");
    test_read_lexical_unit(" 2131;1231 124******((+  abcd  +5", "2131");

    test_end_of_string("ala ma kota", false);
    test_end_of_string("", true);
    test_end_of_string("\0ala ma kota", true);

    test_read_from_separated_form("", "");
    test_read_from_separated_form("14 sth", "14");
    test_read_from_separated_form("uwu sth", "uwu");

    test_remaining_text_read_from_separated_form("sth goes wrong", "goes wrong");
    test_remaining_text_read_from_separated_form("wrong", "");

    test_convert_expression_to_separated_form("3+5", "3 + 5");
    test_convert_expression_to_separated_form("((", "( (");
    test_convert_expression_to_separated_form("3^5", "3  5");
    test_convert_expression_to_separated_form("3+++5", "3 +++ 5");
    test_convert_expression_to_separated_form("  <><==36 +++ \t  ( 5 var )  ", "<><== 36 +++ ( 5 var )");

    test_check_if_lexical_unit_is_correct("ala", NO_ERROR);
    test_check_if_lexical_unit_is_correct("245", NO_ERROR);
    test_check_if_lexical_unit_is_correct("<=", NO_ERROR);
    test_check_if_lexical_unit_is_correct(">=", NO_ERROR);
    test_check_if_lexical_unit_is_correct("==", NO_ERROR);
    test_check_if_lexical_unit_is_correct("!=", NO_ERROR);
    test_check_if_lexical_unit_is_correct("<", NO_ERROR);
    test_check_if_lexical_unit_is_correct(">", NO_ERROR);
    test_check_if_lexical_unit_is_correct(">>", WRONG_OPERATOR_USAGE);
    test_check_if_lexical_unit_is_correct(">>", WRONG_OPERATOR_USAGE);
    test_check_if_lexical_unit_is_correct("&", WRONG_OPERATOR_USAGE);
    test_check_if_lexical_unit_is_correct("$", ILLEGAL_CHARACTER_USAGE);

    test_check_if_separated_form_is_correct("vara + varb", NO_ERROR);
    test_check_if_separated_form_is_correct("vara ++ varb", WRONG_OPERATOR_USAGE);
    test_check_if_separated_form_is_correct("( vara + varb )", NO_ERROR);
    test_check_if_separated_form_is_correct("( vara + ) varb", ILLEGAL_EXPRESSION_FORM);
    test_check_if_separated_form_is_correct("( vara + ) 345 varb", ILLEGAL_EXPRESSION_FORM);
    test_check_if_separated_form_is_correct("( ( vara + 2323 ) * 345 ) == ( varb != 6 )", NO_ERROR);

    test_expression_to_ONP("2", "2");
    test_expression_to_ONP("", "");
    test_expression_to_ONP("256", "256");
    test_expression_to_ONP("abcd", "abcd");
    test_expression_to_ONP("abcd + 16", "abcd 16 +");
    test_expression_to_ONP("abcd + 16 * 6", "abcd 16 6 * +");
    test_expression_to_ONP("69 + var / 3 * 6", "69 var 3 / 6 * +");
    test_expression_to_ONP("( ( i + someVar ) * ( 16 * 6 ) + 37 ) * another", "i someVar + 16 6 * * 37 + another *");
    test_expression_to_ONP("3 == 4 && test || 17", "3 4 == test && 17 ||");
    test_expression_to_ONP("a == 3 || b == 5", "a 3 == b 5 == ||");
    test_expression_to_ONP("a == ( 3 || b ) == 5", "a 3 b || == 5 ==");

    test_calculate_ONP_val("2 3 +", 5);
    test_calculate_ONP_val("2 3 + 7 ||", 1);
    test_calculate_ONP_val("2 3 + 7 ||", 1);
    test_calculate_ONP_val("2 3 + 0 &&", 0);
    test_calculate_ONP_val("8 49 7 / <", 0);
    test_calculate_ONP_val("someVar", 1);
    test_calculate_ONP_val("someVar 0 &&", 0);
    test_calculate_ONP_val("someVar 0 ||", 1);
    test_calculate_ONP_val("someVar 00 <=", 0);

    test_evaluate_expression("(3 + var) * 8", 32);
    test_evaluate_expression("(11 / 2) == 5", 1);
    test_evaluate_expression("  (11/2) !=  5  ", 0);

}

void test_get_lexical_unit_type(char *lexical_unit, lexical_unit_t expected_val) {
    lexical_unit_t result;
    result = detect_to_which_lexical_unit_string_belongs(lexical_unit);
    run_test("test detect_to_which_lexical_unit_string_belongs()", expected_val == result);
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

void test_read_from_separated_form(char *expression, char *expected_val) {
    char word[LINE_LENGTH];
    read_word(expression, word);
    run_test("test read_from_separated_form()", test_if_result_equals_expected(word, expected_val));
}

void test_remaining_text_read_from_separated_form(char *expression, char *expected_val) {
    char word[LINE_LENGTH];
    expression = read_word(expression, word);
    run_test("test remaining_text_read_from_separated_form()", test_if_result_equals_expected(expression, expected_val));
}


void test_convert_expression_to_separated_form(char *expression, char *expected_val) {
    char separated_form[LINE_LENGTH];
    convert_expression_to_separated_form(separated_form, expression);
    run_test("test convert_expression_to_separated_form()", test_if_result_equals_expected(separated_form, expected_val));
}

void test_check_if_lexical_unit_is_correct(char *lexical_unit, error_t expected_val) {
    error_t result = check_if_lexical_unit_is_correct(lexical_unit);
    run_test("test check_if_lexical_unit_is_correct()", result == expected_val);
}

void test_check_if_separated_form_is_correct(char *separated_form, error_t expected_val) {
    error_t result = check_if_separated_form_is_correct(separated_form);
    run_test("test check_if_separated_form_is_correct()", result == expected_val);
}


void test_expression_to_ONP(char *expression, char *expected_val) {
    char ONP[LINE_LENGTH];
    separated_form_to_ONP(expression, ONP);
    run_test("test separated_form_to_ONP()", test_if_result_equals_expected(ONP, expected_val));
}

void test_calculate_ONP_val(char *ONP_expression, int expected_val) {
    int result = calculate_ONP_val(ONP_expression);
    run_test("test calculate_ONP_val()", result == expected_val);
}

void test_evaluate_expression(char *expression, int expected_val) {
    int result = evaluate_expression(expression);
    run_test("test evaluate_expression()", result == expected_val);
}