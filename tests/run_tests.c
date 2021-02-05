#include "run_tests.h"

void run_tests() {
    test_instruction_stack();
    test_parser();
    test_instruction();
    test_evaluation();
    test_source_code_reader();
    test_variable_register();

//    test_program_runner();
}