#include "../include/OrdInd.h"
#include "../include/memlog.h"
#include "../include/sort_algorithms.h"
#include <string.h>

void swapIndexes(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

int partition(OrdInd *ord, int low, int high, int keyType) {
    char *pivot;
    int i = low - 1;

    // Escolhendo o pivô como o último elemento
    switch (keyType) {
        case 1:
            pivot = ord->records[ord->nameIndex[high]].name;
            LEMEMLOG((long int)&ord->records[ord->nameIndex[high]].name, sizeof(char *), 1);
            break;
        case 2:
            pivot = ord->records[ord->idIndex[high]].id;
            LEMEMLOG((long int)&ord->records[ord->idIndex[high]].id, sizeof(char *), 2);
            break;
        case 3:
            pivot = ord->records[ord->addressIndex[high]].address;
            LEMEMLOG((long int)&ord->records[ord->addressIndex[high]].address, sizeof(char *), 3);
            break;
        default:
            return -1;  // Caso o tipo de chave seja inválido
    }

    for (int j = low; j < high; j++) {
        char *current;
        switch (keyType) {
            case 1:
                current = ord->records[ord->nameIndex[j]].name;
                LEMEMLOG((long int)&ord->records[ord->nameIndex[j]].name, sizeof(char *), 1);
                break;
            case 2:
                current = ord->records[ord->idIndex[j]].id;
                LEMEMLOG((long int)&ord->records[ord->idIndex[j]].id, sizeof(char *), 2);
                break;
            case 3:
                current = ord->records[ord->addressIndex[j]].address;
                LEMEMLOG((long int)&ord->records[ord->addressIndex[j]].address, sizeof(char *), 3);
                break;
        }

        if (strcmp(current, pivot) < 0) {
            i++;
            switch (keyType) {
                case 1:
                    swapIndexes(&ord->nameIndex[i], &ord->nameIndex[j]);
                    ESCREVEMEMLOG((long int)&ord->nameIndex[i], sizeof(int), 1);
                    ESCREVEMEMLOG((long int)&ord->nameIndex[j], sizeof(int), 1);
                    break;
                case 2:
                    swapIndexes(&ord->idIndex[i], &ord->idIndex[j]);
                    ESCREVEMEMLOG((long int)&ord->idIndex[i], sizeof(int), 2);
                    ESCREVEMEMLOG((long int)&ord->idIndex[j], sizeof(int), 2);
                    break;
                case 3:
                    swapIndexes(&ord->addressIndex[i], &ord->addressIndex[j]);
                    ESCREVEMEMLOG((long int)&ord->addressIndex[i], sizeof(int), 3);
                    ESCREVEMEMLOG((long int)&ord->addressIndex[j], sizeof(int), 3);
                    break;
            }
        }
    }
    switch (keyType) {
        case 1:
            swapIndexes(&ord->nameIndex[i + 1], &ord->nameIndex[high]);
            ESCREVEMEMLOG((long int)&ord->nameIndex[i + 1], sizeof(int), 1);
            ESCREVEMEMLOG((long int)&ord->nameIndex[high], sizeof(int), 1);
            break;
        case 2:
            swapIndexes(&ord->idIndex[i + 1], &ord->idIndex[high]);
            ESCREVEMEMLOG((long int)&ord->idIndex[i + 1], sizeof(int), 2);
            ESCREVEMEMLOG((long int)&ord->idIndex[high], sizeof(int), 2);
            break;
        case 3:
            swapIndexes(&ord->addressIndex[i + 1], &ord->addressIndex[high]);
            ESCREVEMEMLOG((long int)&ord->addressIndex[i + 1], sizeof(int), 3);
            ESCREVEMEMLOG((long int)&ord->addressIndex[high], sizeof(int), 3);
            break;
    }
    return i + 1;
}


void quickSort(OrdInd *ord, int low, int high, int keyType)
{
    if (low < high)
    {
        int pi = partition(ord, low, high, keyType);
        quickSort(ord, low, pi - 1, keyType);
        quickSort(ord, pi + 1, high, keyType);
    }
}

void bubbleSort(OrdInd *ord, int low, int high, int keyType)
{
    int i, j;
    for (i = low; i < high; i++)
    {
        for (j = low; j < high - i + low; j++)
        {
            char *current, *next;
            switch (keyType)
            {
            case 1:
                current = ord->records[ord->nameIndex[j]].name;
                next = ord->records[ord->nameIndex[j + 1]].name;
                LEMEMLOG((long int)&ord->records[ord->nameIndex[j]].name, sizeof(char*), 1);
                LEMEMLOG((long int)&ord->records[ord->nameIndex[j + 1]].name, sizeof(char*), 1);
                break;
            case 2:
                current = ord->records[ord->idIndex[j]].id;
                next = ord->records[ord->idIndex[j + 1]].id;
                LEMEMLOG((long int)&ord->records[ord->idIndex[j]].id, sizeof(char*), 2);
                LEMEMLOG((long int)&ord->records[ord->idIndex[j + 1]].id, sizeof(char*), 2);
                break;
            case 3:
                current = ord->records[ord->addressIndex[j]].address;
                next = ord->records[ord->addressIndex[j + 1]].address;
                LEMEMLOG((long int)&ord->records[ord->addressIndex[j]].address, sizeof(char*), 3);
                LEMEMLOG((long int)&ord->records[ord->addressIndex[j + 1]].address, sizeof(char*), 3);
                break;
            }

            if (strcmp(current, next) > 0)
            {
                switch (keyType)
                {
                case 1:
                    swapIndexes(&ord->nameIndex[j], &ord->nameIndex[j + 1]);
                    ESCREVEMEMLOG((long int)&ord->nameIndex[j], sizeof(int), 1);
                    ESCREVEMEMLOG((long int)&ord->nameIndex[j + 1], sizeof(int), 1);
                    break;
                case 2:
                    swapIndexes(&ord->idIndex[j], &ord->idIndex[j + 1]);
                    ESCREVEMEMLOG((long int)&ord->idIndex[j], sizeof(int), 2);
                    ESCREVEMEMLOG((long int)&ord->idIndex[j + 1], sizeof(int), 2);
                    break;
                case 3:
                    swapIndexes(&ord->addressIndex[j], &ord->addressIndex[j + 1]);
                    ESCREVEMEMLOG((long int)&ord->addressIndex[j], sizeof(int), 3);
                    ESCREVEMEMLOG((long int)&ord->addressIndex[j + 1], sizeof(int), 3);
                    break;
                }
            }
        }
    }
}


void selectionSort(OrdInd *ord, int low, int high, int keyType)
{
    int i, j, min_idx;

    for (i = low; i < high; i++)
    {
        min_idx = i;
        for (j = i + 1; j <= high; j++)
        {
            char *current, *min_val;
            switch (keyType)
            {
            case 1:
                current = ord->records[ord->nameIndex[j]].name;
                min_val = ord->records[ord->nameIndex[min_idx]].name;
                LEMEMLOG((long int)&ord->records[ord->nameIndex[j]].name, sizeof(char*), 1);
                LEMEMLOG((long int)&ord->records[ord->nameIndex[min_idx]].name, sizeof(char*), 1);
                break;
            case 2:
                current = ord->records[ord->idIndex[j]].id;
                min_val = ord->records[ord->idIndex[min_idx]].id;
                LEMEMLOG((long int)&ord->records[ord->idIndex[j]].id, sizeof(char*), 2);
                LEMEMLOG((long int)&ord->records[ord->idIndex[min_idx]].id, sizeof(char*), 2);
                break;
            case 3:
                current = ord->records[ord->addressIndex[j]].address;
                min_val = ord->records[ord->addressIndex[min_idx]].address;
                LEMEMLOG((long int)&ord->records[ord->addressIndex[j]].address, sizeof(char*), 3);
                LEMEMLOG((long int)&ord->records[ord->addressIndex[min_idx]].address, sizeof(char*), 3);
                break;
            }

            if (strcmp(current, min_val) < 0)
            {
                min_idx = j;
            }
        }
        // Swap the found minimum element with the first element
        switch (keyType)
        {
        case 1:
            swapIndexes(&ord->nameIndex[min_idx], &ord->nameIndex[i]);
            ESCREVEMEMLOG((long int)&ord->nameIndex[min_idx], sizeof(int), 1);
            ESCREVEMEMLOG((long int)&ord->nameIndex[i], sizeof(int), 1);
            break;
        case 2:
            swapIndexes(&ord->idIndex[min_idx], &ord->idIndex[i]);
            ESCREVEMEMLOG((long int)&ord->idIndex[min_idx], sizeof(int), 2);
            ESCREVEMEMLOG((long int)&ord->idIndex[i], sizeof(int), 2);
            break;
        case 3:
            swapIndexes(&ord->addressIndex[min_idx], &ord->addressIndex[i]);
            ESCREVEMEMLOG((long int)&ord->addressIndex[min_idx], sizeof(int), 3);
            ESCREVEMEMLOG((long int)&ord->addressIndex[i], sizeof(int), 3);
            break;
        }
    }
}
