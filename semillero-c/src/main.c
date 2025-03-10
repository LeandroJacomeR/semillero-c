#include <stdio.h>
#include "transactions/compra/compra.h"
#include "transactions/cierre/cierre.h"
#include "transactions/reporte_totales/reporte_totales.h"

int main(void) {
    short ejecucion = 1;
    while (ejecucion) {
        printf("¡Bienvenido! \n ¿Que transaccion desea realizar? \n 1. Compra \n 2. Anulacion \n 3. Cierre \n 4. Reimpresion \n 5. Reporte de totales \n 6. Finalizar \n");
        short opcion;
        scanf("%hd", &opcion);
        fflush(stdin);
        switch (opcion) {
            case 1:
                realizarCompra();
                fflush(stdin);
                break;
            case 3:
                cierreTransacciones();
                fflush(stdin);
                break;
            case 5:
                mostrarTransacciones();
                fflush(stdin);
                break;
            case 6:
                printf("Finalizando programa \n");
                ejecucion = 0;
                break;
            default:
                printf("Opcion no valida! \n");
        }
    }
    return 0;
}
