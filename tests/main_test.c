#include "../include/OrdInd.h"
#include "../include/sort_algorithms.h"
#include <stdio.h>

int main()
{
    OrdInd *ord = createOrdInd(1000); // Supondo que temos 1000 registros
    if (!loadFromFile(ord, "../tests/cad.r1000.p1000.xcsv"))
    {
        printf("Falha ao carregar dados\n");
    }
    else
    {
        printf("Dados carregados com sucesso\n");

        // Criando índice para ordenação por nome
        createIndex(ord, 1); // Assumindo que 1 representa o índice por nome
        // Ordena o indice usando quick sort
        //quickSort(ord, 0, ord->size - 1, 1);
        //bubbleSort(ord, 0, ord->size - 1, 1);
        selectionSort(ord, 0, ord->size - 1, 1);
        // Imprimir os primeiros 10 registros ordenados pelo nome para verificação
        printf("Primeiros 10 registros ordenados por nome:\n");
        for (int i = 0; i < 10; i++)
        {
            int idx = ord->nameIndex[i];
            printf("Nome: %s, ID: %s, Endereço: %s \n", 
                   ord->records[idx].name, ord->records[idx].id, ord->records[idx].address);
        }

        
        printf("===========================================================================\n");

        // Criando índice para ordenação por nome
        createIndex(ord, 2); // Assumindo que 1 representa o índice por id
        // Ordena o indice usando quick sort
        //quickSort(ord, 0, ord->size - 1, 2);
        //bubbleSort(ord, 0, ord->size - 1, 2);
        selectionSort(ord, 0, ord->size - 1, 2);
        // Imprimir os primeiros 10 registros ordenados pelo nome para verificação
        printf("Primeiros 10 registros ordenados por ID:\n");
        for (int i = 0; i < 10; i++)
        {
            int idx = ord->idIndex[i];
            printf("Nome: %s, ID: %s, Endereço: %s \n", 
                   ord->records[idx].name, ord->records[idx].id, ord->records[idx].address);
        }

        
        printf("===========================================================================\n");

        // Criando índice para ordenação por nome
        createIndex(ord, 3); // Assumindo que 1 representa o índice por Endereço
        // Ordena o indice usando quick sort
        //quickSort(ord, 0, ord->size - 1, 3);
        //bubbleSort(ord, 0, ord->size - 1, 3);
        selectionSort(ord, 0, ord->size - 1, 3);
        // Imprimir os primeiros 10 registros ordenados pelo nome para verificação
        printf("Primeiros 10 registros ordenados por Endereço:\n");
        for (int i = 0; i < 10; i++)
        {
            int idx = ord->addressIndex[i];
            printf("Nome: %s, ID: %s, Endereço: %s \n", 
                   ord->records[idx].name, ord->records[idx].id, ord->records[idx].address);
        }



    }
    destroyOrdInd(ord);
    return 0;
}
