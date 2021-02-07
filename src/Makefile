OBJ = error_manager.o evaluation.o instruction.o instruction_stack.o main.o parser.o program_runner.o source_code_reader.o stack.o string_operations.o variable_register.o

ci : $(OBJ)
	$(CC) -o ci $(OBJ)

error_manager.o: error_manager.c error_manager.h instruction.h \
 constants.h variable_register.h string_operations.h
evaluation.o: evaluation.c variable_register.h constants.h \
 string_operations.h instruction.h evaluation.h error_manager.h parser.h \
 source_code_reader.h instruction_stack.h stack.h
instruction.o: instruction.c instruction.h constants.h \
 string_operations.h
instruction_stack.o: instruction_stack.c instruction_stack.h constants.h \
 instruction.h
main.o: main.c source_code_reader.h variable_register.h constants.h \
 string_operations.h instruction.h program_runner.h evaluation.h \
 error_manager.h parser.h instruction_stack.h ../tests/run_tests.h \
 ../tests/test_evaluation.h ../tests/../src/evaluation.h \
 ../tests/test_source_code_reader.h ../tests/../src/parser.h \
 ../tests/test_parser.h ../tests/test_instruction.h \
 ../tests/test_variable_register.h ../tests/test_program_runner.h \
 ../tests/../src/source_code_reader.h ../tests/../src/variable_register.h \
 ../tests/../src/program_runner.h ../tests/test_instruction_stuck.h
parser.o: parser.c parser.h source_code_reader.h variable_register.h \
 constants.h string_operations.h instruction.h evaluation.h \
 error_manager.h instruction_stack.h
program_runner.o: program_runner.c program_runner.h instruction.h \
 constants.h variable_register.h string_operations.h evaluation.h \
 error_manager.h parser.h source_code_reader.h instruction_stack.h
source_code_reader.o: source_code_reader.c source_code_reader.h \
 variable_register.h constants.h string_operations.h instruction.h \
 error_manager.h
stack.o: stack.c stack.h constants.h
string_operations.o: string_operations.c stack.h constants.h evaluation.h \
 error_manager.h instruction.h variable_register.h string_operations.h \
 parser.h source_code_reader.h instruction_stack.h
variable_register.o: variable_register.c variable_register.h constants.h \
 string_operations.h instruction.h error_manager.h

.PHONY: clear

clear:
	rm -f $(OBJ)