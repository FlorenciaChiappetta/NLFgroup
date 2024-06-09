#include <stdio.h>

int validateIntInput() {
    int number;
    while (scanf("%d", &number) != 1) {
        printf("Opción no válida. Ingrese un número por favor.");
        while (getchar() != '\n');
    }
    return number;
}
