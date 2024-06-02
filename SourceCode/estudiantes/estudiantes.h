#include "materias.h"

//creamos  el tipo de dato


typedef struct structEstudiante {
    int legajo;
    char nombre [100];
    char apellido [100];
    int edad[2];
    carrera carreraAnotada;
    nodoListaMateria* materias;
} Estudiante;


typedef struct nodoListaEstudiante {
    Estudiante* estudiante;
    struct nodoListaEstudiante* proximo;
} nodoListaEstudiante;

//metodos

nodoListaEstudiante *crearListaEstudiantes();
Estudiante* crearEstudiante(char nombre[100], char apellido[100], int legajo, int edad[2], carrera carreraAAnotarse);
nodoListaEstudiante *crearNodoEstudiante (Estudiante* estudiante);
NodoListaEstudiante* validarLegajo(nodoListaEstudiante **lista, int legajo); //HECHO
void darAltaEstudiante(nodoListaEstudiante **lista, Estudiante* nuevoEstudiante);
void buscarEstudiantePorNombre(nodoListaEstudiante **lista, char nombre[100]);
void buscarEstudiantePorLegajo(nodoListaEstudiante **lista, int legajo);//HACER
int obtenerLongitudLista(nodoListaEstudiante **lista);
void anotarMateria(Materia *materia_a_anotar, nodoListaEstudiante *nodoEstudiante, char* path);
void rendirMateria(nodoListaMateria* materia_a_rendir);
void consultarPromedio(nodoListaMateria *lista);
void getEstudiante(estudiante *alumno);
void getListaEstudiantes(nodoListaEstudiante *lista); //HACER