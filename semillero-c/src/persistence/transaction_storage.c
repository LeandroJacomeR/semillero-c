#include "transaction_storage.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

const char* nombre_archivo = "transacciones.txt";
const short MAX_LINEA = 150; // (150 tamaño maximo de una linea)

static void imprimirTransaccion(Transaccion transaccion) {
    printf("Transaccion:\n");
    printf("Fecha: %s \n", transaccion.fecha);
    printf("Tipo: %s \n", tipoTransaccionStr[transaccion.tipo]);
    printf("Monto: %f \n", transaccion.monto);
    printf("Referencia: %d \n", transaccion.referencia);
    printf("Tipo: %s \n", transaccion.pan);
    printf("Tipo: %s \n", transaccion.cvv);
    printf("FechaExp: %s \n", transaccion.fechaExp);
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
        } else if (strcmp(tipo, "Anulacion") == 0) {
            totalAnulaciones++;
            totalMontoAnulacion += monto;
        }
    }

    fclose(archivo);

    printf("Transacciones totales: %d\n", contarLineas());
    printf("=== Resumen de Transacciones ===\n");
    printf("Cantidad de Compras: %d | Monto Total: %.2f\n", totalCompras, totalMontoCompra);
    printf("Cantidad de Anulaciones: %d | Monto Total: %.2f\n", totalAnulaciones, totalMontoAnulacion);

    fclose(archivo);

    printf(" Presione una tecla para continuar \n");
    getch();
    system("cls");
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