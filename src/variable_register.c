#include "variable_register.h"

int get_letter_code(char letter) {
    return letter - 'a';
}

node_t * create() {
    node_t * new_node = malloc(sizeof (node_t));
    for (int i=0; i<NUMBER_OF_LETTERS; i++) {
        new_node->next_node[i] = NULL;
    }

    new_node->defined = false;

    return new_node;
}

variable_register_t insert(variable_register_t variable_register, char *name) {
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
            printf("Name contains non-letter chars\n");
        }

        act_node = act_node->next_node[letter_code];

        name++;
    }

    act_node->value = val;

    return variable_register;
}