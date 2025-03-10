#include "transaction_storage.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

const char* nombre_archivo = "transacciones.txt";
const short MAX_LINEA = 150; // (150 tamaño maximo de una linea)

static void imprimirTransaccion(Transaccion transaccion) {
    printf("Transaccion:\n");
    printf("Referencia: %d \n", transaccion.referencia);
    printf("Fecha: %s \n", transaccion.fecha);
    printf("Tipo: %s \n", tipoTransaccionStr[transaccion.tipo]);
    printf("Monto: %f \n", transaccion.monto);
    printf("Tipo: %s \n", transaccion.pan);
    printf("Tipo: %s \n", transaccion.cvv);
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
    if (!archivo) return 0;  // Si el archivo no existe, retornar 0

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
    fprintf(archivo, "%d | %s | %s | %s | %s | %s | %.2f\n", transaccion.referencia, transaccion.fecha, transaccion.pan, transaccion.cvv, transaccion.fechaExp ,tipoTransaccionStr[transaccion.tipo], transaccion.monto);

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
    FILE *archivo = fopen(nombre_archivo, "r");
    if (!archivo) {
        printf("No hay transacciones registradas o el archivo no existe.\n");
        return;
    }

    int referencia, totalCompras = 0, totalAnulaciones = 0;
    char fecha[11], pan[17], cvv[4], fechaExp[6], tipo[10];
    float monto, totalMontoCompra = 0, totalMontoAnulacion = 0;

    while (fscanf(archivo, "%d | %10[^|] | %16[^|] | %3[^|] | %5[^|] | %9[^|] | %f\n", &referencia, fecha, pan, cvv, fechaExp, tipo, &monto) == 7) {
        printf("%-4d | %-10s | %-16s | %-3s | %-5s | %-8s | %.2f\n", referencia, fecha, pan, cvv, fechaExp, tipo, monto);

        // Eliminar espacios en tipo
        for (int i = 0; i < strlen(tipo); i++) {
            if (tipo[i] == ' ') {
                tipo[i] = '\0';  // Cortar el string en el primer espacio
                break;
            }
        }

        if (strcmp(tipo, "Compra") == 0) {
            totalCompras++;
            totalMontoCompra += monto;
        } else if (strcmp(tipo, "Anulada") == 0) {
            totalAnulaciones++;
            totalMontoAnulacion += monto;
        }
    }

    fclose(archivo);

    printf("Transacciones totales: %d\n", contarLineas());
    printf("---- Resumen de Transacciones ----\n");
    printf("Cantidad de Compras: %d | Monto Total: %.2f\n", totalCompras, totalMontoCompra);
    printf("Cantidad de Anulaciones: %d | Monto Total: %.2f\n", totalAnulaciones, totalMontoAnulacion);

    fclose(archivo);
}

void imprimirDesc() {
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
    Transaccion* transacciones = (Transaccion*)malloc(numLineas * sizeof(Transaccion));
    if (transacciones == NULL) {
        printf("Error al asignar memoria\n");
        fclose(archivo);
        return;
    }

    // Leer las líneas y convertirlas en estructuras Transaccion
    int i = 0;
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        sscanf(linea, "%d | %10[^|] | %16[^|] | %3[^|] | %5[^|] | %9[^|] | %f",
            &transacciones[i].referencia, transacciones[i].fecha, transacciones[i].pan,
            transacciones[i].cvv, transacciones[i].fechaExp, linea, &transacciones[i].monto);

        // Determinar el tipo de transacción (Compra o Anulación)
        if (strstr(linea, "Compra")) {
            transacciones[i].tipo = COMPRA;
        } else if (strstr(linea, "Anulada")) {
            transacciones[i].tipo = ANULACION;
        }
        i++;
    }

    fclose(archivo);  // Cerramos el archivo

    // Imprimir las transacciones en orden inverso
    for (int j = numLineas - 1; j >= 0; j--) {
        imprimirTransaccion(transacciones[j]);
    }

    // Liberar la memoria del arreglo de transacciones
    free(transacciones);

    printf(" Presione una tecla para continuar \n");
    getch();
    system("cls");
}

void crearArchivoTemporal(Transaccion* transacciones, short numlineas) {
    FILE *archivo = fopen("transacciones_temp.txt", "w");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo\n");
        return;
    }

    for (int i = 0; i < numlineas; i++) {
        fprintf(archivo, "%d | %s | %s | %s | %s | %s | %.2f\n", transacciones[i].referencia, transacciones[i].fecha, transacciones[i].pan, transacciones[i].cvv, transacciones[i].fechaExp ,tipoTransaccionStr[transacciones[i].tipo], transacciones[i].monto);
    }

    fclose(archivo);
}

void anulacion(const short ref, const char pan[5], const char cvv[4]) {
    FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo\n");
        return;
    }

    // Contar el número de líneas en el archivo
    int numLineas = contarLineas();
    char linea[MAX_LINEA];

    // Crear un arreglo para almacenar las transacciones
    Transaccion* transacciones = (Transaccion*)malloc(numLineas * sizeof(Transaccion));
    if (transacciones == NULL) {
        printf("Error al asignar memoria\n");
        fclose(archivo);
        return;
    }

    // Leer las líneas y convertirlas en estructuras Transaccion
    int i = 0;
    bool transaccionEncontrada = false;  // Flag para verificar si encontramos la transacción a anular
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        // Leer los datos de la línea
        sscanf(linea, "%d | %10[^|] | %16[^|] | %3[^|] | %5[^|] | %9[^|] | %f",
               &transacciones[i].referencia, transacciones[i].fecha, transacciones[i].pan,
               transacciones[i].cvv, transacciones[i].fechaExp, linea, &transacciones[i].monto);

        // Determinar el tipo de transacción (Compra o Anulación)
        if (strstr(linea, "Compra")) {
            transacciones[i].tipo = COMPRA;  // Asignar tipo COMPRA
        } else if (strstr(linea, "Anulada")) {
            transacciones[i].tipo = ANULACION;  // Asignar tipo ANULACION
        }

        // Intentar encontrar la transacción a anular
        if (ref == transacciones[i].referencia &&
            strcmp(pan, &transacciones[i].pan[12]) == 0 &&  // Comparar los últimos 4 dígitos del PAN
            strcmp(cvv, transacciones[i].cvv) == 0 &&
            transacciones[i].tipo != ANULACION) {  // Solo anular si no ha sido anulada aún

            transacciones[i].tipo = ANULACION;  // Cambiar tipo a ANULACION
            transaccionEncontrada = true;  // Marcar que encontramos la transacción
        }
        i++;
    }

    fclose(archivo);  // Cerramos el archivo

    if (!transaccionEncontrada) {
        printf("No se encontro la transaccion a anular o ya ha sido anulada.\n");
        free(transacciones);  // Liberar memoria antes de salir
        return;
    }
    crearArchivoTemporal(transacciones, numLineas);

    // Eliminar el archivo antiguo y guardar las transacciones modificadas
    if (eliminarArchivo()) {
        for (int j = 0; j < numLineas; j++) {
            if (!guardarArchivo(transacciones[j])) {
                printf("Error al guardar la transacción %d\n", transacciones[j].referencia);
            }
        }
        printf("Transaccion anulada correctamente.\n");
    } else {
        printf("Error al eliminar el archivo original.\n");
    }

    // Liberar la memoria del arreglo de transacciones
    free(transacciones);
}