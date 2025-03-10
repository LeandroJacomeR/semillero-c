#ifndef VALIDACIONES_H
#define VALIDACIONES_H
#include <stdbool.h>

#include "../transactions/transaccion.h"

bool esFloatValido(const char *str);
bool esNumero(const char *cadena);
bool validarFecha(const char* fecha);
bool esPANValido(Transaccion *transaccion, const char *pan);
bool esCVVValido(Transaccion *transaccion, const char *cvv);

#endif //VALIDACIONES_H
