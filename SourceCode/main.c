#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "estudiantes.h"
#include "estructuras.h"


nodoListaEstudiante *listaDeEstudiantes = NULL;
nodoListaEstudiante *estudianteSeleccionado = NULL;


void realizarConsultas() {
    int opcionElegida;
    int running = 1;
    scanf("%d", &opcionElegida);
    while (running) {
        menuOpcionesConsultas();
        scanf("%d", &opcionElegida);
        switch (opcionElegida) {
            case 4:
                running = 0;
                break;
            case 1:
                printf("Elija una opción\n");
                printf("1. Buscar estudiante por nombre\n");
                printf("2. Buscar estudiante por legajo\n");
                int opcion;
                scanf("%d", &opcion);
                    if (opcion == 1){
                            printf("Ingrese el nombre del alumno:\n");
                            char nombreAlumno[100];
                            scanf("%s", nombreAlumno);
                            buscarEstudiantePorNombre(&listaDeEstudiantes, nombreAlumno);
                        }else if (opcion == 2){
                            printf("Ingrese el numero de legajo:\n");
                            int legajo;
                            scanf("%d", &legajo);
                            buscarEstudiantePorLegajo(&listaDeEstudiantes, legajo);
                        }
                break;
            case 2:
                //solicitamos legajo
                printf("Ingrese el numero de legajo.\n");
                int legajo1;
                scanf("%d", &legajo1);
                nodoListaEstudiante* estudiante = validarLegajo(&listaDeEstudiantes, legajo1); 
                consultarPromedio(estudiante->estudiante->materias); 
                break;
            case 3:
                //solicitamos legajo
                printf("Ingrese el numero de legajo.\n");
                int legajo2;
                scanf("%d", &legajo2);
                nodoListaEstudiante* estudiante2 = validarLegajo(&listaDeEstudiantes, legajo2); 
                getListaMaterias(estudiante2->estudiante->materias); 
                break;
            default:
                printf("La opcion ingresada es incorrecta.Por favor, intente de nuevo.\n\n");
                break;
        }
    }
}

void abmRegistros() {
    int running = 1;
    int opcionElegida;
    while (running) {
        menuOpcionesABM();
        scanf("%d", &opcionElegida);
        
        switch (opcionElegida) {
            case 1:
                printf("Seleccione la carrera:\n"); 
                char path[116] = ".\\materiasXcarreras\\";
                elegirCarrera(path);
                agregarMateriaEnArchivoCSV(path);
                break;
            case 2:
                printf("Ingrese la informacion del estudiante:\n");
                char nombre[100];
                printf("Nombre: ");
                scanf("%s", nombre);
                char apellido[100];
                printf("Apellido: ");
                scanf("%s", apellido);
                int edad[2];
                printf("Edad:");
                scanf("%d", &edad);
                int legajo;
                printf("Legajo: ");
                scanf("%d", &legajo);
                int opcionCarrera;
                carrera carreraAAnotarse;
                printf("\n\033[1m--OFERTA ACADEMICA--\033[0m\n");
                printf("1) Ingeniería en computación\n2)Ingeniería en sonido\n");
                printf("Elegir carrera: ");
                scanf("%d",&opcionCarrera);
                if(opcionCarrera==1){
                    carreraAAnotarse=computacion;
                }else if(opcionCarrera==2){
                    carreraAAnotarse=sonido;
                }
                else{
                    printf(COLOR_RED"ERROR: Carrera no encontrada"COLOR_RESET);
                    break;
                }
                
                if (listaDeEstudiantes == NULL){  
                    // Compruebo unicamente la ordenada por edad ya que ambas listas van de la mano
                    listaDeEstudiantes = crearListaEstudiantes(); 
                    Estudiante *aux = crearEstudiante(nombre,apellido,legajo,edad, carreraAAnotarse);    
                    darAltaEstudiante(&listaDeEstudiantes, aux);    
                }   else{
                    Estudiante *aux = crearEstudiante(nombre,apellido,legajo,edad, carreraAAnotarse);    
                    darAltaEstudiante(&listaDeEstudiantes, aux);
                }
                break;
            case 3:
                    printf("Ingrese su legajo: ");
                    int legajoEst;
                    scanf("%d", &legajoEst);
                    nodoListaEstudiante* estudiante = validarLegajo(&listaDeEstudiantes, legajoEst);
                    printf("Seleccione la carrera:\n");
                    char pathListar[116] = ".\\materiasXcarreras\\";
                    // Se elige la carrera (el csv)
                    obtenerRutaDelArchivoxCarrera(pathListar,estudiante);
                    // Se paginan las materias del csv, si el usuario selecciona una materia
                    bool ID = ListarMaterias(pathListar,false);
                    if(ID){ //Si el usuario eligio la opcion 'Seleccionar ID de materia' le pedimos el ID
                        printf("Indique ID: ");
                        int idAnotar;
                        scanf("%d",&idAnotar);
                        // En base al id de la materia introducida, se busca y obtiene esa materia
                        Materia *materiaAAnotarse = buscarIDMateriaArchivo(idAnotar, pathListar);
                        
                        if(materiaAAnotarse != NULL){ //Si se encontro la materia..
                            anotarMateria(materiaAAnotarse, estudiante,pathListar);
                        }
                    }
                    break;
            case 4:
                //elige el estudiante
                printf("Ingrese su legajo: ");
                int legajoEst2;
                scanf("%d", &legajoEst);
                nodoListaEstudiante* estudiante2 = validarLegajo(&listaDeEstudiantes, legajoEst2);
                //elige la materia
                 printf("Seleccionar ID de materia:\n");
                bool pedirIDmateria = ListarMateriasEstudiante(estudiante2->estudiante->materias, false);
                    if(pedirIDmateria){ //Si el usuario eligio la opcion 'Seleccionar ID de materia'
                        printf("Indique ID: ");
                        int idMateria;
                        scanf("%d",&idMateria);
                        // En base al id de la materia introducida, se busca y obtiene esa materia
                        nodoListaMateria *materia = buscarMateriaPorID(estudiante->estudiante->materias, idMateria);
                        //Si no se encontro la materia en base al ID
                        if(materia == NULL){ 
                            printf(COLOR_RED"ERROR: La materia con el ID: %d no fue encontrada\n"COLOR_RESET, idMateria);
                            break;
                        }
                        rendirMateria(materia);
                    }
                    break;
                break;
            case 5:
                running = 0;
                break;
            default:
                printf("La opcion ingresada es incorrecta.Por favor, intente de nuevo.\n\n");
        }
    }
}


int main() {
    int running = 1;
    int opcionElegida;
    while (running) {
        Bienvenida();
        scanf("%d", &opcionElegida);
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
