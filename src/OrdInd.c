#include "OrdInd.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h> // Incluir o cabeçalho para acesso à errno

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

int loadFromFile(OrdInd *ord, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir arquivo");
        return 0;
    }

    char line[4096];
    int expectedColumns = 0;
    int index = 0;

    // Leitura de metadados
    if (fgets(line, sizeof(line), file))
    {
        expectedColumns = atoi(line); // Primeira linha: número de colunas
    }

    // Pula os nomes das colunas e o tipo (s)
    for (int i = 0; i < expectedColumns; i++)
    {
        fgets(line, sizeof(line), file);
    }

    int numRecords;
    // Leitura do número de registros
    if (fgets(line, sizeof(line), file))
    {
        numRecords = atoi(line);
    }
    else
    {
        fprintf(stderr, "Erro ao ler o número de registros\n");
        fclose(file);
        return 0;
    }

    // Processamento de registros
    while (fgets(line, sizeof(line), file) && index < numRecords)
    {
        line[strcspn(line, "\n")] = 0;
        char *token = strtok(line, ",");
        int colIndex = 0;
        while (token && colIndex < expectedColumns)
        {
            switch (colIndex)
            {
            case 0:
                ord->records[index].name = strdup(token);
                break;
            case 1:
                ord->records[index].id = strdup(token);
                break;
            case 2:
                ord->records[index].address = strdup(token);
                break;
            case 3:
                ord->records[index].payload = strdup(token);
                break;
            }
            token = strtok(NULL, ",");
            colIndex++;
        }
        index++;
    }

    fclose(file);
    return 1;
}

void createIndex(OrdInd *ord, int keyType) {
    int i;
    // int j, min_idx;
    int *index;
    // char *keyValue;

    // Escolhendo o vetor de índice apropriado
    switch (keyType) {
        case 1: // Nome
            index = ord->nameIndex;
            break;
        case 2: // ID
            index = ord->idIndex;
            break;
        case 3: // Endereço
            index = ord->addressIndex;
            break;
        default:
            printf("Invalid key type\n");
            return;
    }

    // Inicialização do índice
    for (i = 0; i < ord->size; i++) {
        index[i] = i;
    }

/*
    // Ordenação simples do índice utilizando o método Selection Sort por simplicidade
    for (i = 0; i < ord->size - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < ord->size; j++) {
            // Comparação dependente do tipo de chave
            switch (keyType) {
                case 1:
                    keyValue = ord->records[index[j]].name;
                    break;
                case 2:
                    keyValue = ord->records[index[j]].id;
                    break;
                case 3:
                    keyValue = ord->records[index[j]].address;
                    break;
            }
            if (strcmp(ord->records[index[min_idx]].name, keyValue) > 0) {
                min_idx = j;
            }
        }

        // Trocando os índices
        int temp = index[min_idx];
        index[min_idx] = index[i];
        index[i] = temp;
    }
*/

}
