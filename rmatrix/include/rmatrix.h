#ifndef RMATRIX
#define RMATRIX

#include <stddef.h>
#include "rashunal.h"

typedef struct RMatrix RMatrix;

RMatrix* new_RMatrix(size_t height, size_t width, const Rashunal **data);
RMatrix* new_identity_RMatrix(size_t size);
void free_RMatrix(RMatrix *m);

size_t RMatrix_height(const RMatrix *m);
size_t RMatrix_width(const RMatrix *m);

RMatrix *RMatrix_add(const RMatrix *m, const RMatrix *n);
RMatrix *RMatrix_mul(const RMatrix *m, const RMatrix *n);
RMatrix *RMatrix_transpose(const RMatrix *m);

const Rashunal* RMatrix_get(const RMatrix *m, size_t row, size_t col);

char** RMatrix_to_string_array(const RMatrix *m);

int RMatrix_cmp(const RMatrix *a, const RMatrix *b);

RMatrix* RMatrix_set(const RMatrix *m, const Rashunal *e, size_t row, size_t col);
RMatrix* RMatrix_row_mul(const RMatrix *m, const Rashunal *s, size_t row);
RMatrix* RMatrix_row_swap(const RMatrix *m, size_t row1, size_t row2);
RMatrix* RMatrix_lc(const RMatrix *m, const Rashunal *scale, size_t source_row, size_t dest_row);

#endif
