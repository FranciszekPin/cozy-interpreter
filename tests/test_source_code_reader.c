#include "test_source_code_reader.h"
#include "../src/source_code_reader.h"
#include "../src/constants.h"

void test_source_code_reader() {
    test_read_source_code();
}

void test_read_source_code() {
    source_code_t source_code;
    source_code.number_of_lines = 0;


    load_source_code("main.coz", &source_code);
}