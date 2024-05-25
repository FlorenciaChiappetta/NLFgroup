#include "materias.h"

//creo el tipo de dato
typedef struct estudiante {
    unsigned long legajo;
    char *nombre;
    char *apellido;
    unsigned char edad;
    cursada *lista_materias;
} estudiante;

//inicializo un estudiante
estudiante *new_estudiante(unsigned long legajo, const char *nombre, const char *apellido, unsigned char edad);

//metodos varios 

void anotarse_materia(estudiante *puntEstudiante, materia *puntMateria);

int rendir_materia();

void get_estudiante();

void eliminar_estudiante();

double calcular_promedio_estudiante();

int aprobo_materia();