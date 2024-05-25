#include "estudiantes.h"
#include <string.h>
#define EdadMinima 17
#define EdadMaxima 100
#define notaMinima 4


//creo estudiante
estudiante *new_estudiante(unsigned long legajo, const char *nombre, const char *apellido, unsigned char edad) {
    if (edad < EdadMinima || edad > EdadMaxima) {
        return NULL;
    }

    estudiante *entidad = malloc(sizeof(estudiante));
    entidad->legajo = legajo;
    entidad->nombre = new_string(nombre);
    entidad->apellido = new_string(apellido);
    entidad->edad = edad;
    entidad->lista_materias = new_empty_cursada();

    if (entidad->nombre == NULL || entidad->apellido == NULL) {
        return NULL;
    }

    return entidad;
}

//print con datos del alumno
void get_estudiante(estudiante *alumno) {
    if (alumno == NULL) {
        return;
    }

    printf("Nombre: %s", alumno->nombre);
    printf("Apellido: %s", alumno->apellido);
    printf("Edad: %d\n", alumno->edad);
    printf("Legajo: %d\n\n", alumno->legajo);
}


void anotarse_materia(estudiante *pEstudiante, materia *pMateria) {
}

int rendir_materia(){

}

void eliminar_estudiante(){

}

double calcular_promedio_estudiante(estudiante *pEstudiante) {

}


int aprobo_materia() {

}