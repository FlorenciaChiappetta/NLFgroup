#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "estructuras.h"
#include "Helpers/helpers.h"

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
    printf("Edad: %d\n", *estudiante->edad);
    printf("Legajo: %d\n\n", estudiante->legajo);
}

void listaDeMaterias(nodoListaMateria *lista, int pagina) {
    int contador = 0;
    int inicio = (pagina - 1) * 2; // 2
    int final = inicio + 2; //4
    nodoListaMateria *cursor = lista;

    if(lista->materia == NULL){
        printf("La lista esta vacia!");
        return;
    }

    while (cursor != NULL && contador < final) {
        if(contador >= inicio){
          printf("[ID: %d, Nombre: %s, Anio: %d, Promedio: %.2f, Notas: %d,%d,%d] -> \n", contador + 1, cursor->materia->nombre, cursor->materia->anio, cursor->materia->promedio, cursor->materia->notas[0], cursor->materia->notas[1],cursor->materia->notas[2]);
        }
        contador++;
        cursor = cursor->proximo;
    }
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

void rendirMateria(nodoListaMateria* materiaArendir){
    if(materiaArendir->materia->promedio==0 || materiaArendir->materia->promedio < 4){
        printf("Nota de primer parcial: ");
        materiaArendir->materia->notas[0] = validateIntInput();
        printf("Nota de segundo parcial: ");
        materiaArendir->materia->notas[1] = validateIntInput();
        printf("Nota de final: ");
        materiaArendir->materia->notas[2] = validateIntInput();
        materiaArendir->materia->promedio = (float)(materiaArendir->materia->notas[0] + materiaArendir->materia->notas[1] + materiaArendir->materia->notas[2]) / 3.0;
    }else{
        printf(COLOR_RED "ERROR: Materia: '%s' ya rendida\n" COLOR_RESET, materiaArendir->materia->nombre);
    }
}

//Recibe una lista de referencias de estudiantes y un legajo.
//Busca y retorna la referencia al estudiante cuyo legajo coincida con el introducido.
nodoListaEstudiante* validarLegajo(nodoListaEstudiante **lista, int legajo){
    if(lista == NULL){
        printf("No hay estudiantes cargados!");
        return NULL;
    }

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
    printf("Promedio: %.2f\n", promedio);

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
        printf("\nNo existe un estudiante con ese nombre!\n\n");
    }

    return;
}

