#include <stdio.h>
#include <string.h>
#include "funcion.h"

int main()
{
    char nombres[5][50];
    int demandas[5];
    int tiemposProduccion[5];
    int recursosRequeridos[5];
    int cantidadProductos = 0;
    int tiempoDisponible = 0, recursosDisponibles = 0;
    int opcion;

    do
    {
        printf("\n--- Menu ---\n");
        printf("1. Ingresar tiempo de produccion disponible\n");
        printf("2. Ingresar cantidad de recursos disponibles\n");
        printf("3. Agregar producto\n");
        printf("4. Editar producto\n");
        printf("5. Eliminar producto\n");
        printf("6. Calcular produccion\n");
        printf("7. Salir\n");
        printf("Seleccione una opcion: ");
        opcion = leeropc();

        switch (opcion)
        {
        case 1:
            printf("Ingrese el tiempo de produccion disponible: ");
            tiempoDisponible = validarEnteroPositivo();
            break;

        case 2:
            printf("Ingrese la cantidad de recursos disponibles: ");
            recursosDisponibles = validarEnteroPositivo();
            break;

        case 3:
            if (cantidadProductos >= 5)
            {
                printf("No se pueden agregar mas productos.\n");
                break;
            }

            int nombreValido = 0;
            while (!nombreValido)
            {
                printf("Ingrese el nombre del producto: ");
                fflush(stdin);
                fgets(nombres[cantidadProductos], 50, stdin);
                lens(nombres[cantidadProductos]);

                nombreValido = 1;
                for (int i = 0; i < cantidadProductos; i++)
                {
                    if (strcmp(nombres[i], nombres[cantidadProductos]) == 0)
                    {
                        printf("El producto ya existe. Intente con otro nombre.\n");
                        nombreValido = 0;
                        break;
                    }
                }
            }

            printf("Ingrese la cantidad demandada: ");
            demandas[cantidadProductos] = validarCantidad();
            printf("Ingrese el tiempo de fabricacion por unidad: ");
            tiemposProduccion[cantidadProductos] = validarEnteroPositivo();
            printf("Ingrese los recursos requeridos por unidad: ");
            recursosRequeridos[cantidadProductos] = validarEnteroPositivo();

            cantidadProductos++;
            printf("Producto agregado exitosamente.\n");
            break;

        case 4:
        {
            if (cantidadProductos == 0)
            {
                printf("No hay productos para editar.\n");
                break;
            }

            char nombre[50];
            int encontrado = 0;

            printf("Ingrese el nombre del producto a editar: ");
            fflush(stdin);
            fgets(nombre, 50, stdin);
            lens(nombre);

            for (int i = 0; i < cantidadProductos; i++)
            {
                if (strcmp(nombres[i], nombre) == 0)
                {
                    printf("Producto encontrado. Ingrese los nuevos datos:\n");
                    printf("Nuevo nombre: ");
                    fflush(stdin);
                    fgets(nombres[i], 50, stdin);
                    lens(nombres[i]);

                    printf("Nueva cantidad demandada: ");
                    demandas[i] = validarEnteroPositivo();
                    printf("Nuevo tiempo de fabricación por unidad: ");
                    tiemposProduccion[i] = validarEnteroPositivo();
                    printf("Nuevos recursos requeridos por unidad: ");
                    recursosRequeridos[i] = validarEnteroPositivo();
                    encontrado = 1;
                    printf("Producto editado exitosamente.\n");
                    break;
                }
            }

            if (!encontrado)
            {
                printf("Producto no encontrado.\n");
            }
            break;
        }
        case 5:
        {
            char nombre[50];
            int encontrado = 0;

            if (cantidadProductos == 0)
            {
                printf("No hay productos en la lista.\n");
                break;
            }

            printf("Ingrese el nombre del producto a eliminar: ");
            fflush(stdin);
            fgets(nombre, 50, stdin);
            lens(nombre);

            for (int i = 0; i < cantidadProductos; i++)
            {
                if (strcmp(nombres[i], nombre) == 0)
                {
                    for (int j = i; j < cantidadProductos - 1; j++)
                    {
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

            if (!encontrado)
            {
                printf("Producto no encontrado.\n");
            }
            break;
        }

        case 6:
        {
            if (cantidadProductos == 0)
            {
                printf("No hay productos registrados para calcular la producción.\n");
                break;
            }

            int tiempoTotal = 0, recursosTotales = 0;

            for (int i = 0; i < cantidadProductos; i++)
            {
                tiempoTotal += demandas[i] * tiemposProduccion[i];
                recursosTotales += demandas[i] * recursosRequeridos[i];
            }

            printf("\n--- Resultados de Producción ---\n");
            printf("Tiempo total requerido: %d\n", tiempoTotal);
            printf("Recursos totales requeridos: %d\n", recursosTotales);

            if (tiempoTotal <= tiempoDisponible && recursosTotales <= recursosDisponibles)
            {
                printf("La fábrica puede cumplir con la demanda.\n");
            }
            else
            {
                printf("La fábrica NO puede cumplir con la demanda.\n");
            }
            break;
        }

        case 7:
            printf("Saliendo del programa.\n");
            break;

        default:
            printf("Opción no valida.\n");
            break;
        }
    } while (opcion != 7);

    return 0;
}
