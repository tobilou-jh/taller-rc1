//Una fabrica de componentes electronicos necesita optimizar su produccion para cumplir 
//con la demanda de cinco productos distintos. Cada producto tiene un tiempo de fabricacion especifico y requiere una cantidad fija de recursos. 
//El equipo de ingenieria ha identificado que la linea de produccion tiene limitaciones de tiempo y recursos que deben ser tomadas en cuenta.
#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[]) {
    int opc;
    do {
        printf("Menu de opciones:\n");
        printf("1. Ingresar nombres de cada productos\n");
        printf("2. Ingresar tiempo de fabricacion y recursos de cada producto\n");
        printf("3. Calcular el tiempo total de fabricacion requerido para cumplir con la demanda\n");
        printf("4. Calcular la cantidad de recursos necesarios para producir los productos.\n");
        printf("5. Calcular si la fabrica puede cumplir con la demanda dada una cantidad limitada de recursos y tiempo de produccion disponible.\n");
        printf("6. Modificar nombre del producto\n");
        printf("7. Modificar tiempo de fabricacion y recursos de cada producto\n");
        printf("8. Eliminar producto\n");
        printf("9. Salir\n");
        printf("Seleccione una opcion: ");
        
        scanf("%d", &opc);
        fflush(stdin); // Limpiar el buffer de entrada
        switch(opc) {
            case 1:
                printf("Ingrese el nombre de los productos\n");
                char productos[5][20];
                for (int i = 0; i < 5; i++) {
                    printf("Producto %d: ", i + 1);
                    scanf("%s", productos[i]);
                    fflush(stdin); // Limpiar el buffer de entrada
                }
                break;
            case 2:
                printf("Ingresar tiempo de fabricacion y recursos de cada producto\n");
                float tiempoFabricacion[5];
                float recursos[5];
                for (int i = 0; i < 5; i++) {
                    printf("Producto %s - Tiempo de fabricacion: ", productos[i]);
                    scanf("%d", &tiempoFabricacion[i]);
                    fflush(stdin); // Limpiar el buffer de entrada
                    printf("Producto %s - Recursos requeridos: ", productos[i]);
                    scanf("%d", &recursos[i]);
                    fflush(stdin); // Limpiar el buffer de entrada
                }
                break;
            case 3:
                printf("Calcular el tiempo total de fabricacion requerido para cumplir con la demanda\n");
                int demanda[5];
                for (int i = 0; i < 5; i++) {
                    printf("Demanda para el producto %s: ", productos[i]);
                    scanf("%d", &demanda[i]);
                    fflush(stdin); // Limpiar el buffer de entrada
                }
                float tiempoTotal = 0;
                for (int i = 0; i < 5; i++) {
                    tiempoTotal += tiempoFabricacion[i] * demanda[i];
                }
                printf("Tiempo total de fabricacion requerido: %.2f horas\n", tiempoTotal);
                break;
            case 4:
                printf("Calcular la cantidad de recursos necesarios para producir los productos.\n");
                float recursosTotales = 0;
                for (int i = 0; i < 5; i++) {
                    recursosTotales += recursos[i] * demanda[i];
                } 
                printf("Recursos totales necesarios: %.2f unidades\n", recursosTotales);      
                break;
            case 5:
                printf("Calcular si la fabrica puede cumplir con la demanda dada una cantidad limitada de recursos y tiempo de produccion disponible.\n");
                float tiempoDisponible, recursosDisponibles;
                printf("Ingrese el tiempo de produccion disponible: ");
                scanf("%f", &tiempoDisponible);
                fflush(stdin); // Limpiar el buffer de entrada
                printf("Ingrese la cantidad de recursos disponibles: ");     
                scanf("%f", &recursosDisponibles);
                fflush(stdin); // Limpiar el buffer de entrada
                if (tiempoTotal <= tiempoDisponible && recursosTotales <= recursosDisponibles) {
                    printf("La fabrica puede cumplir con la demanda.\n");
                } else {
                    printf("La fabrica NO puede cumplir con la demanda.\n");
                }
                break;
            case 6:
                printf("Modificar nombre del producto\n");
                char nuevoNombre[20];
                printf("Ingrese el nombre del producto a modificar: ");
                scanf("%s", nuevoNombre);
                fflush(stdin); // Limpiar el buffer de entrada
                for (int i = 0; i < 5; i++) {
                    if (strcmp(productos[i], nuevoNombre) == 0) {
                        printf("Ingrese el nuevo nombre para el producto %s: ", productos[i]);
                        scanf("%s", productos[i]);
                        fflush(stdin); // Limpiar el buffer de entrada
                        printf("Nombre modificado exitosamente.\n");
                        break;
                    } else {
                        printf("Producto no encontrado.\n");
                    }
                }            
                break;
            case 7:
                printf("Modificar tiempo de fabricacion y recursos de cada producto\n");
                char nombreProducto[20];
                printf("Ingrese el nombre del producto a modificar: ");
                scanf("%s", nombreProducto);
                fflush(stdin); // Limpiar el buffer de entrada
                for (int i = 0; i < 5; i++) {
                    if (strcmp(productos[i], nombreProducto) == 0) {
                        printf("Producto %s - Nuevo tiempo de fabricacion: ", productos[i]);
                        scanf("%f", &tiempoFabricacion[i]);
                        fflush(stdin); // Limpiar el buffer de entrada
                        printf("Producto %s - Nuevos recursos requeridos: ", productos[i]);
                        scanf("%f", &recursos[i]);
                        fflush(stdin); // Limpiar el buffer de entrada
                        printf("Datos modificados exitosamente.\n");
                        break;
                    } else {
                        printf("Producto no encontrado.\n");
                    }
                }
                break;
            case 8:
                printf("Eliminar producto\n");
                char eliminarProducto[20];
                printf("Ingrese el nombre del producto a eliminar: ");  
                scanf("%s", eliminarProducto);
                fflush(stdin); // Limpiar el buffer de entrada
                for (int i = 0; i < 5; i++) {
                    if (strcmp(productos[i], eliminarProducto) == 0) {
                        strcpy(productos[i], productos[4]);
                        printf("Producto %s eliminado exitosamente.\n", eliminarProducto);
                        break;
                    } else {
                        printf("Producto no encontrado.\n");
                    }
                }
                break;
            case 9:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Intente nuevamente.\n");
        }
    } while(opc != 9);

    return 0;
}

