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
                    calculate_ONP_val(act_instruction->ONP_expression, variableRegister, act_instruction->line_number), act_instruction->line_number);

        }
            break;
        case PRINT_VARIABLE: {
            printf("%d\n", calculate_ONP_val(act_instruction->ONP_expression, variableRegister, act_instruction->line_number));

        }
            break;

        case PRINT_STRING: {
            printf("%s\n", act_instruction->ONP_expression);

        }
            break;

        case IF: {
            bool is_condition_true = calculate_ONP_val(act_instruction->ONP_expression, variableRegister, act_instruction->line_number);

            if (is_condition_true)
                run_program(act_instruction->instruction_if_true, variableRegister);
            else
                run_program(act_instruction->instruction_if_false, variableRegister);
        }
            break;

        case WHILE: {
            bool is_condition_true = calculate_ONP_val(act_instruction->ONP_expression, variableRegister, act_instruction->line_number);
            while (is_condition_true) {
                run_program(act_instruction->instruction_if_true, variableRegister);

                is_condition_true = calculate_ONP_val(act_instruction->ONP_expression, variableRegister, act_instruction->line_number);
            }
        }
            break;

        case READ: {
            if (!is_variable_defined(variableRegister, act_instruction->ONP_expression, act_instruction->line_number)) {
                throw_error(ILLEGAL_VARIABLE_NAME, act_instruction->line_number);
            }

            int tmp;
            scanf("%d", &tmp);
            set_val(variableRegister, act_instruction->ONP_expression, tmp, act_instruction->line_number);
        }
            break;

        default: {
            throw_error(UNKNOWN_INSTRUCTION_TYPE, act_instruction->line_number);
        }
    }

    run_program(instruction_tree->next_instruction, variableRegister);
}