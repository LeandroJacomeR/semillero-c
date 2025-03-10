#include "transaction_storage.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

const char *nombre_archivo = "transacciones.txt";
const char *old_nombre_archivo = "transacciones_temp.txt";
const short MAX_LINEA = 150; // (150 tamaño maximo de una linea)

static void imprimirTransaccion(Transaccion transaccion) {
    printf("Transaccion:\n");
    printf("Referencia: %d \n", transaccion.referencia);
    printf("Fecha: %s \n", transaccion.fecha);
    printf("Franquicia: %s \n", FRANQUICIAS_STR[transaccion.franquicia]);
    printf("Tipo: %s \n", TIPO_TRANSACCION_STR[transaccion.tipo]);
    printf("Monto: %f \n", transaccion.monto);
    printf("PAN: %s \n", transaccion.pan);
    printf("CVV: %s \n", transaccion.cvv);
    printf("FechaExp: %s \n", transaccion.fechaExp);
    printf("------------------------------------\n");
}

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

int obtenerUltimaReferencia() {
    FILE *archivo = fopen(nombre_archivo, "r");
    if (!archivo) return 0; // Si el archivo no existe, retornar 0

    char linea[MAX_LINEA];
    char ultimaLinea[MAX_LINEA]; // Para almacenar la última línea

    while (fgets(linea, sizeof(linea), archivo)) {
        strcpy(ultimaLinea, linea); // Guardar la última línea leída
    }

    fclose(archivo);

    // Si no se leyó ninguna línea, retornar 0
    if (strlen(ultimaLinea) == 0) return 0;

    // Extraer la referencia desde la última línea
    int ultimaReferencia;
    sscanf(ultimaLinea, "%d,", &ultimaReferencia); // Leer el primer valor (la referencia)

    return ultimaReferencia;
}

bool guardarArchivo(Transaccion transaccion) {
    FILE *archivo = fopen(nombre_archivo, "a"); // "a" para agregar sin sobrescribir
    if (!archivo) {
        printf("Error al abrir el archivo \n");
        return false;
    }

    // Escribir en formato legible
    fprintf(archivo, "%d | %s | %s | %s | %s | %s | %s | %.2f\n", transaccion.referencia, transaccion.fecha,
            FRANQUICIAS_STR[transaccion.franquicia], transaccion.pan, transaccion.cvv, transaccion.fechaExp,
            TIPO_TRANSACCION_STR[transaccion.tipo], transaccion.monto);

    imprimirTransaccion(transaccion);
    fclose(archivo);
    return true;
}

bool eliminarArchivo() {
    FILE *archivo = fopen(nombre_archivo, "r");
    if (!archivo) {
        printf("El archivo no existe.\n");
        return false;
    }
    fclose(archivo);
    return remove(nombre_archivo) == 0 ? true : false;
}

void mostrarTransacciones() {
    FILE *archivo = fopen("transacciones.txt", "r"); // Asegúrate de que el archivo esté bien referenciado
    if (!archivo) {
        printf("No hay transacciones registradas o el archivo no existe.\n");
        return;
    }

    int referencia, totalCompras = 0, totalAnulaciones = 0;
    char fecha[11], pan[20], cvv[4], fechaExp[6], tipo[10], franquicia[30]; // Tamaño para franquisia
    float monto, totalMontoCompra = 0, totalMontoAnulacion = 0;
    char linea[200]; // Buffer para leer una línea completa

    while (fgets(linea, sizeof(linea), archivo)) {
        // Usamos strtok para dividir la línea usando el delimitador " | "
        char *token = strtok(linea, " | ");

        referencia = atoi(token);
        token = strtok(NULL, " | ");
        strncpy(fecha, token, sizeof(fecha));

        token = strtok(NULL, " | ");
        strncpy(franquicia, token, sizeof(franquicia));

        token = strtok(NULL, " | ");
        strncpy(pan, token, sizeof(pan));

        token = strtok(NULL, " | ");
        strncpy(cvv, token, sizeof(cvv));

        token = strtok(NULL, " | ");
        strncpy(fechaExp, token, sizeof(fechaExp));

        token = strtok(NULL, " | ");
        strncpy(tipo, token, sizeof(tipo));

        token = strtok(NULL, " | ");
        monto = atof(token); // Convertimos a float

        printf("%d | %s | %s | %s | %s | %s | %s | %.2f\n", referencia, franquicia, fecha, pan, cvv, fechaExp, tipo,
               monto);

        // Eliminar espacios en tipo
        for (int i = 0; i < strlen(tipo); i++) {
            if (tipo[i] == ' ') {
                tipo[i] = '\0'; // Cortamos el string en el primer espacio
                break;
            }
        }

        // Procesamos la transacción según el tipo
        if (strcmp(tipo, "Compra") == 0) {
            totalCompras++;
            totalMontoCompra += monto;
        } else if (strcmp(tipo, "Anulada") == 0) {
            totalAnulaciones++;
            totalMontoAnulacion += monto;
        }
    }

    fclose(archivo); // Cerramos el archivo

    // Resumen de las transacciones
    printf("Transacciones totales: %d\n", contarLineas());
    printf("---- Resumen de Transacciones ----\n");
    printf("Cantidad de Compras: %d | Monto Total: %.2f\n", totalCompras, totalMontoCompra);
    printf("Cantidad de Anulaciones: %d | Monto Total: %.2f\n", totalAnulaciones, totalMontoAnulacion);
}

