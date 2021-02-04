#include "test_instruction_stuck.h"
#include "../src/instruction_stack.h"
#include "tester_kit.h"

void test_instruction_stack() {
    instruction_stack_t instruction_stack = create_instruction_stack();

    instruction_stack = instruction_stack_push(instruction_stack, IF);
    instruction_stack = instruction_stack_push(instruction_stack, END);
    instruction_stack = instruction_stack_push(instruction_stack, WHILE);

    run_test("test instruction_stuck", instruction_stuck_get_top(instruction_stack) == WHILE);

    type_of_instruction_t instruction;
    instruction_stack = instruction_stuck_pop(instruction_stack, &instruction);

    run_test("test instruction_stuck", instruction == WHILE);
    run_test("test instruction_stuck", instruction_stuck_get_top(instruction_stack) == END);

    instruction_stack = instruction_stack_push(instruction_stack, READ);
    run_test("test instruction_stuck", instruction_stuck_get_top(instruction_stack) == READ);


    instruction_stack = instruction_stuck_pop(instruction_stack, &instruction);
    instruction_stack = instruction_stuck_pop(instruction_stack, &instruction);
    instruction_stack = instruction_stuck_pop(instruction_stack, &instruction);

    run_test("test instruction_stuck", instruction_stuck_is_empty(instruction_stack) == true);
}