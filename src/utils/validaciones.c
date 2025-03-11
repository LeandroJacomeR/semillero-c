#include "validaciones.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

bool esFloatValido(const char* str) {
    int len = strlen(str);

    // Verificamos que la longitud sea válida (máximo 12 caracteres)
    if (len > 12) {
        printf("El numero de caracteres es invalido\n");
        return false;
    }

    // Caso: Cadena vacía
    if (*str == '\0') {
        printf("El parametro esta vacio\n");
        return false;
    }

    // Verificamos que solo haya un punto y que esté en la posición correcta
    int puntos = 0;
    int digitosPostPunto = 0;
    int digitosAntesPunto = 0;

    while (*str != '\0') {
        if (*str == '.') {
            puntos++;
            if (puntos > 1) {
                printf("El formato es incorrecto (solo un punto decimal permitido)\n");
                return false;
            }
        } else if (isdigit(*str)) {
            // Si ya hay un punto, contamos los dígitos después del punto
            if (puntos == 1) {
                digitosPostPunto++;
                if (digitosPostPunto > 2) {
                    printf("El formato es incorrecto (solo se permiten dos dígitos despues del punto)\n");
                    return false;
                }
            } else {
                // Si no hay punto, contamos los dígitos antes del punto
                digitosAntesPunto++;
            }
        } else {
            // Si encontramos un carácter no válido
            printf("El formato es incorrecto (solo se permiten digitos y un punto decimal)\n");
            return false;
        }
        str++;
    }

    // Verificamos que no haya más de 10 dígitos antes del punto
    if (digitosAntesPunto >= 10) {
        printf("El formato es incorrecto (solo se permiten hasta 10 digitos antes del punto)\n");
        return false;
    }

    // Verificamos que el número total no exceda los 12 caracteres, considerando los decimales
    if (digitosAntesPunto + digitosPostPunto + (puntos > 0 ? 1 : 0) > 12) {
        printf("El numero excede el maximo de 12 caracteres\n");
        return false;
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

static bool validarFranquicia(const char *pan, short len, Transaccion *transaccion) {
    if (strncmp(pan, "34", 2) == 0 || strncmp(pan, "37", 2) == 0) {
        if (len == 15) {
            transaccion->franquicia = AMERICAN_EXPRESS;
            return true;
        }
    } else if (strncmp(pan, "4", 1) == 0) {
        if (len == 16) {
            transaccion->franquicia = VISA;
            return true;
        }
    } else if (strncmp(pan, "5", 1) == 0) {
        if (len == 16) {
            transaccion->franquicia = MASTERCARD;
            return true;
        }
    } else if (strncmp(pan, "6011", 4) == 0) {
        if (len == 16) {
            transaccion->franquicia = DISCOVER;
            return true;
        }
    }

    printf("La tarjeta no pertenece a ninguna franquicia conocida.\n");
    return false;
}

static bool validarLuhn(const char *pan, short len) {
    short suma = 0;

    for (int i = len - 1; i >= 0; i--) {
        short numPan = pan[i] - '0';

        if ((len - i) % 2 == 0) {
            numPan *= 2;
            if (numPan > 9) {
                numPan -= 9;
            }
        }

        suma += numPan;
    }

    return (suma % 10 == 0);
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
    if (!esNumero(pan)) {
        printf("La cadena contiene caracteres no numéricos.\n");
        return false;
    }

    short len = strlen(pan);

    // Validar longitud del PAN
    if (len < 15 || len > 19) {
        printf("Formato incorrecto: Longitud del PAN debe estar entre 15 y 19 caracteres.\n");
        return false;
    }

    // Validar la franquicia de la tarjeta
    if (!validarFranquicia(pan, len, transaccion)) {
        return false;
    }

    // Validar con el algoritmo de Luhn
    if (!validarLuhn(pan, len)) {
        printf("El PAN no es valido\n");
        return false;
    }

    return true;
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

    if (transaccion->franquicia != AMERICAN_EXPRESS && len != 3) {
        printf("Formato de CVV no corresponde a la franquicia \n");
        return false;
    }

    bool validar_cadena = esNumero(cvv);

    return validar_cadena;
}