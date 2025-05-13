#include <stdio.h>
#include <string.h>

int main() {
    char nombres[5][50];
    int demandas[5];
    int tiemposProduccion[5];
    int recursosRequeridos[5];
    int cantidadProductos = 0;
    int tiempoDisponible = 0, recursosDisponibles = 0;
    int opcion;

    do {
        printf("\n--- Menu ---\n");
        printf("1. Ingresar tiempo de produccion disponible\n");
        printf("2. Ingresar cantidad de recursos disponibles\n");
        printf("3. Agregar producto\n");
        printf("4. Editar producto\n");
        printf("5. Eliminar producto\n");
        printf("6. Calcular produccion\n");
        printf("7. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese el tiempo de produccion disponible: ");
                scanf("%d", &tiempoDisponible);
                break;

            case 2:
                printf("Ingrese la cantidad de recursos disponibles: ");
                scanf("%d", &recursosDisponibles);
                break;

            case 3:
                if (cantidadProductos >= 5) {
                    printf("No se pueden agregar mas productos.\n");
                    break;
                }

                printf("Ingrese el nombre del producto: ");
                scanf("%s", nombres[cantidadProductos]);
                printf("Ingrese la cantidad demandada: ");
                scanf("%d", &demandas[cantidadProductos]);
                printf("Ingrese el tiempo de fabricacion por unidad: ");
                scanf("%d", &tiemposProduccion[cantidadProductos]);
                printf("Ingrese los recursos requeridos por unidad: ");
                scanf("%d", &recursosRequeridos[cantidadProductos]);

                cantidadProductos++;
                printf("Producto agregado exitosamente.\n");
                break;

            case 4: {
                char nombre[50];
                int encontrado = 0;

                printf("Ingrese el nombre del producto a editar: ");
                scanf("%s", nombre);

                for (int i = 0; i < cantidadProductos; i++) {
                    if (strcmp(nombres[i], nombre) == 0) {
                        printf("Producto encontrado. Ingrese los nuevos datos:\n");
                        printf("Nuevo nombre: ");
                        scanf("%s", nombres[i]);
                        printf("Nueva cantidad demandada: ");
                        scanf("%d", &demandas[i]);
                        printf("Nuevo tiempo de fabricacion por unidad: ");
                        scanf("%d", &tiemposProduccion[i]);
                        printf("Nuevos recursos requeridos por unidad: ");
                        scanf("%d", &recursosRequeridos[i]);
                        encontrado = 1;
                        printf("Producto editado exitosamente.\n");
                        break;
                    }
                }

                if (!encontrado) {
                    printf("Producto no encontrado.\n");
                }
                break;
            }

            case 5: {
                char nombre[50];
                int encontrado = 0;

                printf("Ingrese el nombre del producto a eliminar: ");
                scanf("%s", nombre);

                for (int i = 0; i < cantidadProductos; i++) {
                    if (strcmp(nombres[i], nombre) == 0) {
                        for (int j = i; j < cantidadProductos - 1; j++) {
                            strcpy(nombres[j], nombres[j + 1]);
                            demandas[j] = demandas[j + 1];
                            tiemposProduccion[j] = tiemposProduccion[j + 1];
                            recursosRequeridos[j] = recursosRequeridos[j + 1];
                        }
                        cantidadProductos--;
                        encontrado = 1;
                        printf("Producto eliminado exitosamente.\n");
                        break;
                    }
                }

                if (!encontrado) {
                    printf("Producto no encontrado.\n");
                }
                break;
            }

            case 6: {
                int tiempoTotal = 0, recursosTotales = 0;

                for (int i = 0; i < cantidadProductos; i++) {
                    tiempoTotal += demandas[i] * tiemposProduccion[i];
                    recursosTotales += demandas[i] * recursosRequeridos[i];
                }

                printf("\n--- Resultados de Produccion ---\n");
                printf("Tiempo total requerido: %d\n", tiempoTotal);
                printf("Recursos totales requeridos: %d\n", recursosTotales);

                if (tiempoTotal <= tiempoDisponible && recursosTotales <= recursosDisponibles) {
                    printf("La fabrica puede cumplir con la demanda.\n");
                } else {
                    printf("La fabrica NO puede cumplir con la demanda.\n");
                }
                break;
            }

            case 7:
                printf("Saliendo del programa.\n");
                break;

            default:
                printf("Opcion no valida.\n");
                break;
        }
    } while (opcion != 7);

    return 0;
}
