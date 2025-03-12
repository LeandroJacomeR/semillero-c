#ifndef TRANSACTION_STORAGE_H
#define TRANSACTION_STORAGE_H

#include <stdbool.h>
#include "../transactions/transaccion.h"

int obtenerUltimaReferencia();
int contarLineas();
bool guardarArchivo(Transaccion transacciones);
bool validarRefAnulada(const short ref);
void mostrarTransacciones();
void anulacion(const short ref, const char pan[5], const char cvv[4]);
bool eliminarArchivo();
void imprimirDesc();

#endif //TRANSACTION_STORAGE_H
