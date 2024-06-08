#include <stdlib.h>
#include <string.h>
#include "menu_opt.h"

menu_opt *new_menu_opt(const char label[], int value) { // Calculate the size needed for the struct and the label
    size_t total_size = sizeof(menu_opt) + (strlen(label) + 1);

    menu_opt *opt = malloc(total_size);
    if (opt != NULL) {
        strcpy(opt->label, label);
        opt->value = value;
    }

    return opt;
}