#include <stdio.h>
#include <stdlib.h>
#include "source_code_reader.h"
#include "variable_register.h"
#include "instruction.h"

#include "program_runner.h"
#include "../tests/run_tests.h"

int main(int argc, char **argv) {

    if (argc == 1) {
        printf("No file name provided\n");
    }
    else if (argc == 2) {
        source_code_t source_code;
        create_source_code_reader(&source_code);
        load_source_code(argv[1], &source_code);

        variable_register_t variableRegister = create();
        instruction_tree_t instruction_tree = NULL;


        load_defined_variables(&source_code, variableRegister, instruction_tree);
        instruction_tree = parse_program(&source_code, instruction_tree, variableRegister);


        run_program(instruction_tree, instruction_tree, variableRegister);

        remove_variable_register(variableRegister);
        remove_instruction_tree(instruction_tree);
    }
    else {
        printf("Too many arguments\n");
    }

    return 0;
}