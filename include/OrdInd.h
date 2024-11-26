#ifndef ORDIND_H
#define ORDIND_H

// Estrutura para representar um registro de dados
typedef struct
{
    char *name;
    char *id;
    char *address;
    char *payload; // Essa pode ser uma string longa ou qualquer tipo de dados necessário
} Record;

// Estrutura para a ordenação indireta
typedef struct
{
    Record *records;   // Array de registros
    int *nameIndex;    // Índice para ordenação por nome
    int *idIndex;      // Índice para ordenação por ID
    int *addressIndex; // Índice para ordenação por endereço
    int size;          // Tamanho do array de registros
} OrdInd;

// Funções para manipulação do TAD OrdInd
OrdInd *createOrdInd(int size);
void destroyOrdInd(OrdInd *ord);
int loadFromFile(OrdInd *ord, const char *filename);
void sortBy(OrdInd *ord, int *index);
void printSorted(OrdInd *ord, int *index);
int loadFromFile(OrdInd *ord, const char *filename);

#endif