void buscarEstudiantePorLegajo(nodoListaEstudiante **lista, int legajo){
nodoListaEstudiante* cursor = *lista;
    bool estudianteEncontrado = false;
    while(cursor != NULL){
        if(cursor->estudiante->legajo == legajo){
            printf("[Nombre: %s, Apellido: %s, Legajo: %d, edad: %d%d)]\n ", cursor->estudiante->nombre, cursor->estudiante->apellido, cursor->estudiante->legajo, cursor->estudiante->edad[0],cursor->estudiante->edad[1]);
            estudianteEncontrado = true;
        }
        cursor = cursor->proximo;
    }

    if(!estudianteEncontrado){
        printf("\nNo existe un estudiante con ese legajo!\n\n");
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
void darAltaMateria(nodoListaMateria** lista, Materia* nombreMateria){
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

int obtenerAnioMateria(char *linea){
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

void obtenerMateria(char *linea, char* materia){
    int j=0;
    int i=0;

    //obtenemos materia
    while(linea[i] != ','){
        materia[j++] = linea[i++];
    }
    materia[j] = '\0';
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




// Funcion que valida si fueron aprobadas las materias de años anteriores
//    Devuelve false si:
//   - Se esta intentando anotar como primer materia a una de año mayor a 1
//    - No fueron aprobadas todas las materias de años anteriores a la que el estudiante desea anotarse
//    - Errores inesperados: el archivo no pudo abrirse, el archivo no tiene materias
//    Si no devuelve true

bool ValidarMateria(Materia *materiaAnotar, nodoListaEstudiante *nodoEstudiante, char* path){
    // Si el estudiante se esta anotando a su primer materia
    if(nodoEstudiante->estudiante->materias->materia == NULL){
        // Si el año de la materia es mayor a 1: no esta autorizado
            return true;
    }

    FILE *INput = fopen(path,"r");
    int n = contarMaterias(path);

    //Si el archivo no tiene materias
    if(n == 0){
        printf(COLOR_RED "ERROR: No existe ninguna materia" COLOR_RESET);
        return false;
    }

    //Si el archivo no se pudo abrir (contarMaterias imprimio el error)
    if(n == -1){
        return false;
    }

    //Llegamos a la segunda linea
    char linea[1000];
    fgets(linea,sizeof(linea),INput); //Titulos de los campos

    int anio = 0;
    char materia[100];

    //Se recorre el CSV hasta llegar a la materia que sea del mismo año que a la que se quiere anotar
    while(materiaAnotar->anio > anio){
        fgets(linea,1000,INput);
        anio = obtenerAnioMateria(linea);
        obtenerMateria(linea, materia); //Obtenemos nombre de materia de linea de archivo

        nodoListaMateria* cursor = nodoEstudiante->estudiante->materias;
        //Recorremos la lista de materias
        //Comprobamos que el alumno aprobo la materia sobre la que estamos parados (una materia de año anterior a la que se quiere anotar)
        while (cursor!=NULL){
            if(strcmp(cursor->materia->nombre, materia) == 0){
                // Si la materia no fue aprobada
                if(cursor->materia->promedio < 4 && materiaAnotar->anio > anio){
                    printf(COLOR_RED "Alumno no autorizado para inscripción. Materia: %s\n no aprobada en ciclo anterior..", materiaAnotar->nombre);
                    return false;
                }
            }
            cursor = cursor -> proximo;
        }
    }

    //Si todas las materias de años anteriores a la que se quiere anotar fueron aprobadas
    return true;
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
        printf("El estudiante no está anotado a ninguna materia.\n");
        return;
    }

    while (cursor != NULL) {
        printf("[ID: %d, Nombre: %s, Año: %d, Promedio: %.2f, Notas: %d,%d,%d] -> \n", contador + 1, cursor->materia->nombre, cursor->materia->anio, cursor->materia->promedio, cursor->materia->notas[0], cursor->materia->notas[1],cursor->materia->notas[2]);
         cursor = cursor->proximo;
    }
}
//permite elegir una carrera
void elegirCarrera(char* path){
    bool salir = false;
    while(!salir){
        printf("1. Ingenieria de computacion\n");
        printf("2. Ingenieria de sonido\n");
        printf("\nIngrese una opcion: ");
        int opcion = validateIntInput();

        switch (opcion)
        {
        case 1:
            strcat(path, "IngenieriaEnComputacion.csv");
            salir=true;
            break;
        case 2:
            strcat(path, "IngenieriaEnSonido.csv");
            salir=true;
            break;
        default:
            printf(COLOR_RED"ERROR: Opción no encontrada\n"COLOR_RESET);
            salir = false;
            break;
        }
    }
}
//Formatea el dato obtenido de fgets
//le agrega un \0 para que no se agregue un salto de linea cuando se agrega la materia.
char* formatearInput(char* nombre){
    if ((strlen(nombre) > 0) && (nombre[strlen (nombre) - 1] == '\n'))
        nombre[strlen (nombre) - 1] = '\0';
    return nombre;
}

//agrega materias a partir de un CSV
void agregarMateriaEnArchivoCSV(char* path){
    //Limpiamos el buffer
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

    char* nombreFormateado = formatearInput(nombre);

    printf("Año: ");
    fgets(anio, 20, stdin);
    char* anioFormateado = formatearInput(anio);

    char result[120];
    strcpy(result, "\n");
    strcat(result, nombreFormateado);
    strcat(result, ",");
    strcat(result, anioFormateado);

    fputs(result, fh);
    fflush(fh); // Forzar la escritura del búfer al archivo

    fclose(fh); // Cierra el archivo
}


void obtenerRutaDelArchivoxCarrera(char* path, nodoListaEstudiante* estudiante){
    if(estudiante->estudiante->carreraAnotada == computacion){
        strcat(path, "IngenieriaEnComputacion.csv");
    }else if(estudiante->estudiante->carreraAnotada == sonido){
        strcat(path, "IngenieriaEnSonido.csv");
    }
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

//Lista las materias del archivo CSV
void listarMaterias(char* path, int pagina){
    FILE *input = fopen(path,"r");
    int n = contarMaterias(path);

    if(n == 0){
        printf(COLOR_RED"ERROR: No existe ninguna materia en la base de datos"COLOR_RESET);
        return;
    }

    if(n == -1){
        return;
    }

    //APERTURA
    if(input==NULL){
        printf(COLOR_RED"ERROR: No se pudo abrir el archivo.\n"COLOR_RESET);
        return;
    }
    //Llegamos a la segunda linea
    char linea[1000];
    fgets(linea,sizeof(linea),input); //Titulos de los campos


    int contador = 0;
    int inicio = (pagina - 1) * 10;
    int final = inicio + 10;

    while(contador < n && contador < final){
        fgets(linea,1000,input);
        if(contador >= inicio){
            imprimirLineaDeArchivo(linea, contador+1);
        }
        contador++;
    }
}

//Busca ID de materia (número de línea) desde un archivo.
Materia *buscarIDMateriaArchivo (int id, char* path){
    char nombre[100];
    char anio[2];

    FILE *input = fopen(path,"r"); //path de entrada (pEnt)
    int n = contarMaterias(path);

    if(id <= 0 || id > n){
        printf(COLOR_RED"ERROR: La materia con el ID: %d no fue encontrada\n"COLOR_RESET, id);
        return NULL;
    }
    //APERTURA
    if(input==NULL){
        printf(COLOR_RED"ERROR: No se pudo abrir el archivo: %s\n"COLOR_RESET, path);
        return NULL;
    }
    //Llegamos a la segunda linea
    char linea[1000];
    fgets(linea,sizeof(linea),input); //Titulos de los campos

    int contador = 1;

    while(contador <= n ){
        fgets(linea,1000,input);
        if(contador == id){
            // Guardamos en nombre todos los caracteres hasta la coma
            // Guardamos en año lo que le sigue a la coma
            sscanf(linea, "%[^,],%s", nombre, anio);
        }
        contador++;
    }
    Materia *materia = crearMateria(nombre, atoi(anio));
    return materia;
}

bool ListarMaterias(char* path,bool seleccionar_id){
    int cantidadDeMaterias = contarMaterias(path);
    if(cantidadDeMaterias == -1){
        return false;
    }
    if(cantidadDeMaterias == 0){
        printf(COLOR_RED"ERROR: No existe ninguna materia."COLOR_RESET);
        return false;
    }

    int pagina = 1;
    int materiasPorPagina = 10;
    int numPaginaMaxima = (int) ceil((double) cantidadDeMaterias / materiasPorPagina);

    bool salir = false;
    while(!salir){
        printf("Lista de materias:\n");
        listarMaterias(path, pagina);
        printf("\n\033[1m[Página %d/%d]\033[0m\n", pagina, numPaginaMaxima);

        printf("\033[1m--------------------------------------------------------------------------------------------\n");
        printf("0. Volver\t");
        printf("1. Página siguiente \t");
        printf("2. Página anterior \t");
        if(!seleccionar_id){
            printf("3. Seleccionar ID de materia\t");
        }
        printf("\n----------------------------------------------------------------------------------------------------\033[0m\n");

        printf("\nIngrese una opcion: ");
        int opcion = validateIntInput();
        switch (opcion)
        {
        case 0:
            salir = true;
            break;
        case 1:
            if(pagina == numPaginaMaxima)
                printf(COLOR_RED"\nNo existen mas registros.\n"COLOR_RESET);
            else pagina++;
            break;
        case 2:
            if(pagina == 1)
                printf(COLOR_RED"\nNo existen registros previos.\n"COLOR_RESET);
            else pagina--;
            break;
        case 3:
            if(!seleccionar_id){
                return true;
            }
        default:
            printf(COLOR_RED"\nERROR: Opcion no encontrada\n"COLOR_RESET);
        }
    }

    return false; //Si el usuario no selecciono un ID
}

void anotarMateria(Materia *materiaAnotar, nodoListaEstudiante *nodoEstudiante, char* path) {
    nodoListaMateria *cursor = nodoEstudiante->estudiante->materias;
    while(cursor != NULL){
        //Si el estudiante ya esta anotado en la materia
        if(cursor->materia->nombre != NULL && strcmp(cursor->materia->nombre, materiaAnotar->nombre) == 0){
            printf(COLOR_RED "ERROR: La materia: '%s' ya fue cursada o bien ya se encuentra inscripto\n" COLOR_RESET, materiaAnotar->nombre);
            return;
        }
        cursor = cursor->proximo;
    }

    if(ValidarMateria(materiaAnotar, nodoEstudiante, path)){
        darAltaMateria(&nodoEstudiante->estudiante->materias,materiaAnotar);
        printf("\nInscripción exitosa %s\n", materiaAnotar->nombre);
    } else {
        printf("\nError: Inscripción fallida! %s\n", materiaAnotar->nombre);
    }
}

int obtenerLenghtMaterias(nodoListaMateria **lista) {
    int largo = 0;
    nodoListaMateria *cursor = *lista;
    while (cursor != NULL) {
        cursor = cursor->proximo;
        largo++;
    }
    return largo;
}

bool ListarMateriasEstudiante(nodoListaMateria *lista, bool seleccionarID){

    int cantidadDeMaterias = obtenerLenghtMaterias(&lista);
    if(cantidadDeMaterias == 0){
        printf("No existe ninguna materia.");
        return false;
    }

    int pagina = 1;
    int materiasPorPagina = 2;
    int numPaginaMaxima = (int) ceil((double) cantidadDeMaterias / materiasPorPagina);

    bool salir = false;
    while(!salir){
        printf("\nLista de materias:\n");
        listaDeMaterias(lista, pagina);
        printf("\n\033[1m[Página %d/%d]\033[0m\n", pagina, numPaginaMaxima);

        printf("\033[1m--------------------------------------------------------------------------------------------\n");
        printf("0. Volver\t");
        printf("1. Página siguiente \t");
        printf("2. Página anterior \t");
        if(!seleccionarID){
            printf("3. Seleccionar ID de materia\t");
        }
        printf("\n----------------------------------------------------------------------------------------------------\033[0m\n");

        printf("\nIngrese una opcion: ");
        int opcion = validateIntInput();
        switch (opcion)
        {
            case 0:
                salir = true;
                break;
            case 1:
                if(pagina == numPaginaMaxima)
                    printf(COLOR_RED"\nNo existen mas registros.\n"COLOR_RESET);
                else pagina++;
                break;
            case 2:
                if(pagina == 1)
                    printf(COLOR_RED"\nNo existen registros previos.\n"COLOR_RESET);
                else pagina--;
                break;
            case 3:
                if(!seleccionarID){
                    return true;
                }
            default:
                printf(COLOR_RED"\nERROR: Opcion no encontrada\n"COLOR_RESET);
        }
    }

    return false; //Si el usuario no selecciono un ID
}

void eliminarMateriaEnArchivoCSV(char* path) {
    //Limpiamos el buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}

    FILE *fh = fopen(path, "r");
    if (fh == NULL) {
        printf(COLOR_RED"ERROR: No se pudo abrir el archivo: %s.\n"COLOR_RESET, path);
        return;
    }

    FILE *temp = fopen("temp.csv", "w");
    if (temp == NULL) {
        printf(COLOR_RED"ERROR: No se pudo abrir el archivo temporal.\n"COLOR_RESET);
        return;
    }

    char nombre[100];
    char anio[20];

    printf("Nombre: ");
    fgets(nombre, 100, stdin);

    char* nombreFormateado = formatearInput(nombre);

    printf("Año: ");
    fgets(anio, 20, stdin);
    char* anioFormateado = formatearInput(anio);

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fh) != NULL) {
        char* nombreArchivo = strtok(buffer, ",");
        char* anioArchivo = strtok(NULL, ",");

        if (strcmp(nombreFormateado, nombreArchivo) != 0 || strcmp(anioFormateado, anioArchivo) != 0) {
            fputs(buffer, temp);
        }
    }

    fclose(fh);
    fclose(temp);

    remove(path);
    rename("temp.csv", path);
}

int obtenerLenghtEstudiantes(nodoListaEstudiante **lista) {
    int largo = 0;
    nodoListaEstudiante *cursor = *lista;
    while (cursor != NULL) {
        cursor = cursor->proximo;
        largo++;
    }
    return largo;
}


void buscarEstudiantePorRangoEdad(nodoListaEstudiante **lista,int edadMinima[2], int edadMaxima[2]){
    nodoListaEstudiante *cursor = *lista;
 while(cursor != NULL){
    if (cursor->estudiante->edad >= edadMinima || cursor->estudiante->edad <= edadMaxima){
        printf("[Nombre: %s, Apellido: %d, Edad, %d, Legajo: %.2f \n", cursor->estudiante->nombre, cursor->estudiante->apellido,cursor->estudiante->edad,cursor->estudiante->legajo);
    }
 }

}