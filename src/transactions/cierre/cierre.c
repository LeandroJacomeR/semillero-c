#include "cierre.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void cierreTransacciones() {
    system("cls");
    mostrarTransacciones();
    printf("Desea eliminar todos los datos? Y/N \n");
    char c;
    scanf("%c", &c);
    fflush(stdin);
    if (c == 'Y' || c == 'y') {
        if (eliminarArchivo()) {
            printf("Datos eliminados correctamente \n");
        } else {
            printf("Error al eliminar los datos \n");
        }
    } else {
        system("cls");
        printf("Regresando... \n");
    }
}
