#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rashunal.h"
#include "rmatrix.h"

#define BUF_SIZE 81

int main(int argc, char *argv[])
{
    char buf[BUF_SIZE];

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

    FILE *fptr;
    if (argc > 1) {
        fptr = fopen(argv[1], "r");
    } else {
        fptr = stdin;
    }

    Rashunal *read_data[BUF_SIZE];
    size_t height = 0;
    size_t width = 0;
    int i = 0;
    int numerator, denominator;
    char *token, *slash;
    while (fgets(buf, sizeof(buf), fptr)) {
        ++height;
        width = 0;
        token = strtok(buf, " ");
        while (token != NULL) {
            slash = strchr(token, '/');
            if (slash == NULL) {
                denominator = 1;
            } else {
                *slash = '\0';
                denominator = atoi(slash + 1);
            }
            numerator = atoi(token);
            read_data[i] = n_Rashunal(numerator, denominator);
            ++i;
            ++width;
            token = strtok(NULL, " ");
        }
    }
    printf("Height is %lu\n", height);
    printf("Width is %lu\n", width);
    RMatrix *m2 = new_RMatrix(height, width, read_data);
    Gauss_Factorization *f = RMatrix_gelim(m2);
    char **read_as_string;
    read_as_string = RMatrix_to_string_array(f->l);
    printf("L:\n");
    for (size_t i = 0; i < RMatrix_height(f->l); ++i) {
        printf("%s\n", read_as_string[i]);
    }
    for (size_t i = 0; i < RMatrix_height(f->l); ++i) {
        free(read_as_string[i]);
    }
    free(read_as_string);

    read_as_string = RMatrix_to_string_array(f->u);
    printf("U:\n");
    for (size_t i = 0; i < RMatrix_height(f->u); ++i) {
        printf("%s\n", read_as_string[i]);
    }
    for (size_t i = 0; i < RMatrix_height(f->u); ++i) {
        free(read_as_string[i]);
    }

    free_RMatrix(m);
    for (int i = 0; i < 2; ++i) {
        free(as_string[i]);
    }
    free(as_string);

    for (int i = 0; i < RMatrix_height(m2) * RMatrix_width(m2); ++i) {
        free(read_data[i]);
    }
    free_RMatrix(m2);
    free(read_as_string);
    free_RMatrix(f->pi);
    free_RMatrix(f->l);
    free_RMatrix(f->d);
    free_RMatrix(f->u);
    free(f);

    return 0;
}