/*
Nombre: Erick Eduardo Cano Osorio
Matricula: 1279386

*/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int categoria;
    char concepto[50];
    float costo;
} Gasto;

void capturarGasto(Gasto gastos[], int *numGastos);
void ordenarPorInsercion(Gasto gastos[], int numGastos);
void ordenarPorSeleccion(Gasto gastos[], int numGastos);
void ordenarPorBurbuja(Gasto gastos[], int numGastos);
void mostrarGastos(Gasto gastos[], int numGastos, int categoria, void (*ordenamiento)(Gasto[], int));

int main() {
    Gasto *gastos = NULL;
    int numGastos = 0;
    int opcion;
    
    do {
        printf("--Menu de gastos--\n");
        printf("1. Capturar gasto\n");
        printf("2. Mostrar gasto en alimentos\n");
        printf("3. Mostrar gasto en diversi%cn\n",162);
        printf("4. Mostrar gasto en pagos fijos\n");
        printf("5. Salir\n");
        printf("Elije una opci%cn: ",162);
        scanf("%d", &opcion);
        
        switch (opcion) {
            case 1:
                gastos = (Gasto *)realloc(gastos, (numGastos + 1) * sizeof(Gasto));
                if (gastos == NULL) {
                    printf("Error al asignar memoria.\n");
                    return 1;
                }
                capturarGasto(gastos, &numGastos);
                break;
            case 2:
                mostrarGastos(gastos, numGastos, 1, ordenarPorInsercion);
                break;
            case 3:
                mostrarGastos(gastos, numGastos, 2, ordenarPorSeleccion);
                break;
            case 4:
                mostrarGastos(gastos, numGastos, 3, ordenarPorBurbuja);
                break;
            case 5:
                free(gastos);
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opción invalida.\n");
        }
    } while (opcion != 5);
    
    return 0;
}

void capturarGasto(Gasto gastos[], int *numGastos) {
    Gasto nuevoGasto;
    printf("Seleccione la categor%ca:\n",161);
    printf("1-Alimentos\n");
    printf("2-Diversi%cn\n",162);
    printf("3-Pagos fijos\n");
    printf("Categor%ca: ",161);
    scanf("%d", &nuevoGasto.categoria);
    
    /* Use esta referencia para saber como limpiar el buffer de 
       entrada para evitar problemas con las cadenas de texto
    https://stackoverflow.com/questions/7898215/how-can-i-clear-an-input-buffer-in-c
    */
    while (getchar() != '\n');

    printf("Concepto: ");
    fgets(nuevoGasto.concepto, sizeof(nuevoGasto.concepto), stdin);
    nuevoGasto.concepto[strcspn(nuevoGasto.concepto, "\n")] = '\0';  // Elimina el salto de línea

    printf("Costo: ");
    scanf("%f", &nuevoGasto.costo);
    
    gastos[*numGastos] = nuevoGasto;
    (*numGastos)++;
    
    printf("Gasto capturado con exito.\n");
}

void ordenarPorInsercion(Gasto gastos[], int numGastos) {
    for (int i = 1; i < numGastos; i++) {
        Gasto temp = gastos[i];
        int j = i - 1;
        while (j >= 0 && strcmp(temp.concepto, gastos[j].concepto) < 0) {
            gastos[j + 1] = gastos[j];
            j--;
        }
        gastos[j + 1] = temp;
    }
}

void ordenarPorSeleccion(Gasto gastos[], int numGastos) {
    for (int i = 0; i < numGastos - 1; i++) {
        int maxIndex = i;
        for (int j = i + 1; j < numGastos; j++) {
            if (strcmp(gastos[j].concepto, gastos[maxIndex].concepto) > 0) {
                maxIndex = j;
            }
        }
        Gasto temp = gastos[i];
        gastos[i] = gastos[maxIndex];
        gastos[maxIndex] = temp;
    }
}

void ordenarPorBurbuja(Gasto gastos[], int numGastos) {
    for (int i = 0; i < numGastos - 1; i++) {
        for (int j = 0; j < numGastos - i - 1; j++) {
            if (strcmp(gastos[j].concepto, gastos[j + 1].concepto) > 0) {
                Gasto temp = gastos[j];
                gastos[j] = gastos[j + 1];
                gastos[j + 1] = temp;
            }
        }
    }
}

void mostrarGastos(Gasto gastos[], int numGastos, int categoria, void (*ordenamiento)(Gasto[], int)) {
    Gasto gastosFiltrados[numGastos];
    int numGastosFiltrados = 0;
    
    for (int i = 0; i < numGastos; i++) {
        if (gastos[i].categoria == categoria) {
            gastosFiltrados[numGastosFiltrados] = gastos[i];
            numGastosFiltrados++;
        }
    }
    
    ordenamiento(gastosFiltrados, numGastosFiltrados);
    
    printf("Gastos en ");
    switch (categoria) {
        case 1:
            printf("alimentos:\n");
            break;
        case 2:
            printf("diversi%cn:\n",162);
            break;
        case 3:
            printf("pagos fijos:\n");
            break;
        default:
            printf("categor%ca desconocida:\n",161);
            break;
    }
    
    for (int i = 0; i < numGastosFiltrados; i++) {
        printf("Concepto: %s, Costo: %.2f\n", gastosFiltrados[i].concepto, gastosFiltrados[i].costo);
    }
}