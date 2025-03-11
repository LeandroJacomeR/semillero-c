#include "transaction_storage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

const char *nombre_archivo = "transacciones.dat";
const char *old_nombre_archivo = "transacciones_temp.dat";
const short MAX_LINEA = 150; // Tamaño máximo de una línea

void ocultarPan(char *pan) {
    int len = strlen(pan);
    for (int i = 4; i < len - 4; i++) {
        pan[i] = '*';
    }
}

void imprimirCabecera() {
    // Imprime la cabecera de la tabla con un ancho fijo para cada columna
    printf("%-12s | %-12s | %-18s | %-19s | %-4s | %-10s | %-9s | %-12s\n",
           "Referencia", "Fecha", "Franquicia", "PAN", "CVV", "Expiracion", "Tipo", "Monto");
    printf(
        "---------------------------------------------------------------------------------------------------------------\n");
}

void imprimirTransaccion(Transaccion transaccion) {
    char pan_oculto[20];
    strcpy(pan_oculto, transaccion.pan);
    ocultarPan(pan_oculto);
    printf("%-12d | %-12s | %-18s | %-19s | %-4s | %-10s | %-9s | %-12.2f\n",
           transaccion.referencia,
           transaccion.fecha,
           FRANQUICIAS_STR[transaccion.franquicia],
           pan_oculto,
           transaccion.cvv,
           transaccion.fechaExp,
           (transaccion.tipo == COMPRA) ? "Compra" : "Anulada",
           transaccion.monto);
}

// Función para leer una línea y convertirla a una transacción
static bool leerTransaccion(FILE *archivo, Transaccion *transaccion) {
    char linea[MAX_LINEA];
    if (!fgets(linea, sizeof(linea), archivo)) return false;

    char *token = strtok(linea, " | ");
    transaccion->referencia = atoi(token);

    token = strtok(NULL, " | ");
    strncpy(transaccion->fecha, token, sizeof(transaccion->fecha) - 1);
    transaccion->fecha[sizeof(transaccion->fecha) - 1] = '\0';

    token = strtok(NULL, " | ");
    char franquicia[30];
    strncpy(franquicia, token, sizeof(franquicia) - 1);
    franquicia[sizeof(franquicia) - 1] = '\0';
    transaccion->franquicia = obtenerFranquiciaPorNombre(franquicia);

    token = strtok(NULL, " | ");
    strncpy(transaccion->pan, token, sizeof(transaccion->pan) - 1);
    transaccion->pan[sizeof(transaccion->pan) - 1] = '\0';

    token = strtok(NULL, " | ");
    strncpy(transaccion->cvv, token, sizeof(transaccion->cvv) - 1);
    transaccion->cvv[sizeof(transaccion->cvv) - 1] = '\0';

    token = strtok(NULL, " | ");
    strncpy(transaccion->fechaExp, token, sizeof(transaccion->fechaExp) - 1);
    transaccion->fechaExp[sizeof(transaccion->fechaExp) - 1] = '\0';

    token = strtok(NULL, " | ");
    if (strcmp(token, "Compra") == 0) {
        transaccion->tipo = COMPRA;
    } else if (strcmp(token, "Anulada") == 0) {
        transaccion->tipo = ANULACION;
    }

    token = strtok(NULL, " | ");
    transaccion->monto = atof(token);

    return true;
}

// Función para contar las líneas en un archivo
int contarLineas() {
    FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL) return 0;

    int contador = 0;
    char linea[MAX_LINEA];
    while (fgets(linea, sizeof(linea), archivo)) {
        contador++;
    }
    fclose(archivo);
    return contador;
}

// Función para obtener la última referencia del archivo
int obtenerUltimaReferencia() {
    FILE *archivo = fopen(nombre_archivo, "r");
    if (!archivo) return 0;

    char ultimaLinea[MAX_LINEA];
    while (fgets(ultimaLinea, sizeof(ultimaLinea), archivo)) {
    }

    fclose(archivo);

    if (strlen(ultimaLinea) == 0) return 0;

    int ultimaReferencia;
    sscanf(ultimaLinea, "%d,", &ultimaReferencia);
    return ultimaReferencia;
}

