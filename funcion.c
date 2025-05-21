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

float validarDecimalPositivo() {
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

void menufuncion() {
    printf("--Menu--\n");
    printf("1. Gestionar recursos disponibles\n");
    printf("2. Agregar producto\n");
    printf("3. Editar producto\n");
    printf("4. Eliminar producto\n");
    printf("5. Gestionar materiales de un producto\n");
    printf("6. Ingreso del pedido y calcular produccion\n");
    printf("7. Mostrar productos y materiales\n");
    printf("8. Salir\n");
    printf("Seleccione una opcion: ");
}

void menufuncion2() {
    printf("--Menu--\n");
    printf("1. Agregar material\n");
    printf("2. Editar material\n");
    printf("3. Eliminar material\n");
    printf("4. Ver materiales\n");
    printf("5. Volver\n");
    printf("Seleccione una opcion: ");
}
