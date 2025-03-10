#ifndef TRANSACCION_H
#define TRANSACCION_H

extern const char *tipoTransaccionStr[];

typedef enum {
    ANULACION,
    COMPRA
} TipoTransaccion;

typedef struct {
    int referencia;
    char fecha[11];
    TipoTransaccion tipo;
    float monto;
    char pan[17];
    char cvv[4];
    char fechaExp[5];
} Transaccion;

#endif //TRANSACCION_H
