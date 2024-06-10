// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "estructuras.h"
// #include "estudiantes.h"

// int main() {
    
//     char *ruta_archivo = "../materiasXcarreras/IngenieriaEnComputacion.csv";
//     char *materia_buscada = "Algebra I";

//     // Abrir el archivo CSV
//     FILE *archivo = fopen(ruta_archivo, "r");
//     if (archivo == NULL) {
//         fprintf(stderr, "Error al abrir el archivo: %s\n", strerror(errno));
//         return 1;
//     }
//     //Linea leida y nombre de la materia
//     char linea[100];
//     char materia[100];
//     int anio;
//     int encontrado = 0; // Encuentra o no

//     // Leo cada linda del archivo
//     while (fgets(linea, sizeof(linea), archivo) != NULL) {
//         obtenerMateria(linea, materia);

//         // Comparar la materia con la materia buscada
//         if (strcmp(materia, materia_buscada) == 0) {
//             anio = obtenerAnioMateria(linea);
//             printf("Materia buscada: %s, Año buscado: %d\n", materia, anio);
//             encontrado = 1; // Marcar que se encontró la materia
//             break; // Salir del bucle después de encontrar la materia
//         }
//     }

//     // if (!encontrado) {
//     //     printf("La materia %s no se encontró en el archivo.\n", materia_buscada);
//     // }

//     fclose(archivo);

//     return 0;
// }