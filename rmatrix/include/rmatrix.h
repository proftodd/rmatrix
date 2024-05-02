#ifndef RMATRIX
#define RMATRIX

#include "rashunal.h"

typedef struct RMatrix
{
    const int height;
    const int width;
    const Rashunal **data;
} RMatrix;

RMatrix* new_RMatrix(int height, int width);
void free_RMatrix(RMatrix *m);

#endif
