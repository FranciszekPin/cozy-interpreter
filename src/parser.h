#ifndef COZY_INTERPRETER_PARSER_H
#define COZY_INTERPRETER_PARSER_H

#include "source_code_reader.h"
#include "variable_register.h"

void load_defined_variables(source_code_t *source_code, variable_register_t variable_register);

void load_variable(source_code_t *source_code, variable_register_t variable_register);

#endif //COZY_INTERPRETER_PARSER_H
