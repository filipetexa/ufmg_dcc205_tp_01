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

#include "OrdInd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int loadFromFile(OrdInd *ord, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Erro ao abrir arquivo");
        return 0;
    }

    char line[1024]; // Buffer para ler cada linha
    int index = 0;

    // Pular as linhas de cabeçalho
    for (int i = 0; i < 5; i++)
    {
        if (!fgets(line, sizeof(line), file))
        {
            fprintf(stderr, "Falha ao ler as linhas de cabeçalho\n");
            fclose(file);
            return 0;
        }
    }

    // Ler e processar cada registro
    while (fgets(line, sizeof(line), file) && index < ord->size)
    {
        line[strcspn(line, "\n")] = 0; // Remover a nova linha no final

        // Tokenizar a linha com base em vírgulas
        char *name = strtok(line, ",");
        char *id = strtok(NULL, ",");
        char *address = strtok(NULL, ",");
        char *payload = strtok(NULL, "");

        if (!name || !id || !address || !payload)
        {
            fprintf(stderr, "Dados incompletos na linha %d\n", index + 1);
            continue; // Pula esta iteração se os dados estão incompletos
        }

        // Alocação de memória e cópia dos dados
        ord->records[index].name = strdup(name);
        ord->records[index].id = strdup(id);
        ord->records[index].address = strdup(address);
        ord->records[index].payload = strdup(payload);

        index++;
    }

    fclose(file);
    return 1; // Sucesso
}
