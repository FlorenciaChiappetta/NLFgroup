#include "materia.h"

// creo una materia
materia *new_materia(unsigned short id, char *nombre) {
    if (nombre == NULL) {
        return NULL;
    }

    materia *puntMateria = (materia *) malloc(sizeof(materia));
    puntMateria->id = id;
    puntMateria->nombre = new_string(nombre);
    return pMateria;
}

//print datos de la materia
void get_materia(materia *puntMateria) {
    if (puntMateria == NULL) {
        return;
    }
    printf("\n")
    printf("Id Materia: %d\n", puntMateria->id);
    printf("Nombre: %s\n", puntMateria->nombre);
    printf("\n")
}


void eliminar_materia(materia *puntMateria) {
if (puntMateria == NULL) {
        return;
    }

    free(puntMateria->nombre);
    free(puntMateria);
}
