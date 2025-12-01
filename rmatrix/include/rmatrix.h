#pragma once

#ifdef _WIN32
  #ifdef RMATRIX_BUILD_DLL
    #define RMATRIX_API __declspec(dllexport)
  #else
    #define RMATRIX_API __declspec(dllimport)
  #endif
#else
  #define RMATRIX_API
#endif

#ifndef RMATRIX
#define RMATRIX

#include <stddef.h>
#include "rashunal.h"

typedef struct RMatrix RMatrix;

typedef struct Gauss_Factorization {
    const RMatrix *pi;
    const RMatrix *l;
    const RMatrix *d;
    const RMatrix *u;
} Gauss_Factorization;

RMATRIX_API RMatrix* new_RMatrix(size_t height, size_t width, Rashunal * const *data);
RMATRIX_API RMatrix* new_copy_RMatrix(const RMatrix *matrix);
RMATRIX_API RMatrix* new_identity_RMatrix(size_t size);
RMATRIX_API RMatrix* new_permutation_RMatrix(size_t size, size_t r1, size_t r2);
RMATRIX_API void free_RMatrix(RMatrix *m);

RMATRIX_API size_t RMatrix_height(const RMatrix *m);
RMATRIX_API size_t RMatrix_width(const RMatrix *m);

RMATRIX_API RMatrix *RMatrix_add(const RMatrix *m, const RMatrix *n);
RMATRIX_API RMatrix *RMatrix_mul(const RMatrix *m, const RMatrix *n);
RMATRIX_API RMatrix *RMatrix_transpose(const RMatrix *m);

RMATRIX_API const Rashunal* RMatrix_get(const RMatrix *m, size_t row, size_t col);

RMATRIX_API char** RMatrix_to_string_array(const RMatrix *m);

RMATRIX_API int RMatrix_cmp(const RMatrix *a, const RMatrix *b);

RMATRIX_API RMatrix* RMatrix_set(const RMatrix *m, const Rashunal *e, size_t row, size_t col);
RMATRIX_API RMatrix* RMatrix_row_mul(const RMatrix *m, const Rashunal *s, size_t row);
RMATRIX_API RMatrix* RMatrix_row_swap(const RMatrix *m, size_t row1, size_t row2);
RMATRIX_API RMatrix* RMatrix_lc(const RMatrix *m, const Rashunal *scale, size_t source_row, size_t dest_row);
RMATRIX_API RMatrix* RMatrix_invert(const RMatrix *m);
RMATRIX_API RMatrix* RMatrix_minor(const RMatrix *m, size_t row, size_t col);
RMATRIX_API Rashunal* RMatrix_det(const RMatrix *m);

RMATRIX_API Gauss_Factorization* RMatrix_gelim(const RMatrix *m);

#endif
