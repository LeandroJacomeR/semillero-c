#include "reporte_totales.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void reporteTotales() {
    FILE *archivo = fopen("transacciones.dat", "rb");
    if (!archivo) {
        perror("Error al abrir el archivo");
        return;
    }

    Transaccion t;
    printf("Listado de Transacciones:\n");

    // Leer y mostrar todas las transacciones
    while (fread(&t, sizeof(Transaccion), 1, archivo) == 1) {
        printf("Referencia: %d, monto: %f, tipo: %s \n", t.referencia, t.monto, tipoTransaccionStr[t.tipo]);
    }

    fclose(archivo);

    printf("Presione una tecla para continuar \n");
    getch();
    system("cls");
}
