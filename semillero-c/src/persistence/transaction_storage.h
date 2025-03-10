#ifndef TRANSACTION_STORAGE_H
#define TRANSACTION_STORAGE_H

#include <stdbool.h>
#include "../transactions/transaccion.h"

int obtenerUltimaReferencia();
int contarLineas();
bool guardarArchivo(Transaccion transacciones);
void mostrarTransacciones();
//void anulacion(const short ref, const char pan[4], const char cvv[3]);
bool eliminarArchivo();

#endif //TRANSACTION_STORAGE_H
