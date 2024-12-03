#include "../include/OrdInd.h"  
#include <string.h>

void swapIndexes(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

int partition(OrdInd *ord, int low, int high, int keyType) {
    char *pivot;
    int i = low - 1;

    // Escolhendo o pivô como o último elemento
    switch (keyType) {
        case 1: pivot = ord->records[ord->nameIndex[high]].name; break;
        case 2: pivot = ord->records[ord->idIndex[high]].id; break;
        case 3: pivot = ord->records[ord->addressIndex[high]].address; break;
        default: return -1;  // Caso o tipo de chave seja inválido
    }

    for (int j = low; j < high; j++) {
        char *current;
        switch (keyType) {
            case 1: current = ord->records[ord->nameIndex[j]].name; break;
            case 2: current = ord->records[ord->idIndex[j]].id; break;
            case 3: current = ord->records[ord->addressIndex[j]].address; break;
        }

        if (strcmp(current, pivot) < 0) {
            i++;
            switch (keyType) {
                case 1: swapIndexes(&ord->nameIndex[i], &ord->nameIndex[j]); break;
                case 2: swapIndexes(&ord->idIndex[i], &ord->idIndex[j]); break;
                case 3: swapIndexes(&ord->addressIndex[i], &ord->addressIndex[j]); break;
            }
        }
    }
    switch (keyType) {
        case 1: swapIndexes(&ord->nameIndex[i + 1], &ord->nameIndex[high]); break;
        case 2: swapIndexes(&ord->idIndex[i + 1], &ord->idIndex[high]); break;
        case 3: swapIndexes(&ord->addressIndex[i + 1], &ord->addressIndex[high]); break;
    }
    return i + 1;
}

void quickSort(OrdInd *ord, int low, int high, int keyType) {
    if (low < high) {
        int pi = partition(ord, low, high, keyType);
        quickSort(ord, low, pi - 1, keyType);
        quickSort(ord, pi + 1, high, keyType);
    }
}


void bubbleSort(OrdInd *ord, int low, int high, int keyType) {
    int i, j;
    for (i = low; i < high; i++) {
        for (j = low; j < high - i + low; j++) {
            char *current, *next;
            switch (keyType) {
                case 1:
                    current = ord->records[ord->nameIndex[j]].name;
                    next = ord->records[ord->nameIndex[j + 1]].name;
                    break;
                case 2:
                    current = ord->records[ord->idIndex[j]].id;
                    next = ord->records[ord->idIndex[j + 1]].id;
                    break;
                case 3:
                    current = ord->records[ord->addressIndex[j]].address;
                    next = ord->records[ord->addressIndex[j + 1]].address;
                    break;
            }

            if (strcmp(current, next) > 0) {
                switch (keyType) {
                    case 1:
                        swapIndexes(&ord->nameIndex[j], &ord->nameIndex[j + 1]);
                        break;
                    case 2:
                        swapIndexes(&ord->idIndex[j], &ord->idIndex[j + 1]);
                        break;
                    case 3:
                        swapIndexes(&ord->addressIndex[j], &ord->addressIndex[j + 1]);
                        break;
                }
            }
        }
    }
}

void selectionSort(OrdInd *ord, int low, int high, int keyType) {
    int i, j, min_idx;

    for (i = low; i < high; i++) {
        min_idx = i;
        for (j = i + 1; j <= high; j++) {
            char *current, *min_val;
            switch (keyType) {
                case 1:
                    current = ord->records[ord->nameIndex[j]].name;
                    min_val = ord->records[ord->nameIndex[min_idx]].name;
                    break;
                case 2:
                    current = ord->records[ord->idIndex[j]].id;
                    min_val = ord->records[ord->idIndex[min_idx]].id;
                    break;
                case 3:
                    current = ord->records[ord->addressIndex[j]].address;
                    min_val = ord->records[ord->addressIndex[min_idx]].address;
                    break;
            }

            if (strcmp(current, min_val) < 0) {
                min_idx = j;
            }
        }
        // Swap the found minimum element with the first element
        switch (keyType) {
            case 1:
                swapIndexes(&ord->nameIndex[min_idx], &ord->nameIndex[i]);
                break;
            case 2:
                swapIndexes(&ord->idIndex[min_idx], &ord->idIndex[i]);
                break;
            case 3:
                swapIndexes(&ord->addressIndex[min_idx], &ord->addressIndex[i]);
                break;
        }
    }
}
