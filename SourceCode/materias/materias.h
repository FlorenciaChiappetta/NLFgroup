#include <stdlib.h>
//creo el tipo de dato MATERIA

typedef struct materia {
    unsigned short idMateria;
    char *nombre;
} materia;

//inicializo
materia *new_materia(unsigned short idMateria, char *nombre);

//metodos

void get_materia(materia *pMateria);

void eliminar_materia(materia *pMateria);