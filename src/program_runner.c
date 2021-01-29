#include "program_runner.h"
#include "evaluation.h"


void run_program(instruction_tree_t instruction_tree, variable_register_t variableRegister) {
    if (instruction_tree == NULL)
        return;

    instruction_tree_t act_instruction = instruction_tree;
    type_of_instruction_t type_of_instruction = act_instruction->type_of_instruction;


    switch (type_of_instruction) {
        case START_PROGRAM: {
            run_program(instruction_tree->instruction_if_true, variableRegister);
        }
            break;

        case ASSIGN: {
            set_val(variableRegister, act_instruction->variable_name,
                    calculate_ONP_val(act_instruction->ONP_expression, variableRegister));

        }
            break;
        case PRINT_VARIABLE: {
            printf("%d\n", calculate_ONP_val(act_instruction->ONP_expression, variableRegister));

        }
            break;

        case PRINT_STRING: {
            printf("%s\n", act_instruction->ONP_expression);

        }
            break;

        case IF: {
            bool is_condition_true = calculate_ONP_val(act_instruction->ONP_expression, variableRegister);

            if (is_condition_true)
                run_program(act_instruction->instruction_if_true, variableRegister);
            else
                run_program(act_instruction->instruction_if_false, variableRegister);
        }
            break;

        case WHILE: {
            bool is_condition_true = calculate_ONP_val(act_instruction->ONP_expression, variableRegister);
            while (is_condition_true) {
                run_program(act_instruction->instruction_if_true, variableRegister);

                is_condition_true = calculate_ONP_val(act_instruction->ONP_expression, variableRegister);
            }
        }
            break;

        case READ: {
            if (!is_variable_defined(variableRegister, act_instruction->ONP_expression)) {
                // TODO: hnadling undefined variable
            }

            int tmp;
            scanf("%d", &tmp);
            set_val(variableRegister, act_instruction->ONP_expression, tmp);
        }
            break;

        default: {
            // TODO: handling wrong instruction type
            exit(1);
        }
    }

    run_program(instruction_tree->next_instruction, variableRegister);
}