#include "variable_register.h"
#include "string_operations.h"

int get_letter_code(char letter) {
    return letter - 'a';
}

node_t * create() {
    node_t * new_node = malloc(sizeof (node_t));
    for (int i=0; i<NUMBER_OF_LETTERS; i++) {
        new_node->next_node[i] = NULL;
    }

    new_node->value = -1;

    new_node->defined = false;

    return new_node;
}

variable_register_t define_variable(variable_register_t variable_register, char *name) {
    node_t * act_node = variable_register;

    while (*name != '\0') {
        int letter_code = get_letter_code(*name);

        if (letter_code >= NUMBER_OF_LETTERS) {
            printf("Name contains non-letter chars\n");
        }

        if (act_node->next_node[letter_code] == NULL) {
            act_node->next_node[letter_code] = create();
        }

        act_node = act_node->next_node[letter_code];

        name++;
    }

    act_node->defined = true;
    act_node->value = 0;


    return variable_register;
}

variable_register_t set_val(variable_register_t variable_register, char *name, int val) {
    node_t * act_node = variable_register;

    while (*name != '\0') {
        int letter_code = get_letter_code(*name);

        if (letter_code >= NUMBER_OF_LETTERS) {
            // TODO: handling when there is bad name provided
            printf("Name contains non-letter chars\n");
        }

        act_node = act_node->next_node[letter_code];

        name++;
    }

    act_node->value = val;

    return variable_register;
}

bool is_variable_defined(variable_register_t variable_register, char *name) {
    bool result = true;

    while (*name != '\0') {
        int letter_code = get_letter_code(*name);

        if (letter_code > NUMBER_OF_LETTERS) {
            // TODO: handling when there is bad name provided
        }

        if (variable_register->next_node[letter_code] == NULL) {
            result = false;
            break;
        }

        variable_register = variable_register->next_node[letter_code];

        name++;
    }

    return result;
}

int get_variable_val(variable_register_t variable_register, char *name) {
    if (!is_variable_defined(variable_register, name)) {
        // TODO: handling when undefined variable is provided
    }

    while (*name != '\0') {
        int letter_code = get_letter_code(*name);
        variable_register = variable_register->next_node[letter_code];

        name++;
    }

    return variable_register->value;
}

variable_type_t detect_variable_type(char *name) {
    variable_type_t result = NOT_A_TYPE;

    if (equal(name, "int"))
        result = INT;

    return result;
}

variable_register_t remove_variable_register(variable_register_t variable_register) {
    for (int i=0; i<NUMBER_OF_LETTERS; i++) {
        if (variable_register->next_node[i] != NULL)
            variable_register->next_node[i] = remove_variable_register(variable_register->next_node[i]);
    }

    free(variable_register);

    return NULL;
}