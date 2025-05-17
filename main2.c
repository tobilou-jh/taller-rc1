#include <stdio.h>
#include <string.h>
#include "funcion.h"

int main() {
    // Productos y materiales
    char nombres[5][50];
    int demandas[5], tiemposProduccion[5], cantidadProductos = 0;
    char matNombres[5][10][50];
    int matCants[5][10], matCount[5] = {0};
    char recursosNombres[50][50];
    int recursosDisponibles[50], cantRecursosDisponibles = 0;
    int tiempoDisponible = 0, opcion;

    do {
        menufuncion();
        opcion = leeropc();

        switch(opcion) {
            case 1: {
                int opRec;
                do {
                    printf("\n--- Recursos disponibles en fabrica ---\n");
                    printf("1. Agregar o modificar recurso\n2. Ver recursos\n3. Volver\nSeleccione una opcion: ");
                    opRec = leeropc();
                    if (opRec == 1) {
                        if (cantRecursosDisponibles >= 50) {
                            printf("No se pueden agregar mas tipos de recursos.\n");
                            continue;
                        }
                        char nombreRecurso[50];
                        printf("Ingrese el nombre del recurso: ");
                        fflush(stdin);
                        fgets(nombreRecurso, 50, stdin);
                        lens(nombreRecurso);
                        int idx = -1;
                        for (int i = 0; i < cantRecursosDisponibles; i++)
                            if (strcmp(recursosNombres[i], nombreRecurso) == 0) { idx = i; break; }
                        if (idx == -1) {
                            strcpy(recursosNombres[cantRecursosDisponibles], nombreRecurso);
                            printf("Ingrese la cantidad disponible: ");
                            recursosDisponibles[cantRecursosDisponibles++] = validarEnteroPositivo();
                        } else {
                            printf("Ingrese la nueva cantidad disponible: ");
                            recursosDisponibles[idx] = validarEnteroPositivo();
                        }
                    } else if (opRec == 2) {
                        printf("\nRecursos disponibles:\n");
                        for (int i = 0; i < cantRecursosDisponibles; i++)
                            printf("  - %s: %d\n", recursosNombres[i], recursosDisponibles[i]);
                    }
                } while (opRec != 3);
                break;
            }
            case 2:
                printf("Ingrese el tiempo de produccion disponible: ");
                tiempoDisponible = validarEnteroPositivo();
                break;
            case 3:
                if (cantidadProductos >= 5) { printf("No se pueden agregar mas productos.\n"); break; }
                printf("Ingrese el nombre del producto: ");
                fflush(stdin);
                fgets(nombres[cantidadProductos], 50, stdin);
                lens(nombres[cantidadProductos]);
                printf("Ingrese la demanda: ");
                demandas[cantidadProductos] = validarCantidad();
                printf("Ingrese el tiempo de produccion por unidad: ");
                tiemposProduccion[cantidadProductos] = validarEnteroPositivo();
                matCount[cantidadProductos++] = 0;
                printf("Producto agregado exitosamente.\n");
                break;
            case 4: {
                if (cantidadProductos == 0) { printf("No hay productos para editar.\n"); break; }
                char nombre[50]; printf("Ingrese el nombre del producto a editar: ");
                fflush(stdin); fgets(nombre, 50, stdin); lens(nombre);
                int encontrado = 0;
                for (int i = 0; i < cantidadProductos; i++) {
                    if (strcmp(nombres[i], nombre) == 0) {
                        printf("Nuevo nombre: "); fflush(stdin); fgets(nombres[i], 50, stdin); lens(nombres[i]);
                        printf("Nueva demanda: "); demandas[i] = validarCantidad();
                        printf("Nuevo tiempo de produccion por unidad: "); tiemposProduccion[i] = validarEnteroPositivo();
                        printf("Producto editado correctamente.\n"); encontrado = 1; break;
                    }
                }
                if (!encontrado) printf("Producto no encontrado.\n");
                break;
            }
            case 5: {
                if (cantidadProductos == 0) { printf("No hay productos para eliminar.\n"); break; }
                char nombre[50]; printf("Ingrese el nombre del producto a eliminar: ");
                fflush(stdin); fgets(nombre, 50, stdin); lens(nombre);
                int encontrado = 0;
                for (int i = 0; i < cantidadProductos; i++) {
                    if (strcmp(nombres[i], nombre) == 0) {
                        for (int j = i; j < cantidadProductos - 1; j++) {
                            strcpy(nombres[j], nombres[j + 1]);
                            demandas[j] = demandas[j + 1];
                            tiemposProduccion[j] = tiemposProduccion[j + 1];
                            matCount[j] = matCount[j + 1];
                            for (int k = 0; k < 10; k++) {
                                strcpy(matNombres[j][k], matNombres[j + 1][k]);
                                matCants[j][k] = matCants[j + 1][k];
                            }
                        }
                        cantidadProductos--;
                        printf("Producto eliminado exitosamente.\n"); encontrado = 1; break;
                    }
                }
                if (!encontrado) printf("Producto no encontrado.\n");
                break;
            }
            case 6: {
                if (cantidadProductos == 0) { printf("No hay productos registrados.\n"); break; }
                char nombre[50]; printf("Ingrese el nombre del producto para gestionar materiales: ");
                fflush(stdin); fgets(nombre, 50, stdin); lens(nombre);
                int idx = -1;
                for (int i = 0; i < cantidadProductos; i++)
                    if (strcmp(nombres[i], nombre) == 0) { idx = i; break; }
                if (idx == -1) { printf("Producto no encontrado.\n"); break; }
                int opMat;
                do {
                    printf("\n--- Materiales para %s ---\n", nombres[idx]);
                    menufuncion2();
                    opMat = leeropc();
                    switch(opMat) {
                        case 1:
                            if (matCount[idx] >= 10) { printf("No se pueden agregar mas materiales a este producto.\n"); break; }
                            printf("Ingrese el nombre del material: ");
                            fflush(stdin); fgets(matNombres[idx][matCount[idx]], 50, stdin); lens(matNombres[idx][matCount[idx]]);
                            printf("Ingrese la cantidad requerida: ");
                            matCants[idx][matCount[idx]] = validarCantidad();
                            matCount[idx]++;
                            printf("Material agregado.\n"); break;
                        case 2: {
                            if (matCount[idx] == 0) { printf("No hay materiales para editar.\n"); break; }
                            char nombreMat[50]; printf("Ingrese el nombre del material a editar: ");
                            fflush(stdin); fgets(nombreMat, 50, stdin); lens(nombreMat);
                            int encontrado = 0;
                            for (int m = 0; m < matCount[idx]; m++) {
                                if (strcmp(matNombres[idx][m], nombreMat) == 0) {
                                    printf("Nuevo nombre: ");
                                    fflush(stdin); fgets(matNombres[idx][m], 50, stdin); lens(matNombres[idx][m]);
                                    printf("Nueva cantidad: "); matCants[idx][m] = validarCantidad();
                                    printf("Material editado.\n"); encontrado = 1; break;
                                }
                            }
                            if (!encontrado) printf("Material no encontrado.\n");
                            break;
                        }
                        case 3: {
                            if (matCount[idx] == 0) { printf("No hay materiales para eliminar.\n"); break; }
                            char nombreMat[50]; printf("Ingrese el nombre del material a eliminar: ");
                            fflush(stdin); fgets(nombreMat, 50, stdin); lens(nombreMat);
                            int encontrado = 0;
                            for (int m = 0; m < matCount[idx]; m++) {
                                if (strcmp(matNombres[idx][m], nombreMat) == 0) {
                                    for (int n = m; n < matCount[idx] - 1; n++) {
                                        strcpy(matNombres[idx][n], matNombres[idx][n+1]);
                                        matCants[idx][n] = matCants[idx][n+1];
                                    }
                                    matCount[idx]--;
                                    printf("Material eliminado.\n"); encontrado = 1; break;
                                }
                            }
                            if (!encontrado) printf("Material no encontrado.\n");
                            break;
                        }
                        case 4:
                            if (matCount[idx] == 0) printf("No hay materiales registrados para este producto.\n");
                            else for (int m = 0; m < matCount[idx]; m++)
                                printf("  - %s: %d\n", matNombres[idx][m], matCants[idx][m]);
                            break;
                        case 5: printf("Volviendo al menu principal...\n"); break;
                        default: printf("Opcion no valida.\n");
                    }
                } while (opMat != 5);
                break;
            }
            case 7: {
                if (cantidadProductos == 0) { printf("No hay productos registrados.\n"); break; }
                int tiempoTotal = 0, cantReqs = 0;
                char reqNombres[50][50];
                int reqCantidades[50] = {0};
                for (int i = 0; i < cantidadProductos; i++) {
                    tiempoTotal += demandas[i] * tiemposProduccion[i];
                    for (int m = 0; m < matCount[i]; m++) {
                        int idx = -1;
                        for (int r = 0; r < cantReqs; r++)
                            if (strcmp(reqNombres[r], matNombres[i][m]) == 0) { idx = r; break; }
                        int totalMat = demandas[i] * matCants[i][m];
                        if (idx == -1) {
                            strcpy(reqNombres[cantReqs], matNombres[i][m]);
                            reqCantidades[cantReqs] = totalMat;
                            cantReqs++;
                        } else {
                            reqCantidades[idx] += totalMat;
                        }
                    }
                }
                int puedeCumplir = 1;
                printf("\n--- Resultados de Produccion ---\n");
                printf("1. El tiempo total de fabricacion requerido para cumplir con la demanda: %d\n", tiempoTotal);
                printf("2. Recursos/materiales necesarios:\n");
                for (int r = 0; r < cantReqs; r++) {
                    printf("   - %s: %d (disponible: ", reqNombres[r], reqCantidades[r]);
                    int disp = 0, found = 0;
                    for (int z = 0; z < cantRecursosDisponibles; z++)
                        if (strcmp(reqNombres[r], recursosNombres[z]) == 0) { disp = recursosDisponibles[z]; found = 1; break; }
                    printf("%d)\n", disp);
                    if (!found) puedeCumplir = 0;
                    if (reqCantidades[r] > disp) puedeCumplir = 0;
                }
                printf("3. ");
                if (tiempoTotal > tiempoDisponible) puedeCumplir = 0;
                if (puedeCumplir == 1)
                    printf("La fabrica puede cumplir con la demanda total.\n");
                else
                    printf("La fabrica NO puede cumplir con la demanda total.\n");

                // Evaluar cada producto individualmente
                printf("\n4. Cumplimiento de demanda por producto:\n");
                for (int i = 0; i < cantidadProductos; i++) {
                    int puede = 1;
                    int tiempoNecesario = demandas[i] * tiemposProduccion[i];
                    if (tiempoNecesario > tiempoDisponible) puede = 0;
                    for (int m = 0; m < matCount[i]; m++) {
                        int req = demandas[i] * matCants[i][m];
                        int disp = 0, found = 0;
                        for (int z = 0; z < cantRecursosDisponibles; z++)
                            if (strcmp(matNombres[i][m], recursosNombres[z]) == 0) { disp = recursosDisponibles[z]; found = 1; break; }
                        if (!found) puede = 0;
                        if (req > disp) puede = 0;
                    }
                    printf("   - %s: ", nombres[i]);
                    if (puede == 1)
                        printf("SI puede cumplir");
                    else
                        printf("NO puede cumplir");
                    printf(" | Tiempo de produccion requerido: %d\n", tiempoNecesario);
                }
                printf("Si desea actulizar el stock de recursos selecione la opcion 1 del menu principal.\n");
                printf("Si desea actulizar el tiempo de producion selecione la opcion 2 del menu principal.\n");
                
                break;
            }
            case 8:
                if (cantidadProductos == 0) { printf("No hay productos registrados.\n"); break; }
                for (int i = 0; i < cantidadProductos; i++) {
                    printf("\nProducto: %s\nDemanda: %d\nTiempo por unidad: %d\nMateriales:\n",
                        nombres[i], demandas[i], tiemposProduccion[i]);
                    if (matCount[i] == 0) printf("  (Sin materiales)\n");
                    else for (int m = 0; m < matCount[i]; m++)
                        printf("  - %s: %d\n", matNombres[i][m], matCants[i][m]);
                }
                break;
            case 9: printf("Saliendo del programa.\n"); 
            break;
            default: printf("Opcion no valida.\n");
        }
    } while (opcion != 9);

    return 0;
}
