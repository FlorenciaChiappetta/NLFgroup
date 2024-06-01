
// Lista de estudiantes 
nodoListaEstudiantes *crearListaEstudiantes() {
    nodoListaEstudiantes *nodo = malloc(sizeof(nodoListaEstudiantes));
    nodo->estudiante = NULL;
    nodo->next = NULL;
    return nodo;
}

//    Crea un nodo de estudiante a partir de la referencia a un estudiante

nodoListaEstudiantes *crearNodoEstudiante (Estudiante* estudiante){
    nodoListaEstudiantes *nodo = malloc(sizeof(nodoListaEstudiantes));
    nodo->estudiante = estudiante;
    nodo->next = NULL;
    return nodo;
}



// Crear estudiante

Estudiante* crearEstudiante(char nombre[100], char apellido[100], int legajo, int edad[2], carrera carreraAAnotarse){
    Estudiante *estudianteNuevo = malloc(sizeof(Estudiante));
    strcpy(estudianteNuevo->nombre, nombre);
    strcpy(estudianteNuevo->apellido, apellido);
    estudianteNuevo->legajo = legajo;
    memcpy(estudianteNuevo->edad, edad, sizeof(int) * 2);
    estudianteNuevo->materias = malloc(sizeof(nodoListaMateria));
    estudianteNuevo->materias->materia = NULL;
    estudianteNuevo->materias->proximo = NULL;
    estudianteNuevo->carreraAnotada = carreraAAnotarse;

    return estudianteNuevo;
}