#include "test_program_runner.h"
#include "../src/source_code_reader.h"
#include "../src/variable_register.h"
#include "../src/parser.h"
#include "../src/program_runner.h"

void test_program_runner() {
    source_code_t source_code;
    create_source_code_reader(&source_code);
    load_source_code("tests/test_program_runner.coz", &source_code);

    variable_register_t variableRegister = create();

    load_defined_variables(&source_code, variableRegister);
    instruction_tree_t instruction_tree = parse_program(&source_code);

    run_program(instruction_tree, variableRegister);

    remove_variable_register(variableRegister);
    remove_instruction_tree(instruction_tree);
}