// Función para guardar una transacción en el archivo
bool guardarArchivo(Transaccion transaccion) {
    FILE *archivo = fopen(nombre_archivo, "a");
    if (!archivo) {
        printf("Error al abrir el archivo\n");
        return false;
    }

    fprintf(archivo, "%d | %s | %s | %s | %s | %s | %s | %.2f\n", transaccion.referencia, transaccion.fecha,
            FRANQUICIAS_STR[transaccion.franquicia], transaccion.pan, transaccion.cvv, transaccion.fechaExp,
            TIPO_TRANSACCION_STR[transaccion.tipo], transaccion.monto);

    imprimirTransaccion(transaccion);
    fclose(archivo);
    return true;
}

// Función para eliminar el archivo original
bool eliminarArchivo() {
    FILE *archivo = fopen(nombre_archivo, "r");
    if (!archivo) {
        printf("El archivo no existe.\n");
        return false;
    }
    fclose(archivo);
    return remove(nombre_archivo) == 0;
}

// Función para mostrar las transacciones
void mostrarTransacciones() {
    FILE *archivo = fopen(nombre_archivo, "r");
    if (!archivo) {
        printf("No hay transacciones registradas o el archivo no existe.\n");
        return;
    }

    Transaccion transaccion;
    int totalCompras = 0, totalAnulaciones = 0;
    float totalMontoCompra = 0, totalMontoAnulacion = 0;
    imprimirCabecera();

    while (leerTransaccion(archivo, &transaccion)) {
        // printf("%d | %s | %s | %s | %s | %s | %s | %.2f\n", transaccion.referencia, FRANQUICIAS_STR[transaccion.franquicia],
        //        transaccion.fecha, transaccion.pan, transaccion.cvv, transaccion.fechaExp, TIPO_TRANSACCION_STR[transaccion.tipo], transaccion.monto);

        imprimirTransaccion(transaccion);

        if (transaccion.tipo == COMPRA) {
            totalCompras++;
            totalMontoCompra += transaccion.monto;
        } else if (transaccion.tipo == ANULACION) {
            totalAnulaciones++;
            totalMontoAnulacion += transaccion.monto;
        }
    }

    fclose(archivo);

    printf("Transacciones totales: %d\n", contarLineas());
    printf("---- Resumen de Transacciones ----\n");
    printf("Cantidad de Compras: %d | Monto Total: %.2f\n", totalCompras, totalMontoCompra);
    printf("Cantidad de Anulaciones: %d | Monto Total: %.2f\n", totalAnulaciones, totalMontoAnulacion);
}

// Función para imprimir transacciones de forma inversa
void imprimirDesc() {
    system("cls");
    FILE *archivo = fopen(nombre_archivo, "r");
    if (!archivo) {
        printf("No hay transacciones registradas o el archivo no existe.\n");
        printf("Presione cualquier tecla para salir \n");
        getch();
        system("cls");
        return;
    }

    int numLineas = contarLineas();
    if (numLineas == 0) {
        printf("No se encuentran datos\n");
        return;
    }
    Transaccion *transacciones = (Transaccion *) malloc(numLineas * sizeof(Transaccion));
    if (!transacciones) {
        printf("Error al asignar memoria\n");
        fclose(archivo);
        return;
    }

    int i = 0;
    while (leerTransaccion(archivo, &transacciones[i])) {
        i++;
    }

    fclose(archivo);
    imprimirCabecera();
    int contador = numLineas - 1;

    if (contador == 0) {
        imprimirTransaccion(transacciones[contador]);

        printf("\n \n \n");
        printf("Presione cualquier tecla para salir \n");

        getch();
        free(transacciones);
        system("cls");
        return;
    }

    imprimirTransaccion(transacciones[contador]);

    printf("\n \n            d -->\n");
    printf("Presione cualquier tecla para salir \n");

    char next;
    while (1) {
        next = getch();
        next = tolower(next);
        fflush(stdin);
        system("cls");
        imprimirCabecera();

        if (next == 'd' && contador > 0) {
            contador--;  // Mover hacia atrás
        }
        else if (next == 'a' && contador < numLineas - 1) {
            contador++;  // Mover hacia adelante
        }
        else if (next != 'a' && next != 'd') {
            break;
        }

        imprimirTransaccion(transacciones[contador]);

        if (contador == 0) {
            printf("\n \n<-- a           \n");
            printf("Presione cualquier tecla para salir \n");
        } else if (contador == numLineas - 1) {
            printf("\n \n           d --> \n");
            printf("Presione cualquier tecla para salir \n");
        } else {
            printf("\n \n<-- a       d -->\n");
            printf("Presione cualquier tecla para salir \n");
        }
    }

    free(transacciones);
    system("cls");
}

