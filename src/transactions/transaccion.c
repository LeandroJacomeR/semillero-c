#include "transaccion.h"

#include <string.h>

const char *TIPO_TRANSACCION_STR[]  = { "Anulada", "Compra" };
const char *FRANQUICIAS_STR[]  = { "American_Express", "Visa", "Mastercard", "Discover" };


Franquicia obtenerFranquiciaPorNombre(const char *nombre) {
    if (strcmp(nombre, "Visa") == 0) {
        return VISA;
    }
    if (strcmp(nombre, "Mastercard") == 0) {
        return MASTERCARD;
    }
    if (strcmp(nombre, "American_Express") == 0) {
        return AMERICAN_EXPRESS;
    }
    if (strcmp(nombre, "Discover") == 0) {
        return DISCOVER;
    }
    return -1; // Valor de error
}