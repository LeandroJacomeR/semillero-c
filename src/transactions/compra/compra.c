#include "compra.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>


void realizarCompra() {
    if (contarLineas() >= 20) {
        printf("El archivo esta lleno, por favor verifique nuevamente \n");
        return;
    }
    Transaccion transacion;

    // Obtener la fecha actual
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // Formatear la fecha como "DD-MM-YYYY"
    sprintf(transacion.fecha, "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    transacion.referencia = obtenerUltimaReferencia() + 1;
    char input[10];

    printf("Ingrese el monto total (USD):\n");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; // Eliminar el salto de línea

    fflush(stdin);
    if (!esFloatValido(input)) return;

    transacion.monto = strtof(input, NULL); // Convertir el input validado a float


    printf("Ingrese el PAN de la tarjeta (Min 15 - Max 19 caracteres):\n");
    scanf("%s", &transacion.pan);
    fflush(stdin);
    if (!esPANValido(&transacion, transacion.pan)) return;

    printf("Ingrese el cvv de la tarjeta (3 caracteres) \n");
    scanf("%s", &transacion.cvv);
    fflush(stdin);
    if (!esCVVValido(&transacion, transacion.cvv)) return;

    printf("Ingrese el fecha de expiracion (MM/YY):\n");
    scanf("%s", &transacion.fechaExp);
    fflush(stdin);
    if (!validarFecha(transacion.fechaExp)) return;

    transacion.tipo = COMPRA;

    if (!guardarArchivo(transacion)) {
        printf("Error en crear una compra\n");
        return;
    }

    printf("Compra exitosa \n Presione una tecla para continuar \n");
    getch();
    system("cls");
}
