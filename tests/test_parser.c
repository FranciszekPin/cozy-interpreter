#include "test_parser.h"
#include "tester_kit.h"
#include "../src/parser.h"
#include "../src/instruction.h"
#include "../src/string_operations.h"


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

    instruction_tree_t instruction_tree = parse_program(&source_code);

    instruction_tree_t start_block = instruction_tree;
    instruction_tree_t first_assigment = instruction_tree->instruction_if_true;
    instruction_tree_t outer_while = first_assigment->next_instruction;
    instruction_tree_t first_print_var = outer_while->instruction_if_true;
    instruction_tree_t first_if = first_print_var->next_instruction;
    instruction_tree_t inner_while = first_if->instruction_if_true;
    instruction_tree_t first_print_str = inner_while->instruction_if_true;
    instruction_tree_t second_assigment = inner_while->next_instruction;
    instruction_tree_t second_print_str = first_if->instruction_if_false;
    instruction_tree_t third_assigmnet = second_print_str->next_instruction;
    instruction_tree_t third_print_str = first_if->next_instruction;
    instruction_tree_t second_if = third_print_str->next_instruction;
    instruction_tree_t second_print_var = second_if->instruction_if_true;
    instruction_tree_t forth_assigment = outer_while->next_instruction;

    // start block
    run_test("testing parsing program: start block", start_block->type_of_instruction == START_PROGRAM);
    run_test("testing parsing program: start block", start_block->upper_instruction == NULL);
    run_test("testing parsing program: start block", start_block->next_instruction == NULL);
    run_test("testing parsing program: start block", start_block->instruction_if_true == first_assigment);
    run_test("testing parsing program: start block", start_block->instruction_if_false == NULL);
    run_test("testing parsing program: start block", *start_block->ONP_expression == '\0');
    run_test("testing parsing program: start block", *start_block->variable_name == '\0');

    // first assignment
    instruction_tree_t act_instruction = first_assigment;
    run_test("testing parsing program: first assignment", act_instruction->type_of_instruction == ASSIGN);
    run_test("testing parsing program: first assignment", act_instruction->upper_instruction == start_block);
    run_test("testing parsing program: first assignment", act_instruction->next_instruction == outer_while);
    run_test("testing parsing program: first assignment", act_instruction->instruction_if_true == NULL);
    run_test("testing parsing program: first assignment", act_instruction->instruction_if_false == NULL);
    run_test("testing parsing program: first assignment", equal(act_instruction->ONP_expression, "17"));
    run_test("testing parsing program: first assignment", equal(act_instruction->variable_name, "ba"));

    // outer_while
    act_instruction = outer_while;
    run_test("testing parsing program: outer_while", act_instruction->type_of_instruction == WHILE);
    run_test("testing parsing program: outer_while", act_instruction->upper_instruction == start_block);
    run_test("testing parsing program: outer_while", act_instruction->next_instruction == forth_assigment);
    run_test("testing parsing program: outer_while", act_instruction->instruction_if_true == first_print_var);
    run_test("testing parsing program: outer_while", act_instruction->instruction_if_false == NULL);
    run_test("testing parsing program: outer_while", equal(act_instruction->ONP_expression, "17"));
    run_test("testing parsing program: outer_while", equal(act_instruction->variable_name, ""));

    // first_print_var
    act_instruction = first_print_var;
    run_test("testing parsing program: first_print_var", act_instruction->type_of_instruction == PRINT_VARIABLE);
    run_test("testing parsing program: first_print_var", act_instruction->upper_instruction == outer_while);
    run_test("testing parsing program: first_print_var", act_instruction->next_instruction == first_if);
    run_test("testing parsing program: first_print_var", act_instruction->instruction_if_true == NULL);
    run_test("testing parsing program: first_print_var", act_instruction->instruction_if_false == NULL);
    run_test("testing parsing program: first_print_var", equal(act_instruction->ONP_expression, "bc"));
    run_test("testing parsing program: first_print_var", equal(act_instruction->variable_name, ""));

    // first_if
    act_instruction = first_if;
    run_test("testing parsing program: first_if", act_instruction->type_of_instruction == IF);
    run_test("testing parsing program: first_if", act_instruction->upper_instruction == outer_while);
    run_test("testing parsing program: first_if", act_instruction->next_instruction == third_print_str);
    run_test("testing parsing program: first_if", act_instruction->instruction_if_true == inner_while);
    run_test("testing parsing program: first_if", act_instruction->instruction_if_false == second_print_str);
    run_test("testing parsing program: first_if", equal(act_instruction->ONP_expression, "bc"));
    run_test("testing parsing program: first_if", equal(act_instruction->variable_name, ""));

    // inner_while
    act_instruction = inner_while;
    run_test("testing parsing program: inner_while", act_instruction->type_of_instruction == WHILE);
    run_test("testing parsing program: inner_while", act_instruction->upper_instruction == first_if);
    run_test("testing parsing program: inner_while", act_instruction->next_instruction == second_assigment);
    run_test("testing parsing program: inner_while", act_instruction->instruction_if_true == first_print_str);
    run_test("testing parsing program: inner_while", act_instruction->instruction_if_false == NULL);
    run_test("testing parsing program: inner_while", equal(act_instruction->ONP_expression, "bc"));
    run_test("testing parsing program: inner_while", equal(act_instruction->variable_name, ""));

    // first_print_str
    act_instruction = first_print_str;
    run_test("testing parsing program: first_print_str", act_instruction->type_of_instruction == PRINT_STRING);
    run_test("testing parsing program: first_print_str", act_instruction->upper_instruction == inner_while);
    run_test("testing parsing program: first_print_str", act_instruction->next_instruction == NULL);
    run_test("testing parsing program: first_print_str", act_instruction->instruction_if_true == NULL);
    run_test("testing parsing program: first_print_str", act_instruction->instruction_if_false == NULL);
    run_test("testing parsing program: first_print_str", equal(act_instruction->ONP_expression, "bc"));
    run_test("testing parsing program: first_print_str", equal(act_instruction->variable_name, ""));

    // second_assigment
    act_instruction = second_assigment;
    run_test("testing parsing program: second_assigment", act_instruction->type_of_instruction == ASSIGN);
    run_test("testing parsing program: second_assigment", act_instruction->upper_instruction == first_if);
    run_test("testing parsing program: second_assigment", act_instruction->next_instruction == NULL);
    run_test("testing parsing program: second_assigment", act_instruction->instruction_if_true == NULL);
    run_test("testing parsing program: second_assigment", act_instruction->instruction_if_false == NULL);
    run_test("testing parsing program: second_assigment", equal(act_instruction->ONP_expression, "bc"));
    run_test("testing parsing program: second_assigment", equal(act_instruction->variable_name, "ba"));

    // second_print_str
    act_instruction = second_print_str;
    run_test("testing parsing program: second_print_str", act_instruction->type_of_instruction == PRINT_STRING);
    run_test("testing parsing program: second_print_str", act_instruction->upper_instruction == first_if);
    run_test("testing parsing program: second_print_str", act_instruction->next_instruction == third_assigmnet);
    run_test("testing parsing program: second_print_str", act_instruction->instruction_if_true == NULL);
    run_test("testing parsing program: second_print_str", act_instruction->instruction_if_false == NULL);
    run_test("testing parsing program: second_print_str", equal(act_instruction->ONP_expression, "bc"));
    run_test("testing parsing program: second_print_str", equal(act_instruction->variable_name, ""));

    // third_assigmnet
    act_instruction = third_assigmnet;
    run_test("testing parsing program: third_assigmnet", act_instruction->type_of_instruction == ASSIGN);
    run_test("testing parsing program: third_assigmnet", act_instruction->upper_instruction == first_if);
    run_test("testing parsing program: third_assigmnet", act_instruction->next_instruction == NULL);
    run_test("testing parsing program: third_assigmnet", act_instruction->instruction_if_true == NULL);
    run_test("testing parsing program: third_assigmnet", act_instruction->instruction_if_false == NULL);
    run_test("testing parsing program: third_assigmnet", equal(act_instruction->ONP_expression, "bc"));
    run_test("testing parsing program: third_assigmnet", equal(act_instruction->variable_name, "bc"));

    // third_print_str
    act_instruction = third_print_str;
    run_test("testing parsing program: third_print_str", act_instruction->type_of_instruction == PRINT_STRING);
    run_test("testing parsing program: third_print_str", act_instruction->upper_instruction == outer_while);
    run_test("testing parsing program: third_print_str", act_instruction->next_instruction == second_if);
    run_test("testing parsing program: third_print_str", act_instruction->instruction_if_true == NULL);
    run_test("testing parsing program: third_print_str", act_instruction->instruction_if_false == NULL);
    run_test("testing parsing program: third_print_str", equal(act_instruction->ONP_expression, "bc"));
    run_test("testing parsing program: third_print_str", equal(act_instruction->variable_name, ""));

    // second_if
    act_instruction = second_if;
    run_test("testing parsing program: second_if", act_instruction->type_of_instruction == IF);
    run_test("testing parsing program: second_if", act_instruction->upper_instruction == outer_while);
    run_test("testing parsing program: second_if", act_instruction->next_instruction == NULL);
    run_test("testing parsing program: second_if", act_instruction->instruction_if_true == second_print_var);
    run_test("testing parsing program: second_if", act_instruction->instruction_if_false == NULL);
    run_test("testing parsing program: second_if", equal(act_instruction->ONP_expression, "bc"));
    run_test("testing parsing program: second_if", equal(act_instruction->variable_name, ""));

    // second_print_var
    act_instruction = second_print_var;
    run_test("testing parsing program: second_print_var", act_instruction->type_of_instruction == PRINT_VARIABLE);
    run_test("testing parsing program: second_print_var", act_instruction->upper_instruction == second_if);
    run_test("testing parsing program: second_print_var", act_instruction->next_instruction == NULL);
    run_test("testing parsing program: second_print_var", act_instruction->instruction_if_true == NULL);
    run_test("testing parsing program: second_print_var", act_instruction->instruction_if_false == NULL);
    run_test("testing parsing program: second_print_var", equal(act_instruction->ONP_expression, "bc"));
    run_test("testing parsing program: second_print_var", equal(act_instruction->variable_name, ""));

    // second_print_var
    act_instruction = forth_assigment;
    run_test("testing parsing program: forth_assigment", act_instruction->type_of_instruction == ASSIGN);
    run_test("testing parsing program: forth_assigment", act_instruction->upper_instruction == start_block);
    run_test("testing parsing program: forth_assigment", act_instruction->next_instruction == NULL);
    run_test("testing parsing program: forth_assigment", act_instruction->instruction_if_true == NULL);
    run_test("testing parsing program: forth_assigment", act_instruction->instruction_if_false == NULL);
    run_test("testing parsing program: forth_assigment", equal(act_instruction->ONP_expression, "ba"));
    run_test("testing parsing program: forth_assigment", equal(act_instruction->variable_name, "ba"));

    remove_instruction_tree(instruction_tree);

    variableRegister = remove_variable_register(variableRegister);

}