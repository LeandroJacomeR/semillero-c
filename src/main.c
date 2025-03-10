#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include "transactions/anulacion/anulacion.h"
#include "transactions/compra/compra.h"
#include "transactions/cierre/cierre.h"
#include "transactions/reporte_totales/reporte_totales.h"

void limpiarconsola() {
    printf(" Presione una tecla para continuar \n");
    getch();
    system("cls");
}

int main(void) {
    short ejecucion = 1;
    while (ejecucion) {
        printf(
            "Bienvenido! \n Que transaccion desea realizar? \n 1. Compra \n 2. Anulacion \n 3. Cierre \n 4. Reimpresion \n 5. Reporte de totales \n 6. Finalizar \n");
        short opcion;
        scanf("%hd", &opcion);
        fflush(stdin);
        switch (opcion) {
            case 1:
                realizarCompra();
                fflush(stdin);
                limpiarconsola();
                break;
            case 2:
                actualizarAnulacion();
                fflush(stdin);
                limpiarconsola();
                break;
            case 3:
                cierreTransacciones();
                fflush(stdin);
                limpiarconsola();
                break;
            case 4:
                imprimirDesc();
                fflush(stdin);
                limpiarconsola();
                break;
            case 5:
                reporteTotales();
                fflush(stdin);
                limpiarconsola();
                break;
            case 6:
                printf("Finalizando programa \n");
                ejecucion = 0;
                break;
            default:
                printf("Opcion no valida! \n Presione una tecla para continuar \n");
                getch();
                system("cls");
        }
    }
    return 0;
}
