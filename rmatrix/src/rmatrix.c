#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rashunal.h"
#include "rashunal_util.h"
#include "rmatrix.h"

struct RMatrix {
    int height;
    int width;
    Rashunal **data;
};

typedef struct IntPair {
    int first;
    int second;
} IntPair;

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
    free(m->data);
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

static Rashunal* RMatrix_query(const RMatrix *m, const size_t row, const size_t col) {
    if (row < 1 || row > m->height || col < 1 || col > m->width) {
        errno = EINVAL;
        return NULL;
    }
    return m->data[(row - 1) * m->width + (col - 1)];
}

char** RMatrix_to_string_array(const RMatrix *m)
{
    IntPair **widths = malloc(sizeof(IntPair *) * m->width);
    for (int j = 1; j <= m->width; ++j) {
        widths[j - 1] = malloc(sizeof(IntPair));
        widths[j - 1]->first = -1;
        widths[j - 1]->second = -1;
        for (int i = 1; i <= m->height; ++i) {
            const Rashunal *r = RMatrix_query(m, i, j);
            const int n_width = count_digits(r->numerator);
            const int d_width = r->denominator == 1 ? 0 : count_digits(r->denominator);
            widths[j - 1]->first = n_width > widths[j - 1]->first ? n_width : widths[j - 1]->first;
            widths[j - 1]->second = d_width > widths[j - 1]->second ? d_width : widths[j - 1]->second;
        }
    }

    int line_width = \
        2         // opening and closing brackets
      + 1         // leading space
      + m->width; // trailing space after each element
    for (int i = 0; i < m->width; ++i) {
        line_width += widths[i]->first;
        if (widths[i]->second > 0) {    // denominator is not 1
            line_width += widths[i]->second \
                + 3;                    // division symbol and spaces
        }
    }

    char *buf = malloc(sizeof(char) * line_width);
    char *format_string = malloc(sizeof(char) * line_width);

    char** res = malloc(sizeof(const char*) * m->height);
    for (int i = 0; i < m->height; ++i) {
        res[i] = malloc(sizeof(char) * line_width + 1);
        strcpy(res[i], "[ ");
        for (int j = 0; j < m->width; ++j) {
            const Rashunal *r = RMatrix_query(m, i + 1, j + 1);
            sprintf(format_string, "%%%dd", widths[j]->first);
            sprintf(buf, format_string, r->numerator);
            strcat(res[i], buf);
            if (widths[j]->second > 0) {
                if (r->denominator > 1) {
                    sprintf(format_string, " / %%-%dd", widths[j]->second);
                    sprintf(buf, format_string, r->denominator);
                    strcat(res[i], buf);
                } else {
                    sprintf(format_string, "%%%dc", widths[j]->second + 3);
                    sprintf(buf, format_string, ' ');
                    strcat(res[i], buf);
                }
            }
            strcat(res[i], " ");
        }
        strcat(res[i], "]");
    }

    for (int i = 0; i < m->width; ++i) {
        free(widths[i]);
    }
    free(widths);
    free(buf);
    free(format_string);

    return res;
}
