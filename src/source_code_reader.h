#ifndef COZY_INTERPRETER_SOURCE_CODE_READER_H
#define COZY_INTERPRETER_SOURCE_CODE_READER_H

#include "constants.h"

typedef struct {
    char code[MAX_NUMBER_OF_LINES][LINE_LENGTH];
    int number_of_lines;
} source_code_t;

char ** load_source_code(char *file_name, source_code_t *source_code);

#endif //COZY_INTERPRETER_SOURCE_CODE_READER_H
