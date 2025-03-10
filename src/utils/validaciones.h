#ifndef VALIDACIONES_H
#define VALIDACIONES_H
#include <stdbool.h>

bool esFloatValido(const char *str);
bool esNumero(const char *cadena);
bool validarFecha(const char* fecha);
bool esPANValido(const char *pan);
bool esCVVValido(const char *cvv);

#endif //VALIDACIONES_H
