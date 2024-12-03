#ifndef SORT_ALGORITHMS_H
#define SORT_ALGORITHMS_H

#include "OrdInd.h"

void quickSort(OrdInd *ord, int low, int high, int keyType);
void selectionSort(OrdInd *ord, int low, int high, int keyType);
void bubbleSort(OrdInd *ord, int low, int high, int keyType);

#endif
