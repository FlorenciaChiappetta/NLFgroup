#include "materias.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define COLOR_RED     "\033[31m"
#define COLOR_RESET   "\033[0m"

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




void elegirCarrera(char* path){
    bool salir = false;
    while(!salir){
        int opcion;
        printf("1. Ingenieria de computacion\n");
        printf("2. Ingenieria de sonido\n");
        printf("\nIngrese una opcion: ");
        scanf("%d", &opcion);
        
        switch (opcion)
        {
        case 1:
            strcat(path, "ing-computacion.csv");
            salir=true;
            break;
        case 2:
            strcat(path, "ing-sonido.csv");
            salir=true;
            break;
        default:
            printf(COLOR_RED"ERROR: Opción no encontrada\n"COLOR_RESET);
            break;
        }
    }
}


void obtenerPathDeArchivoAPartirDeCarrera(char* path, nodoListaEstudiante* estudiante){
    if(estudiante->estudiante->carreraAnotada == computacion){
        strcat(path, "ing-computacion.csv");
    }else if(estudiante->estudiante->carreraAnotada == sonido){
        strcat(path, "ing-sonido.csv");
    }
    }


//Agrega materias al archivo .csv pasado por parámetro
void agregarMateriaABaseDeDatos(char* path){
    //Limpiamos el buffer.
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
    
    FILE *fh = fopen(path, "a");
    if (fh == NULL) {
        printf(COLOR_RED"ERROR: No se pudo abrir el archivo: %s.\n"COLOR_RESET, path);
        return;
    }

    char nombre[100];
    char anio[20];

    printf("Nombre: ");
    fgets(nombre, 100, stdin);
    strcpy(nombre, formatearInput(nombre));
    
    printf("Año: ");
    fgets(anio, 20, stdin);
    strcpy(anio, formatearInput(anio));
    
    char result[120];
    strcpy(result, "\n");
    strcat(result, nombre);
    strcat(result, ",");
    strcat(result, anio);
    
    fputs(result, fh);
    fflush(fh); // Forzar la escritura del búfer al archivo
    fclose(fh); // Cierra el archivo
}


//Devuelve cantidad de materias del archivo pasado por parámetro

int contarMaterias(char * nombreArc){
    FILE *pa = fopen(nombreArc,"r");
    if(pa==NULL){
        printf(COLOR_RED"ERROR: No se pudo abrir el archivo: %s\n"COLOR_RESET, nombreArc);
        return -1;
    }
    int n=0; //cantidad de materias
    char c=fgetc(pa);
    while(!feof(pa)){
        if(c=='\n') n++;
        c = fgetc(pa);
    }
    fclose(pa);
    return n;
}

//Lee una línea, la separa por comas, e imprime ID, Nombre de Materia y Año (orden)
void imprimirLineaDeArchivo(char *linea, int id){
    char nombre[100];
    char anio[100];
    int j=0;
    int i=0;

    //obtenemos materia
    while(linea[i] != ','){
        nombre[j++] = linea[i++];
    }
    nombre[j] = '\0'; // Agregamos el terminador de cadena nulo
    printf("(ID: %d) - Materia: %s, ", id, nombre);
    i++; //salto la coma

    j=0;
    //Obtenemos grado
    while(linea[i]!='\0'){
        anio[j++] = linea[i++];
    }

    anio[j] = '\0'; // Agregamos el terminador de cadena nulo
    int anioNro = atoi(anio);
    printf("Año: %d  \n", anioNro);
}
//lista las materias.

void listarMateriasDeArchivo(char* path, int pagina){
    FILE *pEnt = fopen(path,"r"); //path de entrada (pEnt)
    int n = contarMaterias(path);
    
    if(n == 0){
        printf(COLOR_RED"ERROR: No existe ninguna materia en la base de datos!"COLOR_RESET);
        return;
    }

    if(n == -1){
        return;
    }

    //APERTURA
    if(pEnt==NULL){
        printf(COLOR_RED"ERROR: No se pudo abrir el archivo.\n"COLOR_RESET);
        return;
    }
    //Llegamos a la segunda linea
    char linea[1000];
    fgets(linea,sizeof(linea),pEnt); //Titulos de los campos 


    int contador = 0;
    int inicio = (pagina - 1) * 10;
    int final = inicio + 10;
    
    while(contador < n && contador < final){
        fgets(linea,1000,pEnt);
        if(contador >= inicio){
            imprimirLineaDeArchivo(linea, contador+1);
        }
        contador++;
    }
}



//Busca ID de materia (número de línea) desde un archivo.
Materia *buscarIDMateriaArchivo(int id, char* path){
    char nombre[100];
    char anio[2];

    FILE *pEnt = fopen(path,"r"); //path de entrada (pEnt)
    int n = contarMaterias(path);

    if(id <= 0 || id > n){
        printf(COLOR_RED"ERROR: La materia con el ID: %d no fue encontrada!\n"COLOR_RESET, id);
        return NULL;
    }
    //APERTURA
    if(pEnt==NULL){
        printf(COLOR_RED"ERROR: No se pudo abrir el archivo: %s\n"COLOR_RESET, path);
        return NULL;
    }
    //Llegamos a la segunda linea
    char linea[1000];
    fgets(linea,sizeof(linea),pEnt); //Titulos de los campos 

    int contador = 1;
    
    while(contador <= n ){
        fgets(linea,1000,pEnt);
        if(contador == id){
            // Guardamos en nombre todos los caracteres hasta la coma
            // Guardamos en anio lo que le sigue a la coma
            sscanf(linea, "%[^,],%s", nombre, anio);
        }
        contador++;
    }
    Materia *materia = crearMateria(nombre, atoi(anio));
    return materia;
}