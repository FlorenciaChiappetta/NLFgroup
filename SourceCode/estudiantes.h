#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <ctype.h>
#include <math.h>
#include "estructuras.h"

#define EdadMinima 17
#define EdadMaxima 100
#define notaMinima 4
#define COLOR_RED     "\033[31m"
#define COLOR_RESET   "\033[0m"


//Inicializa la lista de referencias de estudiantes
nodoListaEstudiante *crearListaEstudiantes() {
    nodoListaEstudiante *nodo = malloc(sizeof(nodoListaEstudiante));
    nodo->estudiante = NULL;
    nodo->proximo = NULL;
    return nodo;
}

//creo estudiante
Estudiante* crearEstudiante(char nombre[100], char apellido[100], int legajo, int edad[2], carrera carreraAAnotarse){
    Estudiante *estudianteNuevo = malloc(sizeof(Estudiante));
    strcpy(estudianteNuevo->nombre, nombre);
    strcpy(estudianteNuevo->apellido, apellido);
    estudianteNuevo->legajo = legajo;
    if (*edad >= EdadMinima || *edad <=  EdadMaxima) {
    memcpy(estudianteNuevo->edad, edad, sizeof(int) * 2);
    }
    estudianteNuevo->materias = malloc(sizeof(nodoListaMateria));
    estudianteNuevo->materias->materia = NULL;
    estudianteNuevo->materias->proximo = NULL;
    estudianteNuevo->carreraAnotada = carreraAAnotarse;

    return estudianteNuevo;
}


//    Crea un nodo de estudiante a partir de la referencia a un estudiante
nodoListaEstudiante *crearNodoEstudiante (Estudiante* estudiante){
    nodoListaEstudiante *nodo = malloc(sizeof(nodoListaEstudiante));
    nodo->estudiante = estudiante;
    nodo->proximo = NULL;
    return nodo;
}


//imprime los datos del alumno
void getEstudiante(Estudiante* estudiante) {
    if (estudiante == NULL) {
        return;
    }
    printf("Nombre: %s", estudiante->nombre);
    printf("Apellido: %s", estudiante->apellido);
    printf("Edad: %d\n", estudiante->edad);
    printf("Legajo: %d\n\n", estudiante->legajo);
}   

//devuelve 1 si la edad del param1 es mayor o igual a la del segundo param, sino, devuelve 0
int compararEdad(int *edad1, int *edad2) {
   if (edad1 >= edad2) {
    return 1;
    }

    return 0;
}

//Agrega a la lista de referencias de materias un nuevo estudiante.Se ordena por edad.
void darAltaEstudiante(nodoListaEstudiante **lista, Estudiante* nuevoEstudiante){
    nodoListaEstudiante *nuevoNodo = crearNodoEstudiante(nuevoEstudiante);
    nodoListaEstudiante *cursor = *lista;
    nodoListaEstudiante *nodoARecolocar;

    bool nodoColocado = false;
    //sí no hay elementos en lista, añado el nuevo nodo.
    if ((*lista)->estudiante == NULL) { // queda asi
        *lista = nuevoNodo;
    }
    //si el valor de la edad nueva es MENOR o IGUAL al de la primera posicion...
    else if (compararEdad(nuevoNodo->estudiante->edad, cursor->estudiante->edad) <= 0) {
        nuevoNodo->proximo = *lista;
        *lista = nuevoNodo;
    //si el valor es MAYOR al de la primera posicion...
    } else {
        while (cursor->proximo != NULL && nodoColocado == false) {
            nodoARecolocar = cursor->proximo;
            int edadEstudianteSiguiente[2]; //proximo
            int edadEstudianteActual[2];   //donde estoy parado ahora
            int edadEstudianteNuevo[2];    //el que quiero añadir

            memcpy(edadEstudianteSiguiente, nodoARecolocar->estudiante->edad, sizeof(int) * 2);
            memcpy(edadEstudianteActual, cursor->estudiante->edad, sizeof(int) * 2);
            memcpy(edadEstudianteNuevo, nuevoNodo->estudiante->edad, sizeof(int) * 2);

            if (compararEdad(edadEstudianteNuevo, edadEstudianteActual) == 1 && compararEdad(edadEstudianteNuevo, edadEstudianteSiguiente) <= 0){
                nuevoNodo->proximo = nodoARecolocar;
                cursor->proximo = nuevoNodo;
                nodoColocado = true;
            }
            cursor = cursor->proximo;
        }
        if (cursor->proximo == NULL){   //Si no coloque el nodo en el medio, significa que su posicion es la ultima
            cursor->proximo = nuevoNodo;
        }
    }
}


