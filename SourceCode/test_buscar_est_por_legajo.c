#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.h"
#include "estudiantes.h"

// int main() {
//     // Crear una lista de estudiantes
//     nodoListaEstudiante* listaEstudiantes = crearListaEstudiantes();

//     // Crear y agregar algunos estudiantes a la lista
//     int edad[2]={24,0};
//     Estudiante* estudiante1 = crearEstudiante("Leandro", "Fajardo", 12345, edad, computacion);
//     darAltaEstudiante(&listaEstudiantes, estudiante1);

//     int edad2[2] = {22, 3};
//     Estudiante* estudiante2 = crearEstudiante("Ignacio", "Mattos", 67890, edad2, sonido);
//     darAltaEstudiante(&listaEstudiantes, estudiante2);

//     int edad3[2] = {21, 6};
//     Estudiante* estudiante3 = crearEstudiante("Florencia", "Chiapetta", 11223, edad3, ambiental);
//     darAltaEstudiante(&listaEstudiantes, estudiante3);

//     // Buscar un estudiante por legajo
//     int legajoBuscado = 12345;
//     buscarEstudiantePorLegajo(&listaEstudiantes, legajoBuscado);

//     // Liberar la memoria asignada
//     nodoListaEstudiante* temp;
//     while (listaEstudiantes != NULL) {
//         temp = listaEstudiantes;
//         listaEstudiantes = listaEstudiantes->proximo;
//         free(temp->estudiante->materias);
//         free(temp->estudiante);
//         free(temp);
//     }

//     return 0;
// }
