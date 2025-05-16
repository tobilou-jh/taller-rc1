#include <stdio.h>
#include <string.h>
#include "funcion.h" 

int main() {
    // Productos
    char nombres[5][50];
    int demandas[5];
    int tiemposProduccion[5];
    int cantidadProductos = 0;

    // Materiales por producto
    char matNombre0[10][50], matNombre1[10][50], matNombre2[10][50], matNombre3[10][50], matNombre4[10][50];
    int matCant0[10], matCant1[10], matCant2[10], matCant3[10], matCant4[10];
    int matCount[5] = {0,0,0,0,0};

    // Recursos disponibles en fabrica (materiales globales)
    char recursosNombres[50][50];
    int recursosDisponibles[50];
    int cantRecursosDisponibles = 0;

    int tiempoDisponible = 0;
    int opcion;

    do {
        printf("\n--- Menu ---\n");
        printf("1. Gestionar recursos disponibles (materiales en fabrica)\n");
        printf("2. Ingresar tiempo de produccion disponible\n");
        printf("3. Agregar producto\n");
        printf("4. Editar producto\n");
        printf("5. Eliminar producto\n");
        printf("6. Gestionar materiales de un producto\n");
        printf("7. Calcular produccion\n");
        printf("8. Mostrar productos y materiales\n");
        printf("9. Salir\n");
        printf("Seleccione una opcion: ");
        opcion = leeropc();

        switch(opcion) {
            case 1: { // Gestionar recursos
                int opRec;
                do {
                    printf("\n--- Recursos disponibles en fabrica ---\n");
                    printf("1. Agregar o modificar recurso\n");
                    printf("2. Ver recursos\n");
                    printf("3. Volver\n");
                    printf("Seleccione una opcion: ");
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

                        // Buscar si ya existe
                        int idx = -1;
                        for (int i = 0; i < cantRecursosDisponibles; i++) {
                            if (strcmp(recursosNombres[i], nombreRecurso) == 0) {
                                idx = i;
                                break;
                            }
                        }
                        if (idx == -1) { // Nuevo recurso
                            strcpy(recursosNombres[cantRecursosDisponibles], nombreRecurso);
                            printf("Ingrese la cantidad disponible: ");
                            recursosDisponibles[cantRecursosDisponibles] = validarEnteroPositivo();
                            cantRecursosDisponibles++;
                        } else { // Modificar recurso existente
                            printf("Ingrese la nueva cantidad disponible: ");
                            recursosDisponibles[idx] = validarEnteroPositivo();
                        }
                    } else if (opRec == 2) {
                        printf("\nRecursos disponibles:\n");
                        for (int i = 0; i < cantRecursosDisponibles; i++) {
                            printf("  - %s: %d\n", recursosNombres[i], recursosDisponibles[i]);
                        }
                    }
                } while (opRec != 3);
                break;
            }

            case 2:
                printf("Ingrese el tiempo de produccion disponible: ");
                tiempoDisponible = validarEnteroPositivo();
                break;

            case 3:
                if (cantidadProductos >= 5) {
                    printf("No se pueden agregar mas productos.\n");
                    break;
                }
                printf("Ingrese el nombre del producto: ");
                fflush(stdin);
                fgets(nombres[cantidadProductos], 50, stdin);
                lens(nombres[cantidadProductos]);
                printf("Ingrese la demanda: ");
                demandas[cantidadProductos] = validarCantidad();
                printf("Ingrese el tiempo de produccion por unidad: ");
                tiemposProduccion[cantidadProductos] = validarEnteroPositivo();
                matCount[cantidadProductos] = 0; // inicializa la lista de materiales
                cantidadProductos++;
                printf("Producto agregado exitosamente.\n");
                break;

            case 4: { // Editar producto
                if (cantidadProductos == 0) {
                    printf("No hay productos para editar.\n");
                    break;
                }
                char nombre[50];
                printf("Ingrese el nombre del producto a editar: ");
                fflush(stdin);
                fgets(nombre, 50, stdin);
                lens(nombre);
                int encontrado = 0;
                for (int i = 0; i < cantidadProductos; i++) {
                    if (strcmp(nombres[i], nombre) == 0) {
                        printf("Nuevo nombre: ");
                        fflush(stdin);
                        fgets(nombres[i], 50, stdin);
                        lens(nombres[i]);
                        printf("Nueva demanda: ");
                        demandas[i] = validarCantidad();
                        printf("Nuevo tiempo de produccion por unidad: ");
                        tiemposProduccion[i] = validarEnteroPositivo();
                        printf("Producto editado correctamente.\n");
                        encontrado = 1;
                        break;
                    }
                }
                if (!encontrado) printf("Producto no encontrado.\n");
                break;
            }

            case 5: { // Eliminar producto
                if (cantidadProductos == 0) {
                    printf("No hay productos para eliminar.\n");
                    break;
                }
                char nombre[50];
                printf("Ingrese el nombre del producto a eliminar: ");
                fflush(stdin);
                fgets(nombre, 50, stdin);
                lens(nombre);

                int encontrado = 0;
                for (int i = 0; i < cantidadProductos; i++) {
                    if (strcmp(nombres[i], nombre) == 0) {
                        for (int j = i; j < cantidadProductos - 1; j++) {
                            strcpy(nombres[j], nombres[j + 1]);
                            demandas[j] = demandas[j + 1];
                            tiemposProduccion[j] = tiemposProduccion[j + 1];
                            matCount[j] = matCount[j + 1];
                            for (int k = 0; k < 10; k++) {
                                if(j==0){strcpy(matNombre0[k], matNombre1[k]); matCant0[k]=matCant1[k];}
                                if(j==1){strcpy(matNombre1[k], matNombre2[k]); matCant1[k]=matCant2[k];}
                                if(j==2){strcpy(matNombre2[k], matNombre3[k]); matCant2[k]=matCant3[k];}
                                if(j==3){strcpy(matNombre3[k], matNombre4[k]); matCant3[k]=matCant4[k];}
                            }
                        }
                        cantidadProductos--;
                        printf("Producto eliminado exitosamente.\n");
                        encontrado = 1;
                        break;
                    }
                }
                if (!encontrado) printf("Producto no encontrado.\n");
                break;
            }

            case 6: { // Materiales de producto
                if (cantidadProductos == 0) {
                    printf("No hay productos registrados.\n");
                    break;
                }
                char nombre[50];
                printf("Ingrese el nombre del producto para gestionar materiales: ");
                fflush(stdin);
                fgets(nombre, 50, stdin);
                lens(nombre);

                int idx = -1;
                for (int i = 0; i < cantidadProductos; i++) {
                    if (strcmp(nombres[i], nombre) == 0) {
                        idx = i;
                        break;
                    }
                }
                if (idx == -1) {
                    printf("Producto no encontrado.\n");
                    break;
                }

                int opMat;
                do {
                    printf("\n--- Materiales para %s ---\n", nombres[idx]);
                    printf("1. Agregar material\n");
                    printf("2. Editar material\n");
                    printf("3. Eliminar material\n");
                    printf("4. Ver materiales\n");
                    printf("5. Volver\n");
                    printf("Seleccione una opcion: ");
                    opMat = leeropc();

                    char (*matNombres)[50];
                    int *matCants;
                    if(idx==0){matNombres=matNombre0; matCants=matCant0;}
                    if(idx==1){matNombres=matNombre1; matCants=matCant1;}
                    if(idx==2){matNombres=matNombre2; matCants=matCant2;}
                    if(idx==3){matNombres=matNombre3; matCants=matCant3;}
                    if(idx==4){matNombres=matNombre4; matCants=matCant4;}

                    switch(opMat) {
                        case 1:
                            if (matCount[idx] >= 10) {
                                printf("No se pueden agregar mas materiales a este producto.\n");
                                break;
                            }
                            printf("Ingrese el nombre del material: ");
                            fflush(stdin);
                            fgets(matNombres[matCount[idx]], 50, stdin);
                            lens(matNombres[matCount[idx]]);
                            printf("Ingrese la cantidad requerida: ");
                            matCants[matCount[idx]] = validarCantidad();
                            matCount[idx]++;
                            printf("Material agregado.\n");
                            break;

                        case 2: {
                            if (matCount[idx] == 0) {
                                printf("No hay materiales para editar.\n");
                                break;
                            }
                            char nombreMat[50];
                            printf("Ingrese el nombre del material a editar: ");
                            fflush(stdin);
                            fgets(nombreMat, 50, stdin);
                            lens(nombreMat);

                            int encontrado = 0;
                            for (int m = 0; m < matCount[idx]; m++) {
                                if (strcmp(matNombres[m], nombreMat) == 0) {
                                    printf("Nuevo nombre: ");
                                    fflush(stdin);
                                    fgets(matNombres[m], 50, stdin);
                                    lens(matNombres[m]);
                                    printf("Nueva cantidad: ");
                                    matCants[m] = validarCantidad();
                                    printf("Material editado.\n");
                                    encontrado = 1;
                                    break;
                                }
                            }
                            if (!encontrado) printf("Material no encontrado.\n");
                            break;
                        }

                        case 3: {
                            if (matCount[idx] == 0) {
                                printf("No hay materiales para eliminar.\n");
                                break;
                            }
                            char nombreMat[50];
                            printf("Ingrese el nombre del material a eliminar: ");
                            fflush(stdin);
                            fgets(nombreMat, 50, stdin);
                            lens(nombreMat);

                            int encontrado = 0;
                            for (int m = 0; m < matCount[idx]; m++) {
                                if (strcmp(matNombres[m], nombreMat) == 0) {
                                    for (int n = m; n < matCount[idx] - 1; n++) {
                                        strcpy(matNombres[n], matNombres[n+1]);
                                        matCants[n] = matCants[n+1];
                                    }
                                    matCount[idx]--;
                                    printf("Material eliminado.\n");
                                    encontrado = 1;
                                    break;
                                }
                            }
                            if (!encontrado) printf("Material no encontrado.\n");
                            break;
                        }

                        case 4:
                            if (matCount[idx] == 0) {
                                printf("No hay materiales registrados para este producto.\n");
                            } else {
                                for (int m = 0; m < matCount[idx]; m++) {
                                    printf("  - %s: %d\n", matNombres[m], matCants[m]);
                                }
                            }
                            break;

                        case 5:
                            printf("Volviendo al menu principal...\n");
                            break;

                        default:
                            printf("Opcion no valida.\n");
                    }
                } while (opMat != 5);
                break;
            }

            case 7: { // Calcular produccion
                if (cantidadProductos == 0) {
                    printf("No hay productos registrados.\n");
                    break;
                }
                int tiempoTotal = 0;
                // Acumuladores de requerimientos globales por nombre de material
                char reqNombres[50][50];
                int reqCantidades[50] = {0};
                int cantReqs = 0;

                // 1. Calcular tiempo total y requerimientos de materiales
                for (int i = 0; i < cantidadProductos; i++) {
                    tiempoTotal += demandas[i] * tiemposProduccion[i];
                    char (*matNombres)[50];
                    int *matCants;
                    if(i==0){matNombres=matNombre0; matCants=matCant0;}
                    if(i==1){matNombres=matNombre1; matCants=matCant1;}
                    if(i==2){matNombres=matNombre2; matCants=matCant2;}
                    if(i==3){matNombres=matNombre3; matCants=matCant3;}
                    if(i==4){matNombres=matNombre4; matCants=matCant4;}
                    for (int m = 0; m < matCount[i]; m++) {
                        int idx = -1;
                        for (int r = 0; r < cantReqs; r++) {
                            if (strcmp(reqNombres[r], matNombres[m]) == 0) {
                                idx = r;
                                break;
                            }
                        }
                        int totalMat = demandas[i] * matCants[m];
                        if (idx == -1) {
                            strcpy(reqNombres[cantReqs], matNombres[m]);
                            reqCantidades[cantReqs] = totalMat;
                            cantReqs++;
                        } else {
                            reqCantidades[idx] += totalMat;
                        }
                    }
                }

                // 2. Mostrar resultados y verificar si alcanza
                int puedeCumplir = 1;
                printf("\n--- Resultados de Produccion ---\n");
                printf("1. El tiempo total de fabricacion requerido para cumplir con la demanda: %d\n", tiempoTotal);
                printf("2. Recursos/materiales necesarios:\n");
                for (int r = 0; r < cantReqs; r++) {
                    printf("   - %s: %d (disponible: ", reqNombres[r], reqCantidades[r]);
                    int disp = 0;
                    int found = 0;
                    for (int z = 0; z < cantRecursosDisponibles; z++) {
                        if (strcmp(reqNombres[r], recursosNombres[z]) == 0) {
                            disp = recursosDisponibles[z];
                            found = 1;
                            break;
                        }
                    }
                    printf("%d)\n", disp);
                    if (!found || reqCantidades[r] > disp) puedeCumplir = 0;
                }
                printf("3. ");
                if (tiempoTotal > tiempoDisponible) puedeCumplir = 0;
                if (puedeCumplir) {
                    printf("La fabrica puede cumplir con la demanda.\n");
                } else {
                    printf("La fabrica NO puede cumplir con la demanda.\n");
                }
                break;
            }

            case 8: { // Mostrar productos y materiales
                if (cantidadProductos == 0) {
                    printf("No hay productos registrados.\n");
                    break;
                }
                for (int i = 0; i < cantidadProductos; i++) {
                    printf("\nProducto: %s\n", nombres[i]);
                    printf("Demanda: %d\n", demandas[i]);
                    printf("Tiempo por unidad: %d\n", tiemposProduccion[i]);
                    printf("Materiales:\n");
                    char (*matNombres)[50];
                    int *matCants;
                    if(i==0){matNombres=matNombre0; matCants=matCant0;}
                    if(i==1){matNombres=matNombre1; matCants=matCant1;}
                    if(i==2){matNombres=matNombre2; matCants=matCant2;}
                    if(i==3){matNombres=matNombre3; matCants=matCant3;}
                    if(i==4){matNombres=matNombre4; matCants=matCant4;}
                    if (matCount[i] == 0) {
                        printf("  (Sin materiales)\n");
                    } else {
                        for (int m = 0; m < matCount[i]; m++) {
                            printf("  - %s: %d\n", matNombres[m], matCants[m]);
                        }
                    }
                }
                break;
            }

            case 9:
                printf("Saliendo del programa.\n");
                break;

            default:
                printf("Opcion no valida.\n");
        }
    } while (opcion != 9);

    return 0;
}