void imprimirDesc() {
    system("cls");
    FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo\n");
        return;
    }

    // Contar el número de líneas en el archivo
    int numLineas = contarLineas();
    char linea[MAX_LINEA];

    // Volver al inicio del archivo para leer las líneas
    rewind(archivo);

    // Crear un arreglo para almacenar las transacciones
    Transaccion *transacciones = (Transaccion *) malloc(numLineas * sizeof(Transaccion));
    if (transacciones == NULL) {
        printf("Error al asignar memoria\n");
        fclose(archivo);
        return;
    }

    // Leer las líneas y convertirlas en estructuras Transaccion
    int i = 0;
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        char franquicia[30];

        if (i >= numLineas) {
            printf("Error: demasiadas líneas en el archivo\n");
            break;
        }

        char *token = strtok(linea, " | ");
        if (token == NULL) break;

        transacciones[i].referencia = atoi(token);

        token = strtok(NULL, " | ");
        if (token != NULL) strncpy(transacciones[i].fecha, token, sizeof(transacciones[i].fecha) - 1);
        transacciones[i].fecha[sizeof(transacciones[i].fecha) - 1] = '\0';

        token = strtok(NULL, " | ");
        if (token != NULL) {
            strncpy(franquicia, token, sizeof(franquicia) - 1);
            franquicia[sizeof(franquicia) - 1] = '\0';
            transacciones[i].franquicia = obtenerFranquiciaPorNombre(franquicia);
        }

        token = strtok(NULL, " | ");
        if (token != NULL) strncpy(transacciones[i].pan, token, sizeof(transacciones[i].pan) - 1);
        transacciones[i].pan[sizeof(transacciones[i].pan) - 1] = '\0';

        token = strtok(NULL, " | ");
        if (token != NULL) strncpy(transacciones[i].cvv, token, sizeof(transacciones[i].cvv) - 1);
        transacciones[i].cvv[sizeof(transacciones[i].cvv) - 1] = '\0';

        token = strtok(NULL, " | ");
        if (token != NULL) strncpy(transacciones[i].fechaExp, token, sizeof(transacciones[i].fechaExp) - 1);
        transacciones[i].fechaExp[sizeof(transacciones[i].fechaExp) - 1] = '\0';

        token = strtok(NULL, " | ");
        if (token != NULL) {
            // Determinar el tipo de transacción
            if (strcmp(token, "Compra") == 0) {
                transacciones[i].tipo = COMPRA;
            } else if (strcmp(token, "Anulada") == 0) {
                transacciones[i].tipo = ANULACION;
            }
        }

        token = strtok(NULL, " | ");
        if (token != NULL) {
            transacciones[i].monto = atof(token);
        }

        i++;
    }

    fclose(archivo); // Cerramos el archivo

    // Imprimir las transacciones en orden inverso
    for (int j = numLineas - 1; j >= 0; j--) {
        imprimirTransaccion(transacciones[j]);
    }

    // Liberar la memoria del arreglo de transacciones
    free(transacciones);
}


