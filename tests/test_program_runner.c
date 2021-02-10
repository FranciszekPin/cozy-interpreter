#include "test_program_runner.h"


void test_program_runner() {
    source_code_t source_code;
    create_source_code_reader(&source_code);
    load_source_code("tests/test_program_runner.coz", &source_code);

    variable_register_t variableRegister = create_variable_register();

    instruction_tree_t instruction_tree = NULL;
    load_defined_variables(&source_code, variableRegister, instruction_tree);
    instruction_tree = parse_program(&source_code, instruction_tree, variableRegister);

    run_program(instruction_tree, instruction_tree, variableRegister);

    remove_variable_register(variableRegister);
    remove_instruction_tree(instruction_tree);
}
