#include <stdlib.h>
//creo el tipo de dato MATERIA


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
nodoListaMateria* buscarIDMateriaAnotada(nodoListaMateria *lista, int id);