void crearArchivoTemporal(Transaccion *transacciones, short numlineas) {
    FILE *archivo = fopen("transacciones_temp.txt", "w");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo\n");
        return;
    }

    for (int i = 0; i < numlineas; i++) {
        fprintf(archivo, "%d | %s | %s | %s | %s | %s | %s | %.2f\n",
            transacciones[i].referencia,
            transacciones[i].fecha,
            FRANQUICIAS_STR[transacciones[i].franquicia],
            transacciones[i].pan,
            transacciones[i].cvv,
            transacciones[i].fechaExp,
            TIPO_TRANSACCION_STR[transacciones[i].tipo],
            transacciones[i].monto);
    }

    fclose(archivo);
}

void anulacion(const short ref, const char pan[5], const char cvv[5]) {
    FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo\n");
        return;
    }

    // Contar el número de líneas en el archivo
    int numLineas = contarLineas();
    char linea[MAX_LINEA];

    // Crear un arreglo para almacenar las transacciones
    Transaccion *transacciones = (Transaccion *) malloc(numLineas * sizeof(Transaccion));
    if (transacciones == NULL) {
        printf("Error al asignar memoria\n");
        fclose(archivo);
        return;
    }

    // Leer las líneas y convertirlas en estructuras Transaccion
    int i = 0;
    bool transaccionEncontrada = false; // Flag para verificar si encontramos la transacción a anular
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        char franquicia[30];

        if (i >= numLineas) {
            printf("Error: demasiadas líneas en el archivo\n");
            break;
        }

        char *token = strtok(linea, " | ");
        if (token == NULL) break;

        transacciones[i].referencia = atoi(token);

        token = strtok(NULL, " | ");
        if (token != NULL) strncpy(transacciones[i].fecha, token, sizeof(transacciones[i].fecha) - 1);
        transacciones[i].fecha[sizeof(transacciones[i].fecha) - 1] = '\0';

        token = strtok(NULL, " | ");
        if (token != NULL) {
            strncpy(franquicia, token, sizeof(franquicia) - 1);
            franquicia[sizeof(franquicia) - 1] = '\0';
            transacciones[i].franquicia = obtenerFranquiciaPorNombre(franquicia);
        }

        token = strtok(NULL, " | ");
        if (token != NULL) strncpy(transacciones[i].pan, token, sizeof(transacciones[i].pan) - 1);
        transacciones[i].pan[sizeof(transacciones[i].pan) - 1] = '\0';

        token = strtok(NULL, " | ");
        if (token != NULL) strncpy(transacciones[i].cvv, token, sizeof(transacciones[i].cvv) - 1);
        transacciones[i].cvv[sizeof(transacciones[i].cvv) - 1] = '\0';

        token = strtok(NULL, " | ");
        if (token != NULL) strncpy(transacciones[i].fechaExp, token, sizeof(transacciones[i].fechaExp) - 1);
        transacciones[i].fechaExp[sizeof(transacciones[i].fechaExp) - 1] = '\0';

        token = strtok(NULL, " | ");
        if (token != NULL) {
            // Determinar el tipo de transacción
            if (strcmp(token, "Compra") == 0) {
                transacciones[i].tipo = COMPRA;
            } else if (strcmp(token, "Anulada") == 0) {
                transacciones[i].tipo = ANULACION;
            }
        }

        token = strtok(NULL, " | ");
        if (token != NULL) {
            transacciones[i].monto = atof(token);
        }

        if (ref == transacciones[i].referencia &&
            strncmp(pan, &transacciones[i].pan[strlen(transacciones[i].pan) - 4], 4) == 0 && // Los últimos 4 dígitos
            strcmp(cvv, transacciones[i].cvv) == 0 &&
            transacciones[i].tipo != ANULACION) {
            // Solo anular si no ha sido anulada aún

            printf("Anulando transaccion con referencia: %d\n", transacciones[i].referencia);
            transacciones[i].tipo = ANULACION; // Cambiar tipo a ANULACION
            transaccionEncontrada = true; // Marcar que encontramos la transacción
        }

        i++;
    }

    fclose(archivo); // Cerramos el archivo

    if (!transaccionEncontrada) {
        printf("No se encontro la transaccion a anular o ya ha sido anulada.\n");
        free(transacciones); // Liberar memoria antes de salir
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

    // Liberar la memoria del arreglo de transacciones
    free(transacciones);
}
