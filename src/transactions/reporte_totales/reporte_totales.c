#include "reporte_totales.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "../../persistence/transaction_storage.h"

void reporteTotales() {
    mostrarTransacciones();

    printf("Presione una tecla para continuar \n");
    getch();
    system("cls");
}
