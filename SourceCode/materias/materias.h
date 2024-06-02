#include <stdlib.h>
//creo el tipo de dato MATERIA

typedef enum {false, true} bool;
typedef enum {computacion,sonido} carrera;

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

//metodos

nodoListaMateria* crearListaMaterias();
Materia* crearMateria(char nombre[100], int anio);
nodoListaMateria* crearNodoMateria(Materia* materiaNueva);
nodoListaMateria* darAltaMateria(nodoListaMateria** lista, Materia* nombreMateria);
int obtenerCantMaterias(nodoListaMateria **lista);
nodoListaMateria* buscarMateriaPorNombre(nodoListaMateria *lista, char nombre[100]); //HACER
void getListaMaterias(nodoListaMateria *lista); //HECHO
nodoListaMateria* buscarMateriaPorID(nodoListaMateria *lista, int id);
