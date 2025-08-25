#include <stdio.h>
#include <stdlib.h>
#include "rashunal.h"
#include "rmatrix.h"

int main(int argc, char *argv[])
{
    Rashunal *data[6] = {
        &(Rashunal){.numerator = 1, .denominator = 1},
        &(Rashunal){.numerator = 2, .denominator = 1},
        &(Rashunal){.numerator = 3, .denominator = 1},
        &(Rashunal){.numerator = 4, .denominator = 1},
        &(Rashunal){.numerator = 5, .denominator = 1},
        &(Rashunal){.numerator = 6, .denominator = 1},
    };
    RMatrix *m = new_RMatrix(2, 3, data);
    char **as_string = RMatrix_to_string_array(m);
    for (int i = 0; i < 2; ++i) {
        printf("%s\n", as_string[i]);
    }

    free_RMatrix(m);
    for (int i = 0; i < 2; ++i) {
        free(as_string[i]);
    }
    free(as_string);

    return 0;
}