#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "estudiantes.h"
#include "materias.h"
#define COLOR_RED     "\033[31m"
#define COLOR_RESET   "\033[0m"

typedef enum {false, true} bool;
typedef enum {computacion,sonido} carrera;

const char *nombresCarreras[] = {
  "Computacion",
  "Sonido",
  "Ambiental",
};


nodoListaEstudiante *listaDeEstudiantes = NULL;
nodoListaEstudiante *estudianteSeleccionado = NULL;


int main() {
    setbuf(stdout, 0);
    Bienvenida();
    int running = 1;
    int opcionElegida;
    scanf("%s", opcionElegida);
    while (running) {
        switch (opcionElegida) {
            case 1:
                realizarConsultas();
                break;
            case 2:
                abmRegistros();
                break;
            case 3:
                running = 0;
                break;
            default:
                printf("La opcion ingresada es incorrecta.Por favor, intente de nuevo.\n\n");
                break;
        }
    }
    menuFinalizar();

    return 0;
}

/*
int scan() {

    //clean del buffer
    fflush(stdin);
    char option[4];
    fgets(option, 4, stdin);
    fflush(stdin);
    printf("\n");
    // seteamos como integer 
    return (int) strtol(option, NULL, 10);
}
*/

void realizarConsultas() {
    int running = 1;
    int opcionElegida;
   /* printf("Elija una de las siguientes opciones:\n\n");
    printf("1 Buscar estudiantes\n");
    printf("2 Obtener promedio de estudiante\n");
    printf("3 Obtener materias de estudiante\n");
    */
    menuOpcionesConsultas();
    scanf("%d", &opcionElegida);
    while (running) {

        switch (opcionElegida) {
            case 4:
                running = 0;
                break;
            case 1:
                int opcion;
                printf("Elija una opción\n");
                printf("1. Buscar estudiante por nombre\n");
                printf("2. Buscar estudiante por legajo\n");
                scanf("%d", &opcion);
                switch (opcion) {
                case 1:
                char nombreAlumno[100];
                printf("Ingrese el nombre del alumno. ");
                scanf("%s", nombreAlumno);
                buscarEstudiantePorNombre(&listaDeEstudiantes, nombreAlumno);
                break;
                case 2:
                    printf("Ingrese el numero de legajo.\n");
                    int legajo;
                    scanf("%d", &legajo);
                   // buscarEstudiantePorLegajo(&listaDeEstudiantes, legajo); 
                    break;
            case 2:
                //solicitamos legajo
                printf("Ingrese el numero de legajo.\n");
                int legajo;
                scanf("%d", &legajo);
                nodoListaEstudiante* estudiante = validarLegajo(&listaDeEstudiantes, legajo); 
                consultarPromedio(estudiante->estudiante->materias); 
                break;
            case 3:
                //solicitamos legajo
                printf("Ingrese el numero de legajo.\n");
                int legajo;
                scanf("%d", &legajo);
                nodoListaEstudiante* estudiante = validarLegajo(&listaDeEstudiantes, legajo); 
                getListaMaterias(estudiante->estudiante->materias); 
                break;
            default:
                printf("La opcion ingresada es incorrecta.Por favor, intente de nuevo.\n\n");
                break;
        }
    }
}

void abmRegistros() {
    int running = 1;
    while (running) {
        int opcionElegida;
        menuOpcionesABM();
        scanf("%s", opcionElegida);

   /*printf("Elija una de las siguientes opciones:\n\n");
    printf("1 Agregar materia\n");
    printf("2 Agregar estudiante\n");
    printf("3 Inscribir estudiante en materia\n");
    printf("4 Registrar nota\n");
    printf("5 Volver al menu principal\n");*/ 

        switch (opcionElegida) {
            case 1:
                printf("Seleccione la carrera:\n");
                char path[116] = ".\\carreras\\";
                elegirCarrera(path);
                agregarMateriaABaseDeDatos(path);
                break;
            case 2:
                printf("Ingrese la informacion del estudiante:\n");
                char nombre[100];
                printf("Nombre: ");
                scanf("%s", nombre);
                char apellido[100];
                printf("Apellido: ");
                scanf("%s", apellido);
                int legajo;
                printf("Legajo: ");
                scanf("%d", &legajo);
                int opcionCarrera;
                carrera carreraAAnotarse;
                printf("\n\033[1m--CARRERAS DISPONIBLES--\033[0m\n");
                printf("1) Ingeniería en computación\n2)Ingeniería en sonido");
                printf("Elegir carrera: ");
                scanf("%d",&opcionCarrera);
                if(opcionCarrera==1){
                    carreraAAnotarse=computacion;
                }else if(opcionCarrera==2){
                    carreraAAnotarse=sonido;
                }
                }else{
                    printf(COLOR_RED"ERROR: Carrera no encontrada"COLOR_RESET);
                    break;
                }
                int edad[2];
                printf("Edad:\n");
                scanf("%d", &edad[2]);
                if (listaDeEstudiantes == NULL){  
                    // Compruebo unicamente la ordenada por edad ya que ambas listas van de la mano
                    listaDeEstudiantes = crearListaEstudiantes(); 
                    Estudiante *aux = crearEstudiante(nombre,apellido,legajo,fechaDeNacimiento, carreraAAnotarse);    
                    darAltaEstudiante(&listaDeEstudiantes, aux);    
                }   else{
                    Estudiante *aux = crearEstudiante(nombre,apellido,legajo,edad, carreraAAnotarse);    
                    darAltaEstudiante(&listaDeEstudiantesXEdad, aux);
                }
                break;
            case 3:
                printf("Seleccione la carrera:\n");
                char pathListar[116] = ".\\carreras\\";
                // Se elige la carrera (el csv)
                obtenerPathDeArchivoAPartirDeCarrera(pathListar,estudiante);
                // Se paginan las materias del csv
                bool pedirAnotarID = paginarMateriasDeArchivo(pathListar,false);
                    
                if(pedirAnotarID){ //Si el usuario eligio la opcion 'Seleccionar ID de materia'
                    printf("Indique ID: ");
                    int idAnotar;
                    scanf("%d",&idAnotar);
                    // En base al id de la materia introducida, se busca y obtiene esa materia
                    Materia *materiaAAnotarse = buscarIDMateriaArchivo(idAnotar, pathListar);
                        
                    if(materiaAAnotarse != NULL){ //Si se encontro la materia
                        anotarMateria(materiaAAnotarse, estudiante,pathListar);
                        }
                    }
                    break;
            case 4:
                
                break;
            case 5:
                running = 0;
                break;
            default:
                printf("La opcion ingresada es incorrecta.Por favor, intente de nuevo.\n\n");
        }
    }
}


