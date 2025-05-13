#include <stdio.h>
#include <string.h>
#include "funcion.h"

void lens(char str[]) {
    int len = strlen(str) - 1;
    if (len >= 0 && str[len] == '\n') {
        str[len] = '\0';
    }
}

int leeropc() {
    int opc, val;
    do {
        fflush(stdin);
        val = scanf("%d", &opc);
        if (val != 1) {
            printf("Dato invalido. Por favor, ingrese un numero entero.\n");
        }
    } while (val != 1);
    return opc;
}

int validarEnteroPositivo() {
    int numero, val;
    do {
        val = scanf("%d", &numero);
        if (val != 1 || numero <= 0) {
            printf("Dato invalido. Ingrese un numero entero positivo.\n");
            fflush(stdin);
        }
    } while (val != 1 || numero <= 0);
    
    return numero;
}

int validarCantidad() {
    int cantidad, val;
    do {
        val = scanf("%d", &cantidad);
        if (val != 1 || cantidad <= 0) {
            printf("Dato invalido. Ingrese una cantidad valida.\n");
            fflush(stdin);
        }
    } while (val != 1 || cantidad <= 0);

    return cantidad;
}

float validarFloatPositivo() {
    float numero;
    int val;
    do {
        val = scanf("%f", &numero);
        if (val != 1 || numero <= 0) {
            printf("Dato invalido. Ingrese un numero decimal positivo.\n");
            fflush(stdin);
        }
    } while (val != 1 || numero <= 0);
    
    return numero;
}
