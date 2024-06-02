#define COLOR_RED     "\033[31m"
#define COLOR_RESET   "\033[0m"


void Bienvenida();

void menuPrincipal();

void menuFinalizar();

void menuOpcionesABM();

void menuOpcionesConsultas();


void Bienvenida() {
    printf("______________________________________________\n");
    printf("Bienvenida/o al Sistema de Gestion de Estudiantes\n");
    menuPrincipal();
    printf("______________________________________________\n");
}

void menuFinalizar(){
    printf("Gracias por utilizar el Sistema de Gestion  de Estudiantes\n");
}

void menuPrincipal() {

    printf("Elija una de las siguientes opciones para continuar:\n\n");
    printf("1: Realizar una consulta \n");
    printf("2: Agregar, borrar o modificar registros del sistema\n");
    printf("3: Salir\n");
}

void menuOpcionesABM() {
    printf("Elija una de las siguientes opciones:\n\n");
    printf("1 Agregar materia\n");
    printf("2 Agregar estudiante\n");
    printf("3 Inscribir estudiante en materia\n");
    printf("4 Registrar nota\n");
    printf("5 Volver al menu principal\n");
    printf("______________________________________________\n");
}

void menuOpcionesConsultas() {
    printf("------- Consultas--------- \n");
    printf("Elija una de las siguientes opciones:\n\n");
    printf("1 Buscar estudiantes\n");
    printf("2 Obtener promedio de estudiante\n");
    printf("3 Obtener materias de estudiante\n");
    printf("4 Volver al menu principal\n");
    printf("______________________________________________\n");
}
