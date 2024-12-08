#include "../include/OrdInd.h"
#include "../include/sort_algorithms.h"
#include "../include/memlog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename.xcsv>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        perror("Erro ao abrir arquivo");
        return EXIT_FAILURE;
    }

    // O caminho para o arquivo de log dentro da pasta tests/output
    char *nomeArquivo = "../tests/output/OrdInd.out";
    if (iniciaMemLog(nomeArquivo) != 0) {
        fprintf(stderr, "Falha ao iniciar memlog\n");
        return EXIT_FAILURE;
    }

    ativaMemLog();


    char line[4096];
    int expectedColumns = 0;
    int numRecords = 0;
    char header[4096] = "";

    // Leitura de metadados
    if (fgets(line, sizeof(line), file))
    {
        expectedColumns = atoi(line); // Primeira linha: número de colunas
    }

    // Leitura e armazenamento dos nomes e tipos das colunas
    for (int i = 0; i < expectedColumns; i++)
    {
        fgets(line, sizeof(line), file);
        strcat(header, line);
    }

    // Leitura do número de registros
    if (fgets(line, sizeof(line), file))
    {
        numRecords = atoi(line);
    }

    // Criação e carregamento dos dados
    OrdInd *ord = createOrdInd(numRecords);
    if (!loadFromFile(ord, argv[1]))
    {
        fprintf(stderr, "Falha ao carregar dados de %s\n", argv[1]);
        fclose(file);
        destroyOrdInd(ord);
        return EXIT_FAILURE;
    }

    fclose(file);

    // Aplicação dos algoritmos de ordenação
    int keyTypes[3] = {1, 2, 3}; // Representando nome, ID, endereço
    void (*sortAlgorithms[3])(OrdInd *, int, int, int) = {quickSort, bubbleSort, selectionSort};

    int memoryLogFase = 0;

    for (int alg = 0; alg < 3; alg++)
    {
        for (int key = 0; key < 3; key++)
        {
            defineFaseMemLog(memoryLogFase);
            createIndex(ord, keyTypes[key]); // Cria os indices para essa ordenação
            sortAlgorithms[alg](ord, 0, ord->size - 1, keyTypes[key]);

            // Imprimir todos os registros após a ordenação
            printf("%d\n%s%d\n", expectedColumns, header, ord->size);

            for (int i = 0; i < ord->size; i++)
            {

                int idx;
                if (key == 0)
                {
                    idx = ord->nameIndex[i];
                }
                else if (key == 1)
                {
                    idx = ord->idIndex[i];
                }
                else
                {
                    idx = ord->addressIndex[i];
                }
                printf("%s,%s,%s,%s\n", ord->records[idx].name, ord->records[idx].id, ord->records[idx].address, ord->records[idx].payload);
            }
            memoryLogFase++; // Muda fase do registro de memoria
        }
    }

    destroyOrdInd(ord);
    finalizaMemLog();
    return 0;
}
