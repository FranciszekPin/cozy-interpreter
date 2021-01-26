#include "test_parser.h"
#include "tester_kit.h"
#include "../src/parser.h"


void test_parser() {
    source_code_t source_code;
    create_source_code_reader(&source_code);
    load_source_code("tests/test_parser.coz", &source_code);

    variable_register_t variableRegister = create();

    load_defined_variables(&source_code, variableRegister);

    run_test("test if variable is loaded", is_variable_defined(variableRegister, "a") == true);
    run_test("test if variable is loaded", get_variable_val(variableRegister, "a") == 0);
    run_test("test if variable is loaded", is_variable_defined(variableRegister, "ba") == true);
    run_test("test if variable is loaded", get_variable_val(variableRegister, "ba") == 0);
    run_test("test if variable is loaded", is_variable_defined(variableRegister, "bc") == true);
    run_test("test if variable is loaded", get_variable_val(variableRegister, "bc") == 0);
    run_test("test if variable is loaded", is_variable_defined(variableRegister, "b") == false);
    run_test("test if variable is loaded", is_variable_defined(variableRegister, "ugh") == false);

    run_test("test if act_line_number is set to program", get_act_line_number(&source_code) == 6);

    variableRegister = remove_variable_register(variableRegister);
}