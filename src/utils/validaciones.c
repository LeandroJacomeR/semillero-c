#include "validaciones.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

bool esFloatValido(const char* str) {
    short puntos = 0;
    if (*str == '\0') {
        printf("El parametro esta vacio");
        return false;
    }

    while (*str != '\0') {
        if (*str == '.') {
            puntos++;
            if (puntos > 1) {
                printf("El formato es incorrecto \n");
                return false;
            }
        }else if (!isdigit(*str)) {
            printf("El formato es incorrecto \n");
            return false;
        }
        str++;
    }

    return true;
}

bool esNumero(const char *cadena) {
    int i = 0;
    while (cadena[i] != '\0') {
        if (!isdigit(cadena[i])) {
            printf("Formato incorrecto \n");
            return false;
        }
        i++;
    }
    return true;
}

bool validarFecha(const char* fecha) {
    if (strlen(fecha) != 5 || fecha[2] != '/') {
        printf("Formato de fecha de expiracion invalido\n");
        return false;
    }

    int mes, anio;
    // Verificar que el formato sea MM/YY y que solo tenga 2 dígitos en cada campo
    if (sscanf(fecha, "%2d/%2d", &mes, &anio) != 2) {
        printf("Formato incorrecto de fecha\n");
        return false;
    }

    if (mes < 1 || mes > 12) {
        printf("Formato de mes incorrecto \n");
        return false;
    }

    if (anio < 00 || anio > 99) {
        printf("Formato de anio incorrecto \n");
        return false;
    }

    // Obtener fecha actual
    time_t t = time(NULL);
    struct tm *fechaActual = localtime(&t);
    int anioActual = (fechaActual->tm_year + 1900) % 100; // Tomar los últimos dos dígitos del año
    int mesActual = fechaActual->tm_mon + 1;

    // Validar si la tarjeta está vencida
    if (anio < anioActual || (anio == anioActual && mes < mesActual)) {
        printf("Fecha vencida\n");
        return false;
    }

    return true;
}

bool esPANValido(Transaccion *transaccion, const char *pan) {
    short len = strlen(pan);
    short result = 0;

    // TODO: terminar el algoritmo de luhn
    for (int i = len; i >= 0; i--) {
        if (i % 2 != 0) {
            result = (short) pan[i] * 2;
            if (result > 10) {
                result = result + result;
            }
            result += (short) pan[i] * 2;
        }
    }

    printf("%hd \n", result);

    if (len < 13 || len > 19) {
        printf("Formato incorrecto \n");
        return false;
    }

    if (strncmp(pan, "34", 2) == 0 || strncmp(pan, "37", 2) == 0 && len == 15) {
        transaccion->franquicia = AMERICAN_EXPRESS;
    }
    if (strncmp(pan, "4", 1) == 0 && len == 16) {
        transaccion->franquicia = VISA;
    }
    if (strncmp(pan, "5", 2) == 0 && len == 16) {
        transaccion->franquicia = MASTERCARD;
    }
    if (strncmp(pan, "6011", 4) == 0 && len == 16) {
        transaccion->franquicia = DISCOVER;
    }

    bool validar_cadena = esNumero(pan);

    return validar_cadena;
}

bool esCVVValido(Transaccion *transaccion, const char *cvv) {
    short len = strlen(cvv);
    if (len < 3 || len > 4) {
        printf("Formato incorrecto \n");
        return false;
    }

    if (transaccion->franquicia == AMERICAN_EXPRESS && len != 4) {
        printf("Formato de CVV no corresponde a la franquicia \n");
        return false;
    }

    bool validar_cadena = esNumero(cvv);

    return validar_cadena;
}