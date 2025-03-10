cmake_minimum_required(VERSION 3.30)
project(Semillero C)

set(CMAKE_C_STANDARD 99)

add_executable(Semillero src/main.c
        src/transactions/compra/compra.c
        src/transactions/compra/compra.h
        src/transactions/transaccion.c
        src/transactions/transaccion.h
        src/utils/validaciones.c
        src/utils/validaciones.h
        src/persistence/transaction_storage.c
        src/persistence/transaction_storage.h
        src/transactions/reporte_totales/reporte_totales.c
        src/transactions/reporte_totales/reporte_totales.h
        src/transactions/anulacion/anulacion.c
        src/transactions/anulacion/anulacion.h
        src/transactions/cierre/cierre.c
        src/transactions/cierre/cierre.h)
