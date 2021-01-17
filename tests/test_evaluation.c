#include "test_evaluation.h"
#include "../src/constants.h"
#include "tester_kit.h"

void test_evaluation() {
    test_expression_to_ONP("(2+3)*5", "23+5*");
    test_expression_to_ONP("2+(3*5)", "235*+");
    test_expression_to_ONP("(2+2)*(3*5)", "22+35**");
    test_expression_to_ONP("(((2+(3*5))))", "235*+");
}

void test_expression_to_ONP(char *expression, char *expected_val) {
    char ONP[LINE_LENGTH];
    expression_to_ONP(expression, ONP);
    run_test("test expression_to_ONP()", test_if_result_equals_expected(ONP, expected_val));
}

