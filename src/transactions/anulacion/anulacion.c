#include "anulacion.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


void actualizarAnulacion() {
    short ref;
    char pan[17], cvv[4];
    printf("Ingrese el numero de referencia: \n");
    scanf("%hd", &ref);
    do {
        printf("Ingrese los ultimos 4 digitos del PAN de la tarjeta:\n");
        scanf("%s", &pan);
        fflush(stdin);
    }while (strlen(pan) == 5 && esNumero(pan));

    do {
        printf("Ingrese el cvv de la tarjeta (3 caracteres) \n");
        scanf("%s", &cvv);
        fflush(stdin);
    }while (!esCVVValido(cvv));

    anulacion(ref, pan, cvv);

    printf(" Presione una tecla para continuar \n");
    getch();
    system("cls");
}
