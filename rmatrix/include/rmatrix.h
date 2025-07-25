#ifndef RMATRIX
#define RMATRIX

#include <stddef.h>
#include "rashunal.h"

typedef struct RMatrix RMatrix;

RMatrix* new_RMatrix(size_t height, size_t width, const Rashunal **data);
void free_RMatrix(RMatrix *m);

size_t RMatrix_height(const RMatrix *m);
size_t RMatrix_width(const RMatrix *m);
const Rashunal* RMatrix_get(const RMatrix *m, size_t row, size_t col);

#endif
