#include "estudiantes.h"
#include <string.h>
#define EdadMinima 17
#define EdadMaxima 100
#define notaMinima 4
#define MaxMaterias 5


//creo estudiante
estudiante *new_estudiante(unsigned long legajo, const char *nombre, const char *apellido, unsigned char edad) {
    if (edad < EdadMinima || edad > EdadMaxima) {
        return NULL;
    }

    estudiante *entidad = malloc(sizeof(estudiante)); //Dinamica
    entidad->legajo = legajo;
    entidad->nombre = new_string(nombre); //Dinamica
    entidad->apellido = new_string(apellido); //Dinamica
    entidad->edad = edad;
    entidad->lista_materias = new_empty_cursada(); //Dinamica

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
    if(/*condición donde se supera la cantidad de materías a inscribirse */){
        printf("No se puede inscribir a más materías. \n");
        return;
    }

}

int rendir_materia(){

}

//Se elimina un estudiante por nombre, quizas será mejor por apellido o legajo, ver despues
void eliminar_estudiante(estudiante *alumno){
    if(alumno == NULL){
        return;
    }
    free(alumno ->nombre);
    free(alumno -> apellido);
    free(alumno->lista_materias);

    free(alumno);
}

double calcular_promedio_estudiante(estudiante *pEstudiante) {

}


int aprobo_materia() {

}