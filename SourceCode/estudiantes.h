#include "materias.h"
#include <string.h>
#define EdadMinima 17
#define EdadMaxima 100
#define notaMinima 4
#define COLOR_RED     "\033[31m"
#define COLOR_RESET   "\033[0m"

typedef enum {false, true} bool;
typedef enum {computacion,sonido} carrera;

const char *nombresCarreras[] = {
  "Computacion",
  "Sonido",
  "Ambiental",
};

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



//    Crea un nodo de estudiante a partir de la referencia a un estudiante
nodoListaEstudiantes *crearNodoEstudiante (Estudiante* estudiante){
    nodoListaEstudiantes *nodo = malloc(sizeof(nodoListaEstudiantes));
    nodo->estudiante = estudiante;
    nodo->next = NULL;
    return nodo;
}

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
    if (edad >= EdadMinima || edad <=  EdadMaxima) {
    memcpy(estudianteNuevo->edad, edad, sizeof(int) * 2);
    }
    estudianteNuevo->materias = malloc(sizeof(nodoListaMateria));
    estudianteNuevo->materias->materia = NULL;
    estudianteNuevo->materias->proximo = NULL;
    estudianteNuevo->carreraAnotada = carreraAAnotarse;

    return estudianteNuevo;
}

//imprime los datos del alumno
void getEstudiante(Estudiante* nuevoEstudiante) {
    if (estudiante == NULL) {
        return;
    }
    printf("Nombre: %s", estudiante->nombre);
    printf("Apellido: %s", estudiante->apellido);
    printf("Edad: %d\n", estudiante->edad);
    printf("Legajo: %d\n\n", estudiante->legajo);
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

//devuelve 1 si la edad del param1 es mayor o igual a la del segundo param, sino, devuelve 0

int compararEdad(int *edad1, int *edad2) {
   if (edad1 >= edad2) {
    return 1
   }

    return 0;
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

//busco el nombre de materia de linea de archivo
void obtenerMateria(char *linea, char* materia){
    int j=0;
    int i=0;

    //obtenemos materia
    while(linea[i] != ','){
        materia[j++] = linea[i++];
    }
    materia[j] = '\0'; // Agregamos el terminador de cadena nulo
}

// devuelve el año que corresponde a la linea del archivo
int obtenerAnio(char *linea){
    char anio[100];
    int j=0;
    int i=0;

    //llego hasta la coma
    while(linea[i] != ','){
        i++;
    }
    i++; //salto la coma

    j=0;
    //Obtenemos grado
    while(linea[i]!='\0'){
        anio[j++] = linea[i++];
    }

    anio[j] = '\0'; // Agregamos el terminador de cadena nulo
    int anioNro = atoi(anio);

    return anioNro;
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

//valida si fueron aprobadas las materias de años anteriores para poder anotarte en una materia
//Devuelve false si:
//- Se esta intentando anotar como primer materia a una de año mayor a 1
//- No fueron aprobadas todas las materias de años anteriores a la que el estudiante desea anotarse
//    Si no devuelve true

bool aproboMateriasDeAniosAnteriores(Materia *materia_a_anotar, nodoListaEstudiante *nodoEstudiante, char* path){
    
    // Si el estudiante se esta anotando a su primer materia
    if(nodoEstudiante->estudiante->materias->materia == NULL){
        // Si el año de la materia es mayor a 1: no esta autorizado
        if(materia_a_anotar->anio > 1){
            return false;
        } else{
            return true;
        }
    }
    
    FILE *pEnt = fopen(path,"r"); 
    int n = contarMaterias(path);
    
    //Si el archivo no tiene materias
    if(n == 0){
        printf(COLOR_RED "ERROR: No existe ninguna materia en la base de datos" COLOR_RESET);
        return false;
    }

    //Si el archivo no se pudo abrir (contarMaterias imprimio el error)
    if(n == -1){
        return false;
    }

    //Llegamos a la segunda linea
    char linea[1000];
    fgets(linea,sizeof(linea),pEnt); //Titulos de los campos 

    int anio = 0;
    char materia[100];

    //Se recorre el CSV hasta llegar a la materia que sea del mismo año que a la que se quiere anotar
    while(materia_a_anotar->anio > anio){
        fgets(linea,1000,pEnt);
        anio = obtenerAnio(linea); //Obtenemos año de la linea de archivo
        obtenerMateria(linea, materia); //Obtenemos nombre de materia de linea de archivo
        
        nodoListaMateria* cursor = nodoEstudiante->estudiante->materias;
        //Recorremos la lista de materias
        //Comprobamos que el alumno aprobo la materia sobre la que estamos parados (una materia de año anterior a la que se quiere anotar)
        while (cursor!=NULL){ 
            if(strcmp(cursor->materia->nombre, materia) == 0){
                // Si la materia no fue aprobada
                if(cursor->materia->promedio < 4 && materia_a_anotar->anio > anio){
                    printf(COLOR_RED "ERROR: No estas autorizado a anotarte a la materia: %s\n",materia_a_anotar);
                    printf("RAZON: No aprobaste todas las materias de años anteriores\n" COLOR_RESET);
                    return false;
                }
            }
            cursor = cursor -> proximo;
        }
    }

    //Si todas las materias de años anteriores a la que se quiere anotar fueron aprobadas
    return true;
}

// Recibe la referencia a una materia y la referencia a un nodo de estudiante.
//Recorro la lista de materias del estudiante para chequear que el estudiante no se haya anotado a dicha materia
// Si no lo hizo, se chequea que se hayan aprobado todas las materias de años anteriores 
void anotarMateria(Materia *materia_a_anotar, nodoListaEstudiante *nodoEstudiante, char* path) {    
    nodoListaMateria *cursor = nodoEstudiante->estudiante->materias;
    while(cursor != NULL){
        //Si el estudiante ya esta anotado en la materia
        if(cursor->materia->nombre != NULL && strcmp(cursor->materia->nombre, materia_a_anotar->nombre) == 0){
            printf(COLOR_RED "ERROR: Materia: '%s' ya cursada o en curso\n" COLOR_RESET, materia_a_anotar->nombre);
            return;
        }
        cursor = cursor->proximo;
    }
    
    if(aproboMateriasDeAniosAnteriores(materia_a_anotar, nodoEstudiante, path)){
        darAltaMateria(&nodoEstudiante->estudiante->materias,materia_a_anotar);
        printf("Te has anotado con exito en la materia: %s\n", materia_a_anotar->nombre);
    }
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