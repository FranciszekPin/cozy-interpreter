//
// Created by learning-account on 20.01.2021.
//

#include <stdio.h>
#include "error_manager.h"

void throw_error(error_t error_type) {
    printf("%d\n", error_type);
}