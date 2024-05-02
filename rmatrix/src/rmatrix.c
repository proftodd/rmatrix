#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rashunal.h"
#include "rmatrix.h"

RMatrix* new_RMatrix(int height, int width)
{
    RMatrix r =
    {
        .height = height,
        .width = width,
        .data = NULL
    };
    RMatrix *result = malloc(sizeof(RMatrix));
    if (result) {
        memcpy(result, &r, sizeof(RMatrix));
        return result;
    } else {
        return NULL;
    }
}

void free_RMatrix(RMatrix *m)
{

}
