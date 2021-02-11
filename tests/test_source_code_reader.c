#include <stdio.h>
#include "test_source_code_reader.h"
#include "../src/constants.h"
#include "tester_kit.h"
#include "../src/string_operations.h"

void test_source_code_reader() {
    test_read_source_code();
}

void test_read_source_code() {
    source_code_t source_code;
    create_source_code_reader(&source_code);

    load_source_code(&source_code, "tests/test_source_code_reader.coz");

    run_test("test checking number of lines", get_number_of_lines(&source_code) == 7);

    run_test("test reading from file line 0", equal(get_act_code_line(&source_code, NULL, NULL), "some"));
    go_to_next_line(&source_code);
    run_test("test reading from file line 1", equal(source_code.code[1], "    random"));
    go_to_next_line(&source_code);
    run_test("test reading from file line 2", equal(source_code.code[2], "    test"));
    go_to_next_line(&source_code);
    run_test("test reading from file line 3", equal(get_act_code_line(&source_code, NULL, NULL), "    here."));

    run_test("test if there are lines to read", are_lines_to_read(&source_code) == true);

    skip_empty_lines(&source_code, NULL, NULL);
    run_test("test skipping whitespace", get_act_line_number(&source_code) == 3);

    go_to_next_line(&source_code);
    skip_empty_lines(&source_code, NULL, NULL);
    run_test("test skipping whitespace", get_act_line_number(&source_code) == 6);

    skip_empty_lines(&source_code, NULL, NULL);
    run_test("test skipping whitespace", get_act_line_number(&source_code) == 6);

    go_to_next_line(&source_code);
    run_test("test if there are lines to read", are_lines_to_read(&source_code) == false);
}