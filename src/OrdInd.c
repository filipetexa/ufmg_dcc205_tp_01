#include "OrdInd.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Função para criar e inicializar a estrutura OrdInd
OrdInd *createOrdInd(int size)
{
    OrdInd *ord = malloc(sizeof(OrdInd));
    if (ord)
    {
        ord->size = size;
        ord->records = malloc(sizeof(Record) * size);
        ord->nameIndex = malloc(sizeof(int) * size);
        ord->idIndex = malloc(sizeof(int) * size);
        ord->addressIndex = malloc(sizeof(int) * size);
        // Inicializar os índices aqui
    }
    return ord;
}

// Função para destruir a estrutura OrdInd
void destroyOrdInd(OrdInd *ord)
{
    if (ord)
    {
        free(ord->records);
        free(ord->nameIndex);
        free(ord->idIndex);
        free(ord->addressIndex);
        free(ord);
    }
}

// Carrega linhas do arquivo
int loadFromFile(OrdInd *ord, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        return 0; // Falha ao abrir o arquivo
    }

    char line[1024]; // Buffer para ler cada linha do arquivo
    int index = 0;
    while (fgets(line, sizeof(line), file) && index < ord->size)
    {
        // Remover a nova linha no final, se houver
        line[strcspn(line, "\n")] = 0;

        // Tokenizar a linha com base em vírgulas
        char *name = strtok(line, ",");
        char *id = strtok(NULL, ",");
        char *address = strtok(NULL, ",");
        char *payload = strtok(NULL, "");

        // Alocar memória e copiar os dados para a estrutura
        ord->records[index].name = strdup(name);
        ord->records[index].id = strdup(id);
        ord->records[index].address = strdup(address);
        ord->records[index].payload = strdup(payload);

        index++;
    }

    fclose(file);
    return 1; // Sucesso
}
