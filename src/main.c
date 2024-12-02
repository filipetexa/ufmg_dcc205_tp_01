#include "../include/OrdInd.h"
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

        // Imprimir os primeiros 10 registros ordenados pelo nome para verificação
        printf("Primeiros 10 registros ordenados por nome:\n");
        for (int i = 0; i < 10; i++)
        {
            int idx = ord->nameIndex[i];
            printf("Nome: %s, ID: %s, Endereço: %s, Payload: %s \n", 
                   ord->records[idx].name, ord->records[idx].id, ord->records[idx].address, ord->records[idx].payload);
        }
    }
    destroyOrdInd(ord);
    return 0;
}
