#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rashunal.h"
#include "rashunal_util.h"
#include "rmatrix.h"

struct RMatrix {
    size_t height;
    size_t width;
    Rashunal **data;
};

typedef struct IntPair {
    int first;
    int second;
} IntPair;

RMatrix* new_RMatrix(const size_t height, const size_t width, Rashunal * const *data)
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
    const size_t total = height * width;

    matrix->data = malloc(sizeof(Rashunal *) * total);
    if (!matrix->data) {
        free(matrix);
        return NULL;
    }

    for (size_t i = 0; i < total; ++i) {
        matrix->data[i] = nr_Rashunal(data[i]);
        if (!matrix->data[i]) {
            for (size_t j = 0; j < i; ++j) {
                free(matrix->data[j]);
            }
            free(matrix->data);
            free(matrix);
            return NULL;
        }
    }

    return matrix;
}

RMatrix *new_copy_RMatrix(const RMatrix *matrix)
{
    return new_RMatrix(matrix->height, matrix->width, matrix->data);
}

RMatrix *new_identity_RMatrix(const size_t size)
{
    if (size < 1) {
        errno = EINVAL;
        return NULL;
    }

    RMatrix *matrix = malloc(sizeof(RMatrix));
    if (!matrix) {
        return NULL;
    }

    matrix->height = size;
    matrix->width = size;
    const size_t total = size * size;

    matrix->data = malloc(sizeof(Rashunal *) * total);
    if (!matrix->data) {
        free(matrix);
        return NULL;
    }

    for (size_t i = 0; i < total; ++i) {
        const size_t row = i / size;
        const size_t col = i % size;
        matrix->data[i] = row == col
            ? ni_Rashunal(1)
            : ni_Rashunal(0);
        if (!matrix->data[i]) {
            for (size_t j = 0; j < i; ++j) {
                free(matrix->data[j]);
            }
            free(matrix->data);
            free(matrix);
            return NULL;
        }
    }

    return matrix;
}