//Devuelve la cantidad de estudiantes
 int obtenerLongitudLista(nodoListaEstudiante **lista){
    if(*lista == NULL){
        return 0;
    }
    int largo = 0;
    nodoListaEstudiante *cursor = *lista;
    while (cursor->proximo != NULL) {
        cursor = cursor->proximo;
        largo++;
    }
    return largo + 1;
}
    
//Recibe la referencia a una materia a rendir.
// Se ingresan las 3 notas que el estudiante obtuvo durante su cursada.
//   Las guardamos junto al promedio de las 3 notas.

void rendirMateria(nodoListaMateria* materia_a_rendir){
    if(materia_a_rendir->materia->promedio==0 || materia_a_rendir->materia->promedio < 4){
        printf("Nota de primer parcial: ");
        scanf("%d",&materia_a_rendir->materia->notas[0]);
        printf("Nota de segundo parcial: ");
        scanf("%d",&materia_a_rendir->materia->notas[1]);
        printf("Nota de final: ");
        scanf("%d",&materia_a_rendir->materia->notas[2]);
        materia_a_rendir->materia->promedio = (float)(materia_a_rendir->materia->notas[0] + materia_a_rendir->materia->notas[1] + materia_a_rendir->materia->notas[2]) / 3.0;
    }else{
        printf(COLOR_RED "ERROR: Materia: '%s' ya rendida\n" COLOR_RESET, materia_a_rendir->materia->nombre);
    }
}

//Recibe una lista de referencias de estudiantes y un legajo.
//Busca y retorna la referencia al estudiante cuyo legajo coincida con el introducido.
nodoListaEstudiante* validarLegajo(nodoListaEstudiante **lista, int legajo){
    bool legajoEncontrado = false;
    nodoListaEstudiante *cursor = *lista;
    while (cursor != NULL){
        if (cursor->estudiante->legajo == legajo){
            return cursor;
        }
        cursor = cursor->proximo;
    }

    return NULL;
}


// Recibe una lista de referencias de materias de un estudiante. Calcula e imprime el promedio general considerando las materias aprobadas.

void consultarPromedio(nodoListaMateria *lista) {
    int sumaNotas = 0;
    int contadorMateriasRendidas = 0;
    nodoListaMateria *cursor = lista;

    while (cursor != NULL) {
        if (cursor->materia->promedio >= 4) {
            contadorMateriasRendidas++;
            sumaNotas += cursor->materia->promedio;
        }
        cursor = cursor->proximo;
    }

    float promedio = 0.0;
    if (contadorMateriasRendidas > 0) {
        promedio = (float) sumaNotas / contadorMateriasRendidas;
    }
    printf("Promedio: %.2f", promedio);
    
}

// Buscamos un estudiante por nombre.
void buscarEstudiantePorNombre(nodoListaEstudiante **lista, char nombre[100]){
    nodoListaEstudiante* cursor = *lista;
    bool estudianteEncontrado = false;
    while(cursor != NULL){
        if(strcmp(cursor->estudiante->nombre, nombre) == 0){
            printf("[Nombre: %s, Apellido: %s, Legajo: %d, edad: %d%d)] -> \n ", cursor->estudiante->nombre, cursor->estudiante->apellido, cursor->estudiante->legajo, cursor->estudiante->edad[0],cursor->estudiante->edad[1]);
            estudianteEncontrado = true;
        }
        cursor = cursor->proximo;
    }

    if(!estudianteEncontrado){
        printf("No existe un estudiante con ese nombre!");
    }

    return; 
}

void buscarEstudiantePorLegajo(nodoListaEstudiante **lista, int legajo){
nodoListaEstudiante* cursor = *lista;
    bool estudianteEncontrado = false;
    while(cursor != NULL){
        if(cursor->estudiante->legajo == legajo){
            printf("[Nombre: %s, Apellido: %s, Legajo: %d, edad: %d%d)] -> \n ", cursor->estudiante->nombre, cursor->estudiante->apellido, cursor->estudiante->legajo, cursor->estudiante->edad[0],cursor->estudiante->edad[1]);
            estudianteEncontrado = true;
        }
        cursor = cursor->proximo;
    }

    if(!estudianteEncontrado){
        printf("No existe un estudiante con ese nombre!");
    }

    return; 
}

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
    int contador;
    contador  = 0;
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
