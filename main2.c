#include <stdio.h>
#include <string.h>
#include "funcion.h"

int main()
{
    // Productos y materiales
    char nombres[5][50];
    int demandas[5], tiemposProduccion[5], cantidadProductos = 0;
    char matNombres[5][10][50];
    int matCants[5][10], matCount[5] = {0};
    char recursosNombres[50][50];
    int recursosDisponibles[50], cantRecursosDisponibles = 0;
    int tiempoDisponible = 0, opcion;
    int verifica, verifica2, verifica3 = 0;

    // Declaraciones de punteros a los arreglos principales
    char (*pNombres)[50];
    int *pDemandas;
    int *pTiemposProduccion;
    char (*pMatNombres)[10][50];
    int (*pMatCants)[10];
    int *pMatCount;
    char (*pRecursosNombres)[50];
    int *pRecursosDisponibles;
    pNombres = nombres;
    pDemandas = demandas;
    pTiemposProduccion = tiemposProduccion;
    pMatNombres = matNombres;
    pMatCants = matCants;
    pMatCount = matCount;
    pRecursosNombres = recursosNombres;
    pRecursosDisponibles = recursosDisponibles;

    do
    {
        menufuncion();
        opcion = leeropc();

        switch (opcion)
        {
        case 1:
        {
            verifica3 = 1;
            int opRec;
            do
            {
                printf("\n--- Recursos disponibles en fabrica ---\n");
                printf("1. Agregar o modificar recurso\n2. Ver recursos\n3. Volver\nSeleccione una opcion: ");
                opRec = leeropc();
                if (opRec == 1)
                {
                    if (cantRecursosDisponibles >= 50)
                    {
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
                        if (strcmp(pRecursosNombres[i], nombreRecurso) == 0)
                        {
                            idx = i;
                            break;
                        }

                    if (idx == -1)
                    {
                        strcpy(pRecursosNombres[cantRecursosDisponibles], nombreRecurso);
                        printf("Ingrese la cantidad disponible: ");
                        pRecursosDisponibles[cantRecursosDisponibles++] = validarEnteroPositivo();
                    }
                    else
                    {
                        printf("Ingrese la cantidad adicional para el recurso: ");
                        pRecursosDisponibles[idx] += validarEnteroPositivo(); // 🔹 Suma en lugar de reemplazar
                    }
                }
                else if (opRec == 2)
                {
                    printf("\nRecursos disponibles:\n");
                    for (int i = 0; i < cantRecursosDisponibles; i++)
                        printf("  - %s: %d\n", pRecursosNombres[i], pRecursosDisponibles[i]);
                }
            } while (opRec != 3);
            break;
        }

        case 2:
            verifica2 = 1;
            printf("Ingrese el tiempo de produccion disponible(Horas): ");
            tiempoDisponible = validarEnteroPositivo();
            break;
        case 3:
            if (cantidadProductos >= 5)
            {
                printf("No se pueden agregar mas productos.\n");
                break;
            }
            printf("Ingrese el nombre del producto: ");
            fflush(stdin);
            fgets(pNombres[cantidadProductos], 50, stdin);
            lens(pNombres[cantidadProductos]);
            printf("Ingrese la demanda: ");
            pDemandas[cantidadProductos] = validarCantidad();
            printf("Ingrese el tiempo de produccion por unidad(horas): ");
            pTiemposProduccion[cantidadProductos] = validarEnteroPositivo();
            pMatCount[cantidadProductos++] = 0;
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
            printf("Ingrese el nombre del producto a editar: ");
            fflush(stdin);
            fgets(nombre, 50, stdin);
            lens(nombre);
            int encontrado = 0;
            for (int i = 0; i < cantidadProductos; i++)
            {
                if (strcmp(pNombres[i], nombre) == 0)
                {
                    printf("Nuevo nombre: ");
                    fflush(stdin);
                    fgets(pNombres[i], 50, stdin);
                    lens(pNombres[i]);
                    printf("Nueva demanda: ");
                    pDemandas[i] = validarCantidad();
                    printf("Nuevo tiempo de produccion por unidad(horas): ");
                    pTiemposProduccion[i] = validarEnteroPositivo();
                    printf("Producto editado correctamente.\n");
                    encontrado = 1;
                    break;
                }
            }
            if (!encontrado)
                printf("Producto no encontrado.\n");
            break;
        }
        case 5:
        {
            if (cantidadProductos == 0)
            {
                printf("No hay productos para eliminar.\n");
                break;
            }
            char nombre[50];
            printf("Ingrese el nombre del producto a eliminar: ");
            fflush(stdin);
            fgets(nombre, 50, stdin);
            lens(nombre);
            int encontrado = 0;
            for (int i = 0; i < cantidadProductos; i++)
            {
                if (strcmp(pNombres[i], nombre) == 0)
                {
                    for (int j = i; j < cantidadProductos - 1; j++)
                    {
                        strcpy(pNombres[j], pNombres[j + 1]);
                        pDemandas[j] = pDemandas[j + 1];
                        pTiemposProduccion[j] = pTiemposProduccion[j + 1];
                        pMatCount[j] = pMatCount[j + 1];
                        for (int k = 0; k < 10; k++)
                        {
                            strcpy(pMatNombres[j][k], pMatNombres[j + 1][k]);
                            pMatCants[j][k] = pMatCants[j + 1][k];
                        }
                    }
                    cantidadProductos--;
                    printf("Producto eliminado exitosamente.\n");
                    encontrado = 1;
                    break;
                }
            }
            if (!encontrado)
                printf("Producto no encontrado.\n");
            break;
        }
        case 6:
        {
            if (cantidadProductos == 0)
            {
                printf("No hay productos registrados.\n");
                break;
            }
            verifica = 1;
            char nombre[50];
            printf("Ingrese el nombre del producto para gestionar materiales: ");
            fflush(stdin);
            fgets(nombre, 50, stdin);
            lens(nombre);
            int idx = -1;
            for (int i = 0; i < cantidadProductos; i++)
                if (strcmp(pNombres[i], nombre) == 0)
                {
                    idx = i;
                    break;
                }
            if (idx == -1)
            {
                printf("Producto no encontrado.\n");
                break;
            }
            int opMat;
            do
            {
                printf("\n--- Materiales para %s ---\n", pNombres[idx]);
                menufuncion2();
                opMat = leeropc();
                switch (opMat)
                {
                case 1:
                    if (pMatCount[idx] >= 10)
                    {
                        printf("No se pueden agregar mas materiales a este producto.\n");
                        break;
                    }
                    printf("Ingrese el nombre del material: ");
                    fflush(stdin);
                    fgets(pMatNombres[idx][pMatCount[idx]], 50, stdin);
                    lens(pMatNombres[idx][pMatCount[idx]]);
                    printf("Ingrese la cantidad requerida: ");
                    pMatCants[idx][pMatCount[idx]] = validarCantidad();
                    pMatCount[idx]++;
                    printf("Material agregado.\n");
                    break;
                case 2:
                {
                    if (pMatCount[idx] == 0)
                    {
                        printf("No hay materiales para editar.\n");
                        break;
                    }
                    char nombreMat[50];
                    printf("Ingrese el nombre del material a editar: ");
                    fflush(stdin);
                    fgets(nombreMat, 50, stdin);
                    lens(nombreMat);
                    int encontrado = 0;
                    for (int m = 0; m < pMatCount[idx]; m++)
                    {
                        if (strcmp(pMatNombres[idx][m], nombreMat) == 0)
                        {
                            printf("Nuevo nombre: ");
                            fflush(stdin);
                            fgets(pMatNombres[idx][m], 50, stdin);
                            lens(pMatNombres[idx][m]);
                            printf("Nueva cantidad: ");
                            pMatCants[idx][m] = validarCantidad();
                            printf("Material editado.\n");
                            encontrado = 1;
                            break;
                        }
                    }
                    if (!encontrado)
                        printf("Material no encontrado.\n");
                    break;
                }
                case 3:
                {
                    if (pMatCount[idx] == 0)
                    {
                        printf("No hay materiales para eliminar.\n");
                        break;
                    }
                    char nombreMat[50];
                    printf("Ingrese el nombre del material a eliminar: ");
                    fflush(stdin);
                    fgets(nombreMat, 50, stdin);
                    lens(nombreMat);
                    int encontrado = 0;
                    for (int m = 0; m < pMatCount[idx]; m++)
                    {
                        if (strcmp(pMatNombres[idx][m], nombreMat) == 0)
                        {
                            for (int n = m; n < pMatCount[idx] - 1; n++)
                            {
                                strcpy(pMatNombres[idx][n], pMatNombres[idx][n + 1]);
                                pMatCants[idx][n] = pMatCants[idx][n + 1];
                            }
                            pMatCount[idx]--;
                            printf("Material eliminado.\n");
                            encontrado = 1;
                            break;
                        }
                    }
                    if (!encontrado)
                        printf("Material no encontrado.\n");
                    break;
                }
                case 4:
                    if (pMatCount[idx] == 0)
                        printf("No hay materiales registrados para este producto.\n");
                    else
                        for (int m = 0; m < pMatCount[idx]; m++)
                            printf("  - %s: %d\n", pMatNombres[idx][m], pMatCants[idx][m]);
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
       case 7: {
    if (cantidadProductos == 0) { printf("No hay productos registrados.\n"); break; }
    if (cantRecursosDisponibles == 0) { printf("No hay recursos disponibles registrados.\n"); break; }
    if (verifica2 == 0) { printf("No hay tiempo de produccion disponible registrado.\n"); break; }
    if (verifica == 0) { printf("No hay materiales registrados.\n"); break; }

    int tiempoTotal = 0, cantReqs = 0;
    char reqNombres[50][50];
    int reqCantidades[50] = {0};

    // Calculo de tiempo total y materiales requeridos
    for (int i = 0; i < cantidadProductos; i++) {
        tiempoTotal += pDemandas[i] * pTiemposProduccion[i];
        for (int m = 0; m < pMatCount[i]; m++) {
            int idx = -1;
            for (int r = 0; r < cantReqs; r++)
                if (strcmp(reqNombres[r], pMatNombres[i][m]) == 0) { idx = r; break; }
            int totalMat = pDemandas[i] * pMatCants[i][m];
            if (idx == -1) {
                strcpy(reqNombres[cantReqs], pMatNombres[i][m]);
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
    printf("   El tiempo de produccion disponible: %d\n", tiempoDisponible);
    printf("2. Recursos/materiales necesarios:\n");

    for (int r = 0; r < cantReqs; r++) {
        printf("   - %s: %d (disponible: ", reqNombres[r], reqCantidades[r]);
        int disp = 0, found = 0;
        for (int z = 0; z < cantRecursosDisponibles; z++)
            if (strcmp(reqNombres[r], pRecursosNombres[z]) == 0) { disp = pRecursosDisponibles[z]; found = 1; break; }
        printf("%d)\n", disp);
        if (!found || reqCantidades[r] > disp) puedeCumplir = 0;
    }

    // Nueva validacion: Si al menos un producto no tiene materiales, la fabrica no puede cumplir
    for (int i = 0; i < cantidadProductos; i++) {
        if (pMatCount[i] == 0) {
            puedeCumplir = 0;
            break;
        }
    }

    printf("3. ");
    if (tiempoTotal > tiempoDisponible) puedeCumplir = 0;
    if (puedeCumplir)
        printf("La fabrica puede cumplir con la demanda total.\n");
    else
        printf("La fabrica NO puede cumplir con la demanda total.\n");

    // Evaluacion de cada producto individualmente
    printf("\n4. Cumplimiento de demanda por producto:\n");
    for (int i = 0; i < cantidadProductos; i++) {
        int puede = 1;

        // Validacion de existencia de materiales
        if (pMatCount[i] == 0) {
            printf("   - %s: NO puede cumplir | Razon: No tiene materiales registrados.\n", pNombres[i]);
            continue;
        }

        int tiempoNecesario = pDemandas[i] * pTiemposProduccion[i];
        if (tiempoNecesario > tiempoDisponible) puede = 0;

        for (int m = 0; m < pMatCount[i]; m++) {
            int req = pDemandas[i] * pMatCants[i][m];
            int disp = 0, found = 0;
            for (int z = 0; z < cantRecursosDisponibles; z++)
                if (strcmp(pMatNombres[i][m], pRecursosNombres[z]) == 0) { disp = pRecursosDisponibles[z]; found = 1; break; }

            if (!found) {
                printf("   - %s: NO puede cumplir | Razon: Falta el material %s.\n", pNombres[i], pMatNombres[i][m]);
                puede = 0;
            } else if (req > disp) {
                printf("   - %s: NO puede cumplir | Razon: Insuficiente cantidad de %s.\n", pNombres[i], pMatNombres[i][m]);
                puede = 0;
            }
        }

        if (puede) {
            printf("   - %s: SI puede cumplir | Tiempo requerido: %d\n", pNombres[i], tiempoNecesario);

            // 🔹 Ahora el stock de materiales se reduce después de la producción
            for (int m = 0; m < pMatCount[i]; m++) {
                int req = pDemandas[i] * pMatCants[i][m];
                for (int z = 0; z < cantRecursosDisponibles; z++) {
                    if (strcmp(pMatNombres[i][m], pRecursosNombres[z]) == 0) {
                        pRecursosDisponibles[z] -= req;  // 🔹 Se descuenta el stock de materiales usados
                        break;
                    }
                }
            }
        }
    }

    // 🔹 Restablecimiento de stock con el mensaje original
    int subop;
    printf("\n5. ¿Desea reabastecer recursos? (1: SI, 2: NO): ");
    subop = leeropc();
    int opRec = 0;
    if (subop == 1) {
        do {
            printf("\n--- Reabastecimiento de recursos en fabrica ---\n");
            printf("1. Reabastecer recurso existente\n2. Ver recursos\n3. Volver\nSeleccione una opcion: ");
            opRec = leeropc();
            if (opRec == 1) {
                if (cantRecursosDisponibles == 0) {
                    printf("No hay recursos para reabastecer.\n");
                    continue;
                }
                char nombreRecurso[50];
                printf("Ingrese el nombre del recurso a reabastecer: ");
                fflush(stdin);
                fgets(nombreRecurso, 50, stdin);
                lens(nombreRecurso);
                int idx = -1;
                for (int i = 0; i < cantRecursosDisponibles; i++)
                    if (strcmp(pRecursosNombres[i], nombreRecurso) == 0) { idx = i; break; }
                if (idx == -1) {
                    printf("Recurso no encontrado. Solo puede reabastecer recursos globales existentes.\n");
                } else {
                    printf("Ingrese la cantidad a agregar al stock: ");
                    int cantidad = validarEnteroPositivo();
                    pRecursosDisponibles[idx] += cantidad;
                    printf("Stock actualizado. Nuevo total de %s: %d\n", pRecursosNombres[idx], pRecursosDisponibles[idx]);
                }
            } else if (opRec == 2) {
                printf("\nRecursos disponibles:\n");
                for (int i = 0; i < cantRecursosDisponibles; i++)
                    printf("  - %s: %d\n", pRecursosNombres[i], pRecursosDisponibles[i]);
            }
        } while (opRec != 3);
    } else {
        printf("No se reabasteceran recursos.\n");
    }

    break;
}

        case 8:
            if (cantidadProductos == 0)
            {
                printf("No hay productos registrados.\n");
                break;
            }
            for (int i = 0; i < cantidadProductos; i++)
            {
                printf("\nProducto: %s\nDemanda: %d\nTiempo por unidad: %d\nMateriales:\n",
                       pNombres[i], pDemandas[i], pTiemposProduccion[i]);
                if (pMatCount[i] == 0)
                    printf("  (Sin materiales)\n");
                else
                    for (int m = 0; m < pMatCount[i]; m++)
                        printf("  - %s: %d\n", pMatNombres[i][m], pMatCants[i][m]);
            }
            break;
        case 9:
            printf("Saliendo del programa.\n");
            break;
        default:
            printf("Opcion no valida.\n");
        }
    } while (opcion != 9);

    return 0;
}