RMatrix *new_permutation_RMatrix(const size_t size, const size_t r1, const size_t r2)
{
    if (r1 < 1 || r1 > size || r2 < 1 || r2 > size) {
        errno = EINVAL;
        return NULL;
    }
    RMatrix *i = new_identity_RMatrix(size);
    RMatrix *p = RMatrix_row_swap(i, r1, r2);
    free_RMatrix(i);
    return p;
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

RMatrix *RMatrix_add(const RMatrix *m, const RMatrix *n)
{
    if (m->height != n->height || m->width != n->width) {
        errno = EINVAL;
        return NULL;
    }

    RMatrix *r = malloc(sizeof(RMatrix));
    if (!r) {
        return NULL;
    }

    r->height = m->height;
    r->width = m->width;
    const size_t total = m->height * m->width;

    r->data = malloc(sizeof(Rashunal *) * total);
    if (!r->data) {
        free(r);
        return NULL;
    }

    for (size_t i = 0; i < total; ++i) {
        r->data[i] = r_add(m->data[i], n->data[i]);
        if (!r->data[i]) {
            for (size_t j = 0; j < i; ++j) {
                free(r->data[j]);
            }
            free(r->data);
            free(r);
            return NULL;
        }
    }

    return r;
}

RMatrix *RMatrix_mul(const RMatrix *m, const RMatrix *n)
{
    if (m->width != n->height) {
        errno = EINVAL;
        return NULL;
    }

    RMatrix *r = malloc(sizeof(RMatrix));
    if (!r) {
        return NULL;
    }

    r->height = m->height;
    r->width = n->width;
    const size_t total = r->height * r->width;

    r->data = malloc(sizeof(Rashunal *) * total);
    if (!r->data) {
        free(r);
        return NULL;
    }

    Rashunal *s, *p, *new_s = NULL;
    for (size_t i = 0; i < total; ++i) {
        const size_t left_row_index = i / r->width;
        const size_t right_col_index = i % r->width;
        s = ni_Rashunal(0);
        for (size_t j = 0; j < m->width; ++j) {
            const size_t left_index = left_row_index * m->width + j;
            const size_t right_index = right_col_index + j * n->width;
            const Rashunal *left = m->data[left_index];
            const Rashunal *right = n->data[right_index];
            p = r_mul(left, right);
            if (!p) {
                free(r);
                free(p);
                free(s);
                free(new_s);
                return NULL;
            }
            new_s = r_add(s, p);
            if (!new_s) {
                free(r);
                free(p);
                free(s);
                free(new_s);
                return NULL;
            }
            free(p);
            free(s);
            s = new_s;
        }
        r->data[i] = s;
    }

    return r;
}

RMatrix *RMatrix_transpose(const RMatrix *m)
{
    RMatrix *r = malloc(sizeof(RMatrix));
    if (!r) {
        return NULL;
    }

    r->height = m->width;
    r->width = m->height;
    const size_t total = m->height * m->width;

    r->data = malloc(sizeof(Rashunal *) * total);
    if (!r->data) {
        free(r);
        return NULL;
    }

    for (size_t i = 0; i < total; ++i) {
        size_t si = i / m->height + (i % m->height) * m->width;
        r->data[i] = nr_Rashunal(m->data[si]);
        if (!r->data[i]) {
            for (size_t j = 0; j < i; ++j) {
                free(r->data[j]);
            }
            free(r->data);
            free(r);
            return NULL;
        }
    }

    return r;
}

const Rashunal* RMatrix_get(const RMatrix *m, const size_t row, const size_t col)
{
    if (row < 1 || row > m->height || col < 1 || col > m->width)
    {
        errno = EINVAL;
        return NULL;
    }
    const Rashunal *element = m->data[(row - 1) * m->width + (col - 1)];
    return nr_Rashunal(element);
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
        2              // opening and closing brackets
      + 1              // leading space
      + (int)m->width; // trailing space after each element
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

int RMatrix_cmp(const RMatrix *a, const RMatrix *b)
{
    if (a->width != b->width || a->height != b->height) {
        return 1;
    }
    for (int i = 1; i <= a->height; ++i) {
        for (int j = 1; j <= a->width; ++j) {
            const Rashunal *ar = RMatrix_query(a, i, j);
            const Rashunal *br = RMatrix_query(b, i, j);
            const int diff = r_cmp(ar, br);
            if (diff != 0) {
                return diff;
            }
        }
    }
    return 0;
}

RMatrix *RMatrix_set(const RMatrix *m, const Rashunal *e, const size_t row, const size_t col)
{
    if (row < 1 || row > m->height || col < 1 || col > m->width || e == NULL) {
        errno = EINVAL;
        return NULL;
    }

    RMatrix *r = malloc(sizeof(RMatrix));
    if (!r) {
        return NULL;
    }

    r->height = m->height;
    r->width = m->width;
    const size_t total = m->height * m->width;

    r->data = malloc(sizeof(Rashunal *) * total);
    if (!r->data) {
        free(r);
        return NULL;
    }

    const size_t target_index = (row - 1) * m->width + (col - 1);
    for (size_t i = 0; i < total; ++i) {
        const Rashunal *ee = i == target_index ? e : m->data[i];
        r->data[i] = nr_Rashunal(ee);
        if (!r->data[i]) {
            for (size_t j = 0; j < i; ++j) {
                free(r->data[j]);
            }
            free(r->data);
            free(r);
            return NULL;
        }
    }

    return r;
}

RMatrix *RMatrix_row_mul(const RMatrix *m, const Rashunal *s, const size_t row)
{
    if (row < 1 || row > m->height || s == NULL) {
        errno = EINVAL;
        return NULL;
    }

    RMatrix *r = malloc(sizeof(RMatrix));
    if (!r) {
        return NULL;
    }

    r->height = m->height;
    r->width = m->width;
    const size_t total = m->height * m->width;

    r->data = malloc(sizeof(Rashunal *) * total);
    if (!r->data) {
        free(r);
        return NULL;
    }

    const size_t min_target_index = (row - 1) * m->width;
    const size_t max_target_index = row * m->width;
    for (size_t i = 0; i < total; ++i) {
        Rashunal *ee;
        if (i >= min_target_index && i < max_target_index) {
            ee = r_mul(m->data[i], s);
        } else {
            ee = nr_Rashunal(m->data[i]);
        }
        r->data[i] = ee;
        if (!r->data[i]) {
            for (size_t j = 0; j < i; ++j) {
                free(r->data[j]);
            }
            free(r->data);
            free(r);
            return NULL;
        }
    }

    return r;
}

RMatrix *RMatrix_row_swap(const RMatrix *m, const size_t row1, const size_t row2)
{
    if (row1 < 1 || row1 > m->height || row2 < 1 || row2 > m->height) {
        errno = EINVAL;
        return NULL;
    }

    RMatrix *r = malloc(sizeof(RMatrix));
    if (!r) {
        return NULL;
    }

    r->height = m->height;
    r->width = m->width;
    const size_t total = m->height * m->width;

    r->data = malloc(sizeof(Rashunal *) * total);
    if (!r->data) {
        free(r);
        return NULL;
    }

    const size_t min_target_index_1 = (row1 - 1) * m->width;
    const size_t max_target_index_1 = row1 * m->width;
    const size_t min_target_index_2 = (row2 - 1) * m->width;
    const size_t max_target_index_2 = row2 * m->width;
    size_t an_index;
    for (size_t i = 0; i < total; ++i) {
        if (i >= min_target_index_1 && i < max_target_index_1) {
            an_index = min_target_index_2 + i % m->width;
        } else if (i >= min_target_index_2 && i < max_target_index_2) {
            an_index = min_target_index_1 + i % m->width;
        } else {
            an_index = i;
        }
        r->data[i] = nr_Rashunal(m->data[an_index]);
        if (!r->data[i]) {
            for (size_t j = 0; j < i; ++j) {
                free(r->data[j]);
            }
            free(r->data);
            free(r);
            return NULL;
        }
    }

    return r;
}

RMatrix *RMatrix_lc(const RMatrix *m, const Rashunal *scale, const size_t source_row, const size_t dest_row)
{
    if (source_row < 1 || source_row > m->height || dest_row < 1 || dest_row > m->height) {
        errno = EINVAL;
        return NULL;
    }

    RMatrix *r = malloc(sizeof(RMatrix));
    if (!r) {
        return NULL;
    }

    r->height = m->height;
    r->width = m->width;
    const size_t total = m->height * m->width;

    r->data = malloc(sizeof(Rashunal *) * total);
    if (!r->data) {
        free(r);
        return NULL;
    }

    const size_t min_target_index = (dest_row - 1) * m->width;
    const size_t max_target_index = dest_row * m->width;
    size_t src_index;
    Rashunal *e = NULL, *p = NULL;
    for (size_t i = 0; i < total; ++i) {
        if (i < min_target_index || i >= max_target_index) {
            r->data[i] = nr_Rashunal(m->data[i]);
        } else {
            src_index = (source_row - 1) * m->width + (i % m->width);
            p = r_mul(m->data[src_index], scale);
            e = r_add(m->data[i], p);
            r->data[i] = nr_Rashunal(e);
            free(p);
            free(e);
        }
        if (!r->data[i]) {
            for (size_t j = 0; j < i; ++j) {
                free(r->data[j]);
            }
            free(r->data);
            free(r);
            return NULL;
        }
    }

    return r;
}

Gauss_Factorization *RMatrix_gelim(const RMatrix *m)
{
    Gauss_Factorization *r = malloc(sizeof(Gauss_Factorization));
    if (!r) {
        return NULL;
    }

    RMatrix *u = new_copy_RMatrix(m);
    RMatrix *p = new_identity_RMatrix(m->height);
    RMatrix *l = new_identity_RMatrix(m->height);
    RMatrix *d;
    RMatrix *old_u = NULL, *old_p = NULL, *old_l = NULL, *old_d = NULL;

    const Rashunal *NEGATIVE_ONE = ni_Rashunal(-1);

    for (size_t i = 1, j = 1; i <= m->height - 1 && j <= m->width - 1; ) {
        if (RMatrix_query(u, i, j)->numerator == 0) {
            for (size_t k = i + 1; k <= m->height; ++k) {
                if (RMatrix_query(u, k, j)->numerator != 0) {
                    old_u = u;
                    old_p = p;
                    RMatrix *pp = new_permutation_RMatrix(m->height, i, k);
                    u = RMatrix_row_swap(old_u, i, k);
                    p = RMatrix_mul(pp, old_p);
                    free_RMatrix(old_u);
                    free_RMatrix(old_p);
                    free_RMatrix(pp);
                    break;
                }
            }
        }
        if (RMatrix_query(u, i, j)->numerator == 0) {
            ++j;
            continue;
        }
        for (size_t k = i + 1; k <= m->height; ++k) {
            const Rashunal *pivot = RMatrix_query(u, i, j);
            const Rashunal *el = RMatrix_query(u, k, j);
            Rashunal *factor = r_div(el, pivot);
            Rashunal *multiplier = r_mul(factor, NEGATIVE_ONE);
            old_l = l;
            old_u = u;
            l = RMatrix_set(old_l, factor, k, i);
            u = RMatrix_lc(old_u, multiplier, i, k);
            free(factor);
            free(multiplier);
            free_RMatrix(old_l);
            free_RMatrix(old_u);
        }
        ++i;
        ++j;
    }

    int m_is_singular = 0;
    for (size_t i = 1; i <= m->height; ++i) {
        Rashunal *el = RMatrix_query(u, i, i);
        if (el->numerator == 0) {
            m_is_singular = 1;
            d = NULL;
            break;
        }
    }

    if (m_is_singular == 0) {
        d = new_identity_RMatrix(m->height);
        for (size_t i = 1; i <= m->height; ++i) {
            Rashunal *factor = RMatrix_query(u, i, i);
            Rashunal *inv = r_inv(factor);
            old_d = d;
            old_u = u;
            d = RMatrix_set(old_d, factor, i, i);
            u = RMatrix_row_mul(old_u, inv, i);
            free(inv);
            free_RMatrix(old_d);
            free_RMatrix(old_u);
        }
    }


    r->pi = RMatrix_transpose(p);
    r->l = l;
    r->d = d;
    r->u = u;

    free((Rashunal *)NEGATIVE_ONE);
    free_RMatrix(p);

    return r;
}