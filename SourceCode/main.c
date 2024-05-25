#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "menu/menu.h"


/* Lo dejo como un README

Hay que:

1- crear el tipo de dato estudiante y los metodos asociados...
el tipo de dato tiene que tener:
nombre
apellido
legajo/matricula
edad
cursada?
universidad?
etc

metodos:
anotarse a materias
rendir la materia
un getter de datos personales
un getter de notas por materia
eliminar estudiante..
uno para calcular el promedio 
y un aprobo materia o cursada algo asi.. 

2- crear el tipo de dato materia..

deberia tener codigo de materia y nombre minimo
cuatrimestre?

sus respectivos getters
un agregar materia
un eliminar materia
equivalencias hacemos? o correlativas no sé

3-crear un tipo de dato Curso/cursada 
ahi encerramos materias estudiantes etc.


4- qué guardamos en cada nodo???

*/

int scan();

void crear_materia();

void crear_estudiante();

void inscribir_estudiante();

void rendir_estudiante();

void consultar_materias();

void consultar_estudiantes();

void consultar_promedio_estudiante();

void listar_estudiantes_y_materias();

void materia_aprobada();

void realizar_consultas();

void abm_registros();

void estudiante_promedio_print();

void eliminar_materia();

void eliminar_estudiante();



int main() {

    setbuf(stdout, 0);

    menu_principal();
    int running = 1;

    while (running) {
        switch (scan()) {
            case 1:
                realizar_consultas();
                break;
            case 2:
                abm_registros();
                break;
            case 0:
                running = 0;
                break;
            default:
                printf("La opcion ingresada es incorrecta.Por favor, intente de nuevo.\n\n");
                break;
        }
        menu_opciones();
    }
    menu_finalizar();
    return 0;
}


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


void realizar_consultas() {
    int running = 1;
    while (running) {
        menu_print_query_opciones();
        switch (scan()) {
            case 0:
                running = 0;
                break;
            case 1:
               consultar_materias();
                break;
            case 2:
                consultar_estudiantes();
                break;
            case 3:
                consultar_promedio_estudiante();
                break;
            case 4:
                listar_estudiantes_y_materias();
                break;
            case 5:
                materia_aprobada();
                break;
            default:
                printf("La opcion ingresada es incorrecta.Por favor, intente de nuevo.\n\n");
                break;
        }
    }
}

void abm_registros() {
    int running = 1;
    while (running) {
        menu_print_abm_opciones();
        switch (scan()) {
            case 1:
                crear_materia();
                break;
            case 2:
                crear_estudiante();
                break;
            case 3:
                inscribir_estudiante();
                break;
            case 4:
                rendir_estudiante();
                break;
            case 5:
                eliminar_materia();
                break;
            case 6:
                eliminar_estudiante();
                break;
            case 0:
                running = 0;
                break;
            default:
                printf("La opcion ingresada es incorrecta.Por favor, intente de nuevo.\n\n");
        }
    }
}

void crear_materia() {
   
    }



void crear_estudiante() {
    
}

void inscribir_estudiante() {
    
}


void rendir_estudiante() {
    
}

void listar_estudiantes_y_materias() {

}

void consultar_materias() {

}


void consultar_estudiantes() {

}

void consultar_promedio_estudiante() {

}


void materia_aprobada() {
    
}

void eliminar_materia() {

}

void eliminar_estudiante() {

}