// Función para crear un archivo temporal con las transacciones
void crearArchivoTemporal(Transaccion *transacciones, short numLineas) {
    FILE *archivo = fopen(old_nombre_archivo, "w");
    if (!archivo) {
        printf("No se pudo abrir el archivo\n");
        return;
    }

    for (int i = 0; i < numLineas; i++) {
        fprintf(archivo, "%d | %s | %s | %s | %s | %s | %s | %.2f\n", transacciones[i].referencia,
                transacciones[i].fecha, FRANQUICIAS_STR[transacciones[i].franquicia], transacciones[i].pan,
                transacciones[i].cvv, transacciones[i].fechaExp, TIPO_TRANSACCION_STR[transacciones[i].tipo],
                transacciones[i].monto);
    }

    fclose(archivo);
}

// Función para validar si una referencia ya ha sido anulada
bool validarRefAnulada(const short ref) {
    FILE *archivo = fopen(nombre_archivo, "r");
    if (!archivo) {
        printf("No se pudo abrir el archivo\n");
        return false;
    }

    int numLineas = contarLineas();
    Transaccion *transacciones = (Transaccion *) malloc(numLineas * sizeof(Transaccion));
    if (!transacciones) {
        printf("Error al asignar memoria\n");
        fclose(archivo);
        return false;
    }

    int i = 0;
    bool transaccionEncontrada = false;
    while (leerTransaccion(archivo, &transacciones[i])) {
        if (ref == transacciones[i].referencia && transacciones[i].tipo == ANULACION) {
            transaccionEncontrada = true;
            break;
        }
        i++;
    }

    fclose(archivo);
    free(transacciones);
    if (transaccionEncontrada)
        printf("La transaccion ya se encuentra anulada \n");
    return transaccionEncontrada;
}

// Función para anular una transacción
void anulacion(const short ref, const char pan[5], const char cvv[5]) {
    FILE *archivo = fopen(nombre_archivo, "r");
    if (!archivo) {
        printf("No se pudo abrir el archivo\n");
        return;
    }

    int numLineas = contarLineas();
    Transaccion *transacciones = (Transaccion *) malloc(numLineas * sizeof(Transaccion));
    if (!transacciones) {
        printf("Error al asignar memoria\n");
        fclose(archivo);
        return;
    }

    int i = 0;
    bool transaccionEncontrada = false;
    while (leerTransaccion(archivo, &transacciones[i])) {
        if (ref == transacciones[i].referencia &&
            strncmp(pan, &transacciones[i].pan[strlen(transacciones[i].pan) - 4], 4) == 0 &&
            strcmp(cvv, transacciones[i].cvv) == 0 &&
            transacciones[i].tipo != ANULACION) {
            transacciones[i].tipo = ANULACION;
            transaccionEncontrada = true;
            break;
        }
        i++;
    }

    fclose(archivo);

    if (!transaccionEncontrada) {
        printf("No se encontro la transaccion a anular o ya ha sido anulada.\n");
        free(transacciones);
        return;
    }

    crearArchivoTemporal(transacciones, numLineas);

    if (eliminarArchivo()) {
        rename(old_nombre_archivo, nombre_archivo);
        printf("Transaccion anulada correctamente.\n");
    } else {
        for (int j = 0; j < numLineas; j++) {
            if (!guardarArchivo(transacciones[j])) {
                printf("Error al guardar la transacción %d\n", transacciones[j].referencia);
            }
        }
        printf("Error al eliminar el archivo original.\n");
    }

    free(transacciones);
}
