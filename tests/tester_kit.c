#include "tester_kit.h"

void print_error(char *text) {
    printf("\033[1;31m%s\033[0m", text);
}

void run_test(char *test_title, bool passed) {
    printf("%s: ", test_title);
    print_test_info(passed);
}

bool test_if_result_equals_expected(char *result, char *expected_val) {
    return strcmp(result, expected_val) == 0;
}

void print_test_info(bool passed) {
    (passed) ? printf("SUCCESS") : print_error("FAILED");
    printf("\n");
}
