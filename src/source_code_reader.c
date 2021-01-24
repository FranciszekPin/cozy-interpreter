#include "source_code_reader.h"
#include <stdlib.h>
#include <stdio.h>


char ** load_source_code(char *file_name, source_code_t* source_code) {
    FILE *file;

    file = fopen(file_name, "r");
    if (file == NULL) {
        printf("File with given name doesn't exist.\n");
        exit(EXIT_FAILURE);
    }

    int line_number = 0;
    while (fgets(source_code->code[line_number], 150, file)) {
        printf("%3d: %s", line_number, source_code->code[line_number]);
        line_number++;
    }
    fclose(file);
}

