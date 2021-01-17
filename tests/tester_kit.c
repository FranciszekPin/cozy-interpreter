#include "tester_kit.h"

void run_test(char *test_title, bool passed) {
    printf("%s: ", test_title);
    print_test_info(passed);
}

bool test_if_result_equals_expected(char *result, char *expected_val) {
    return strcmp(result, expected_val) == 0;
}

void print_test_info(bool passed) {
    (passed) ? printf("SUCCESS") : printf("FAILED");
    printf("\n");
}
