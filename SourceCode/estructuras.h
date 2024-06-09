#ifndef STRUCT_H 
#define STRUCT_H 
#define COLOR_RED     "\033[31m"
#define COLOR_RESET   "\033[0m"

typedef enum {false, true} bool;
typedef enum {computacion,sonido,ambiental} carrera;

const char *nombresCarreras[] = {
  "Computacion",
  "Sonido",
  "Ambiental",
};


typedef struct structMateria {
    char nombre[100];
    int notas[3];
    int anio;
    float promedio;
} Materia;

typedef struct nodoListaMateria{
    Materia* materia;
    struct nodoListaMateria* proximo;
} nodoListaMateria;

typedef struct structEstudiante {
    char nombre [100];
    char apellido [100];
    int legajo;
    int edad[2];
    carrera carreraAnotada;
    nodoListaMateria* materias;
} Estudiante;

typedef struct nodoListaEstudiante{
    Estudiante* estudiante;
    struct nodoListaEstudiante* proximo;
    int a;
} nodoListaEstudiante;
#endif 
