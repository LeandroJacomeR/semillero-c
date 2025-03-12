# README - Sistema de Gestión de Transacciones

## Descripción

Este programa es un sistema de gestión de transacciones que permite realizar operaciones como compras, anulaciones, cierre de sesión, reimpresión, reporte de totales y finalizar la sesión.

## Funcionalidades

El sistema ofrece las siguientes opciones de transacción:

1. **Compra**: Realiza una compra con una tarjeta de crédito. Se ingresan detalles como el PAN, CVV, monto y fecha de vencimiento.
2. **Anulación**: Permite anular una transacción previamente realizada. Se requiere la referencia de la transacción y los 4 ultimos digitos de la tarjeta con su respectiv CVV.
3. **Cierre**: Finaliza el proceso de transacciones eliminando los datos simulando un cierre de transacciones.
4. **Reimpresión**: Permite reimprimir todas las transacciones en forma descendente.
5. **Reporte de Totales**: Muestra un reporte con el monto total de las compras y anulaciones realizadas.
6. **Finalizar**: Termina el programa y sale de la aplicación.

## Cómo Usar el Programa

1. **Ejecutar el Programa**:
    - Al iniciar el programa, se te presentará un menú con las opciones disponibles para realizar una transacción.

2. **Seleccionar una Opción**:
    - Deberás ingresar el número de la opción que deseas ejecutar. El sistema procesará la solicitud según la opción seleccionada.

3. **Detalles de las Opciones**:
    - **Opción 1: Compra**
        - Se te pedirá que ingreses el número de la tarjeta (PAN), el CVV, la fecha de vencimiento y el monto de la compra.
    - **Opción 2: Anulación**
        - Para anular una transacción, deberás ingresar la referencia de la transacción a anular y el PAN junto con el CVV correspondientes.
    - **Opción 3: Cierre**
        - Esta opción finalizará las transacciones eliminando los datos.
    - **Opción 4: Reimpresión**
        - Reimprime todas las transacciones de forma descendente.
    - **Opción 5: Reporte de Totales**
        - El sistema mostrará el total de las compras y anulaciones realizadas, sumando todos los montos de las transacciones exitosas.
    - **Opción 6: Finalizar**
        - Finaliza el programa y sale del sistema de manera segura.

## Requisitos

- **Sistema operativo**: Compatible con sistemas Unix/Linux y Windows.
- **Lenguaje**: C
- **Compilador**: GCC o cualquier compilador que soporte C estándar.

## Pasos para Compilar el Programa

1. **Descargar el Código Fuente**:
    - Asegúrate de tener los archivos fuente del programa en tu sistema. Los archivos estarán organizados en subdirectorios como `src/transactions/compra/compra.c`, `src/transactions/transaccion.c`, etc.

2. **Abrir una Terminal o Consola**:
    - En sistemas Unix/Linux, abre una terminal.
    - En Windows, abre la terminal de `CMD` o PowerShell, o usa un entorno como MinGW o Cygwin si estás en un entorno no nativo de C.

3. **Compilar el Código**:
    - Navega al directorio raíz del proyecto (`src` o donde se encuentren los archivos fuente).
    - Usa el siguiente comando para compilar el programa:
      ```bash
      gcc main.c trasactions/* trasactions/anulacion/* trasactions/compra/* trasactions/cierre/* trasactions/reporte_totales/* utils/* persistence/* -o transferencias.exe
      ```
      Este comando compilará todos los archivos fuente y generará un archivo ejecutable llamado `sistema_transacciones`.

4. **Ejecutar el Programa**:
    - Una vez que la compilación se haya completado exitosamente, puedes ejecutar el programa usando el siguiente comando:
        - En sistemas Unix/Linux:
          ```bash
          ./sistema_transacciones
          ```
        - En Windows:
          ```bash
          sistema_transacciones.exe
          ```

5. **Verificar el Funcionamiento**:
    - Al ejecutar el programa, se te presentará un menú interactivo con las opciones de transacciones.
    - Puedes seleccionar cualquier opción para probar el sistema.