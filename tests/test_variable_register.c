#include "test_variable_register.h"
#include "test_source_code_reader.h"
#include "tester_kit.h"

void test_variable_register() {
    variable_register_t variable_register = create();

    variable_register = define_variable(variable_register, "xyz");
    variable_register = define_variable(variable_register, "test");

    variable_register = set_val(variable_register, "test", 5);

    run_test("test checking if variable is defined", is_variable_defined(variable_register, "xyz") == 1);
    run_test("test checking if variable is defined", is_variable_defined(variable_register, "xyx") == 0);
    run_test("test checking if variable is defined", is_variable_defined(variable_register, "xy") == 0);

    run_test("test getting variable val", get_variable_val(variable_register, "xyz") == 0);
    run_test("test getting variable val", get_variable_val(variable_register, "test") == 5);

    run_test("test detecting variable type", detect_variable_type("int") == INT);
    run_test("test detecting variable type", detect_variable_type(" int") == NOT_A_TYPE);

    remove_variable_register(variable_register);
}
