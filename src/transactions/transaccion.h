#ifndef TRANSACCION_H
#define TRANSACCION_H

extern const char *TIPO_TRANSACCION_STR[];
extern const char *FRANQUICIAS_STR[];

typedef enum {
    ANULACION,
    COMPRA
} TipoTransaccion;

typedef enum {
    AMERICAN_EXPRESS,
    VISA,
    MASTERCARD,
    DISCOVER
} Franquicia;

typedef struct {
    int referencia;
    char fecha[11];
    Franquicia franquicia;
    TipoTransaccion tipo;
    float monto;
    char pan[19];
    char cvv[5];
    char fechaExp[6];
} Transaccion;

Franquicia obtenerFranquiciaPorNombre(const char *nombre);

#endif //TRANSACCION_H
