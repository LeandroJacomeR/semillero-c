#include "cierre.h"

#include <stdio.h>

void cierreTransacciones() {
    mostrarTransacciones();
    printf("¿Desea continuar? Y/N");
    char c;
    scanf("%c", &c);
    fflush(stdin);
    if (c == 'Y' || c == 'y') {
        if (eliminarArchivo()) {
            printf("Datos eliminados correctamente");
        } else {
            printf("Error al eliminar los datos");
        }
    } else {
        printf("Regresando...");
    }
}
