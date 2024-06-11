#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "estudiantes.h"
#include "estructuras.h"


nodoListaEstudiante *listaDeEstudiantes = NULL;
nodoListaEstudiante *estudianteSeleccionado = NULL;
//char path[116] = "./materiasXcarreras/";

void realizarConsultas() {
    int running = 1;

    while (running) {
        menuOpcionesConsultas();

        int opcionElegida = validateIntInput();
        switch (opcionElegida) {
            case 4:
                running = 0;
                break;
            case 1:
                printf("Elija una opción\n");
                printf("1. Buscar estudiante por nombre\n");
                printf("2. Buscar estudiante por legajo\n");
                printf("3. Buscar estudiante por rango de edad\n");
                int opcion = validateIntInput();
                switch (opcion) {
                    case 1:
                        printf("Ingrese el nombre del alumno. ");
                        char nombreAlumno[100];
                        scanf("%s", nombreAlumno);
                        buscarEstudiantePorNombre(&listaDeEstudiantes, nombreAlumno);
                        break;
                    case 2:
                        printf("Ingrese el numero de legajo.\n");
                        int legajo = validateIntInput();
                        buscarEstudiantePorLegajo(&listaDeEstudiantes, legajo);
                        break;
                    case 3:
                        printf("Ingrese la edad minima:\n");
                        int edadMinima = validateIntInput();
                        printf("Ingrese la edad máxima:\n");
                        int edadMaxima = validateIntInput();    
                        buscarEstudiantePorRangoEdad(&listaDeEstudiantes,&edadMinima,&edadMaxima);
                        break;
                    default:
                        printf("\nLa opcion ingresada es incorrecta.\n");
                        break;
                }
                break;
            case 2:
                //solicitamos legajo
                printf("Ingrese el numero de legajo.\n");
                int legajo1 = validateIntInput();
                nodoListaEstudiante *estudiante = validarLegajo(&listaDeEstudiantes, legajo1);
                if (estudiante == NULL) {
                    printf("No existe un estudiante con ese legajo!!\n");
                    break;
                }

                consultarPromedio(estudiante->estudiante->materias);
                break;
            case 3:
                //solicitamos legajo
                printf("Ingrese el numero de legajo.\n");
                int legajo2 = validateIntInput();
                nodoListaEstudiante *estudiante2 = validarLegajo(&listaDeEstudiantes, legajo2);
                if (estudiante2 == NULL) {
                    printf("No existe un estudiante con ese legajo!!\n");
                    break;
                }

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
    while (running) {
        menuOpcionesABM();
        int opcionElegida = validateIntInput();

        switch (opcionElegida) {
            case 1:
                printf("Seleccione la carrera:\n");
                char path1[116] = "./materiasXcarreras/";
                elegirCarrera(path1);
                agregarMateriaEnArchivoCSV(path1);
                break;
            case 2:
                // TODO hacer eliminar materia
                printf("La funcionalidad 'Eliminar Materia' no está disponible por el momento.\n");
                // char path2[116] = "./materiasXcarreras/";
                // eliminarMateriaEnArchivoCSV(path2);
                break;
            case 3:
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
                legajo = validateIntInput();
                int opcionCarrera;
                carrera carreraAAnotarse;
                printf("\n\033[1m--OFERTA ACADEMICA--\033[0m\n");
                printf("1) Ingeniería en computación\n2)Ingeniería en sonido\n");
                printf("Elegir carrera: ");
                opcionCarrera = validateIntInput();
                if (opcionCarrera == 1) {
                    carreraAAnotarse = computacion;
                } else if (opcionCarrera == 2) {
                    carreraAAnotarse = sonido;
                } else {
                    printf(COLOR_RED"ERROR: Carrera no encontrada"COLOR_RESET);
                    break;
                }

                if (listaDeEstudiantes == NULL) {
                    // Compruebo unicamente la ordenada por edad ya que ambas listas van de la mano
                    listaDeEstudiantes = crearListaEstudiantes();
                    Estudiante *aux = crearEstudiante(nombre, apellido, legajo, edad, carreraAAnotarse);
                    darAltaEstudiante(&listaDeEstudiantes, aux);
                } else {
                    Estudiante *aux = crearEstudiante(nombre, apellido, legajo, edad, carreraAAnotarse);
                    darAltaEstudiante(&listaDeEstudiantes, aux);
                }
                break;

            case 4:
                // TODO hacer eliminar estudiante
                printf("La funcionalidad 'Borrar estudiante' no está implementada por el momento.\n");

            case 5:
                printf("Ingrese su legajo: ");
                int legajoEst = validateIntInput();
                nodoListaEstudiante *estudiante = validarLegajo(&listaDeEstudiantes, legajoEst);
                if (estudiante == NULL) {
                    printf("No existe un estudiante con ese legajo\n");
                    return;
                }

                printf("Seleccione la carrera:\n");
                // Se elige la carrera (el csv)
                char path3[116] = "./materiasXcarreras/";
                obtenerRutaDelArchivoxCarrera(path3, estudiante);
                // Se paginan las materias del csv, si el usuario selecciona una materia
                bool ID = ListarMaterias(path3, false);
                if (ID) { //Si el usuario eligio la opcion 'Seleccionar ID de materia' le pedimos el ID
                    printf("Indique ID: ");
                    int idAnotar = validateIntInput();
                    // En base al id de la materia introducida, se busca y obtiene esa materia
                    Materia *materiaAAnotarse = buscarIDMateriaArchivo(idAnotar, path3);

                    if (materiaAAnotarse != NULL) { //Si se encontro la materia..
                        anotarMateria(materiaAAnotarse, estudiante, path3);
                    }
                }
                break;
            case 6:
                //elige el estudiante
                printf("Ingrese su legajo: ");
                // int legajoEst2;
                int legajoEst2 = validateIntInput();
                nodoListaEstudiante* estudiante2 = validarLegajo(&listaDeEstudiantes, legajoEst2);
                //elige la materia
                 printf("Seleccionar ID de materia:\n");
                bool pedirIDmateria = ListarMateriasEstudiante(estudiante2->estudiante->materias, false);
                if(pedirIDmateria){ //Si el usuario eligio la opcion 'Seleccionar ID de materia'
                    printf("Indique ID: ");
                    int idMateria = validateIntInput();
                    // En base al id de la materia introducida, se busca y obtiene esa materia
                    nodoListaMateria *materia = buscarMateriaPorID(estudiante2->estudiante->materias, idMateria);
                    //Si no se encontro la materia en base al ID
                    if(materia == NULL){
                        printf(COLOR_RED"ERROR: La materia con el ID: %d no fue encontrada\n"COLOR_RESET, idMateria);
                        break;
                    }
                    rendirMateria(materia);
                }
                break;
            case 7:
                running = 0;
                break;
            default:
                printf("La opcion ingresada es incorrecta.Por favor, intente de nuevo.\n\n");
        }
    }
}


// int main() {
//     int running = 1;
//     while (running) {
//         Bienvenida();

//         int opcionElegida = validateIntInput();
//         switch (opcionElegida) {
//             case 1:
//                 realizarConsultas();
//                 break;
//             case 2:
//                 abmRegistros();
//                 break;
//             case 3:
//                 running = 0;
//                 break;
//             default:
//                 printf("La opcion ingresada es incorrecta.Por favor, intente de nuevo.\n\n");
//                 break;
//         }
//     }
//     menuFinalizar();

//     return 0;
// }
