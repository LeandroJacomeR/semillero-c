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

static bool esNumero(const char *cadena) {
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

bool esPANValido(const char *pan) {
    short len = strlen(pan);
    if (len != 16) {
        printf("Formato incorrecto \n");
        return false;
    }

    bool validar_cadena = esNumero(pan);

    return validar_cadena;
}

bool esCVVValido(const char *cvv) {
    short len = strlen(cvv);
    if (len != 3) {
        printf("Formato incorrecto \n");
        return false;
    }

    bool validar_cadena = esNumero(cvv);

    return validar_cadena;
}