#include <stdio.h>
#include "menu.h"

//habria que agregar los "extras", esto es lo minimo que se pide

void menu_principal() {
    printf("______________________________________________\n");
    printf("Bienvenida/o al Sistema de Gestion de Estudiantes\n");
    menu_print_main_options();
    printf("______________________________________________\n");
}

void menu_opciones() {
    printf("---------------- Menu principal ----------------\n");
    menu_print_main_options();
}

void menu_finalizar(){
    printf("Gracias por utilizar el Sistema de Gestion  de Estudiantes\n");
}

void menu_print_opciones_menu_principal() {

    printf("Elija una de las siguientes opciones para continuar:\n\n");
    printf("1: Realizar una consulta \n");
    printf("2: Agregar, borrar o modificar registros del sistema\n");
    printf("3: Salir\n");
}

void menu_print_abm_optiones() {
    printf("Elija una de las siguientes opciones:\n\n");
    printf("1 Agregar materia\n");
    printf("2 Agregar estudiante\n");
    printf("3 Modificar estudiante\n");    
    printf("4 Inscribir estudiante en materia\n");
    printf("5 Registrar nota\n");
    printf("6 Eliminar materia\n");
    printf("7 Eliminar estudiante\n");
    printf("8 Volver al menu principal\n");
    printf("______________________________________________\n");
}

void menu_print_query_optiones() {
    printf("------- Consultas--------- \n");
    printf("Elija una de las siguientes opciones:\n\n");
    printf("1 Buscar materias\n");
    printf("2 Buscar estudiantes\n");
    printf("3 Obtener promedio de estudiante\n");
    printf("4 Listar registro\n");
    printf("5 Obtener estado de aprobación del estudiante\n");
    printf("6 Volver al menu principal\n");
    printf("______________________________________________\n");
}
