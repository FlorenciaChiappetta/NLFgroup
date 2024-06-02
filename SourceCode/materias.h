#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define COLOR_RED     "\033[31m"
#define COLOR_RESET   "\033[0m"


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
nodoListaMateria* buscarMateriaPorNombre(nodoListaMateria *lista, char nombre[100]); //HACER
void getListaMaterias(nodoListaMateria *lista); //HECHO
nodoListaMateria* buscarMateriaPorID(nodoListaMateria *lista, int id);

//creo lista de materias
nodoListaMateria* crearListaMaterias() {
    nodoListaMateria *nodo = (nodoListaMateria *) malloc(sizeof(nodoListaMateria));
    nodo->materia = NULL;
    nodo->proximo = NULL;
    return nodo;
}


// creo una materia
Materia* crearMateria(char nombre[100], int anio){
    Materia* materiaNueva = (Materia*)malloc(sizeof(Materia));
    strcpy(materiaNueva->nombre, nombre);
    materiaNueva->anio = anio;
    materiaNueva->notas[0] = 0;
    materiaNueva->notas[1] = 0;
    materiaNueva->notas[2] = 0;
    materiaNueva->promedio = 0.0;
    return materiaNueva;
}

//  Crea un nuevo nodo materia 
nodoListaMateria* crearNodoMateria(Materia* materiaNueva){
    nodoListaMateria *nodo = (nodoListaMateria *) malloc(sizeof(nodoListaMateria));
    nodo->materia = materiaNueva;
    nodo->proximo = NULL;
    return nodo;
}

//Agrega a la lista de materias una materia nueva
nodoListaMateria* darAltaMateria(nodoListaMateria** lista, Materia* nombreMateria){
    nodoListaMateria *nuevoNodo = crearNodoMateria(nombreMateria);
    // si la lista esta vacia, le añado un nodo.
    if ((*lista)->materia == NULL) { 
        *lista = nuevoNodo;
    }
    else {
        nodoListaMateria *cursor = *lista;
        //Si existe otro nodo, muevo el cursor a ese nodo
        while (cursor->proximo != NULL) { 
            cursor = cursor->proximo;
        }
        // si no existe otro nodo.. agregamos uno
        cursor->proximo = nuevoNodo; 
    }
}


//    Devuelve el largo de una lista de referencias de materias
int obtenerCantMaterias(nodoListaMateria **lista) {
    int largo = 0;
    nodoListaMateria *cursor = *lista;
    while (cursor != NULL) {
        cursor = cursor->proximo;
        largo++;
    }
    return largo;
}


  // Busca materia en lista por ID
nodoListaMateria* buscarMateriaPorID(nodoListaMateria *lista, int id){
    int contador = 1;
    nodoListaMateria* cursor = lista;
    while(cursor != NULL){
        if(contador == id){
            return cursor; 
        }
        cursor = cursor->proximo; 
        contador++;
    }
    return NULL;
}


//  Recibe la lista de referencias de materias y las lista
void getListaMaterias(nodoListaMateria *lista) {

    nodoListaMateria *cursor = lista;
    if(lista->materia == NULL){
        printf("La lista esta vacia!");
        return;
    }
    
    while (cursor != NULL) {
        printf("[ID: %d, Nombre: %s, Año: %d, Promedio: %.2f, Notas: %d,%d,%d] -> \n", contador + 1, cursor->materia->nombre, cursor->materia->anio, cursor->materia->promedio, cursor->materia->notas[0], cursor->materia->notas[1],cursor->materia->notas[2]);
         cursor = cursor->proximo;
    }
}
