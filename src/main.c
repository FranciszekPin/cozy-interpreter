#include <stdio.h>
#include <stdlib.h>
#include "source_code_reader.h"
#include "variable_register.h"
#include "instruction.h"

#include "program_runner.h"
#include "../tests/run_tests.h"

int main(int argc, char **argv) {
    //run_tests();
    if (argc == 1) {
        throw_error(NO_FILE_PROVIDED, -1, NULL, NULL);
    } else if (argc == 2) {
        source_code_t source_code;
        create_source_code_reader(&source_code);
        load_source_code(&source_code, argv[1]);

        variable_register_t variable_register = create_variable_register();
        instruction_tree_t instruction_tree = create_instruction_tree();

        load_defined_variables(&source_code, variable_register, instruction_tree);
        instruction_tree = parse_program(&source_code, instruction_tree, variable_register);

        run_program(instruction_tree, variable_register);

        remove_variable_register(variable_register);
        remove_instruction_tree(instruction_tree);
    } else {
        throw_error(TOO_MANY_ARGUMENTS, -1, NULL, NULL);
    }

    return 0;
}