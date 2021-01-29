#include "test_evaluation.h"
#include "test_source_code_reader.h"
#include "test_parser.h"
#include "test_instruction.h"
#include "test_variable_register.h"
#include "test_program_runner.h"

void run_tests() {
    test_parser();
    test_instruction();
    test_evaluation();
    test_source_code_reader();
    test_variable_register();

    test_program_runner();
}