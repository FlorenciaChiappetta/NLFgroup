#include "menu.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//habria que agregar los "extras", esto es lo minimo que se pide

// TODO check if this works
void clear_src() {
    fflush(stdin);
}

int read_int() {
    int num;
//    printf("Seleccione una opción: ");
    scanf("%d", &num);
    printf("Opción ingresada: %d", num);

    return num;
}

int read_from_options(menu_opt options[]) {
    int selected_opt;
    bool request_option = true;

    do {
        printf("Seleccione una de las siguientes opciones. Para salir ingrese 0.");
        //  TODO make a function of this
        int array_length = *(&options + 1) - options;
        for (int i = 0; i < array_length; i++) {
            printf("[%d]. %s\n", options[i].value, options[i].label);
        }

        selected_opt = read_int();
        //  TODO make a function of this
        bool value_in_array = value_in_options(selected_opt, &options, array_length);

        if (selected_opt == 0 && value_in_array) {
            request_option = false;
        } else {
            printf("Opción inválida.");
        }
    } while (request_option);
}

// TODO move this to helpers
bool value_in_options(int val, menu_opt *arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i]->value == val) {
            return true;
        }
    }
    return false;
}
