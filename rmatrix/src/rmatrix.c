#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "rashunal.h"
#include "rmatrix.h"

struct RMatrix {
    int height;
    int width;
    Rashunal **data;
};

RMatrix* new_RMatrix(const size_t height, const size_t width, const Rashunal **data)
{
    if (height < 1 || width < 1) {
        errno = EINVAL;
        return NULL;
    }

    RMatrix *matrix = malloc(sizeof(RMatrix));
    if (!matrix) {
        return NULL;
    }

    matrix->height = height;
    matrix->width = width;
    size_t total = height * width;

    matrix->data = malloc(sizeof(Rashunal *) * total);
    if (!matrix->data) {
        free(matrix);
        return NULL;
    }

    for (size_t i = 0; i < total; ++i) {
        matrix->data[i] = n_Rashunal(data[i]->numerator, data[i]->denominator);
        if (!matrix->data[i]) {
            for (size_t j = 0; j < i; ++j) {
                free(matrix->data[j]);
            }
            return NULL;
        }
    }

    return matrix;
}

void free_RMatrix(RMatrix *m)
{
    for (size_t i = 0; i < m->height * m->width; ++i) {
        free(m->data[i]);
    }
    free(m);
}

size_t RMatrix_height(const RMatrix *m)
{
    return m ? m->height : 0;
}

size_t RMatrix_width(const RMatrix *m)
{
    return m ? m->width : 0;
}

const Rashunal* RMatrix_get(const RMatrix *m, const size_t row, const size_t col)
{
    if (row < 1 || row > m->height || col < 1 || col > m->width)
    {
        errno = EINVAL;
        return NULL;
    }
    const Rashunal *element = m->data[(row - 1) * m->width + (col - 1)];
    return n_Rashunal(element->numerator, element->denominator);
}
