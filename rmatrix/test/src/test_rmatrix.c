#include <errno.h>
#include <stdlib.h>
#include "rmatrix.h"
#include "unity.h"

void setUp(void) {

}

void test_new_RMatrix_returns_matrix()
{
    Rashunal *data[] = {
        ni_Rashunal(1),
        ni_Rashunal(2),
        ni_Rashunal(3),
        ni_Rashunal(4),
        ni_Rashunal(5),
        ni_Rashunal(6)
    };
    RMatrix *m = new_RMatrix(2, 3, data);
    TEST_ASSERT_EQUAL(2, RMatrix_height(m));
    TEST_ASSERT_EQUAL(3, RMatrix_width(m));
    for (int i = 0; i < 6; ++i) {
        free((void *)data[i]);
    }
    free_RMatrix(m);
}

void test_new_RMatrix_with_invalid_dimensions_return_void_and_sets_errno()
{
    Rashunal *data[] = {};
    RMatrix *m = new_RMatrix(2, 0, data);
    TEST_ASSERT_NULL(m);
    TEST_ASSERT_EQUAL(EINVAL, errno);
}

void test_new_identity_RMatrix_returns_identity()
{
    Rashunal *data[] = {
        ni_Rashunal(1),
        ni_Rashunal(0),
        ni_Rashunal(0),
        ni_Rashunal(0),
        ni_Rashunal(1),
        ni_Rashunal(0),
        ni_Rashunal(0),
        ni_Rashunal(0),
        ni_Rashunal(1),
    };
    RMatrix *expected = new_RMatrix(3, 3, data);

    RMatrix *actual = new_identity_RMatrix(3);

    TEST_ASSERT_TRUE(RMatrix_cmp(expected, actual) == 0);

    free_RMatrix(expected);
    free_RMatrix(actual);
    for (int i = 0; i < 9; ++i) {
        free((void *)data[i]);
    }
}

void test_RMatrix_add()
{
    Rashunal *data1[] = {
        ni_Rashunal(1),
        ni_Rashunal(2),
        ni_Rashunal(3),
        ni_Rashunal(4),
        ni_Rashunal(5),
        ni_Rashunal(6),
        ni_Rashunal(7),
        ni_Rashunal(8),
        ni_Rashunal(9),
        ni_Rashunal(0),
        ni_Rashunal(1),
        ni_Rashunal(2),
    };
    Rashunal *data2[] = {
        ni_Rashunal(1),
        ni_Rashunal(1),
        ni_Rashunal(1),
        ni_Rashunal(1),
        ni_Rashunal(2),
        ni_Rashunal(2),
        ni_Rashunal(2),
        ni_Rashunal(2),
        ni_Rashunal(3),
        ni_Rashunal(3),
        ni_Rashunal(3),
        ni_Rashunal(3),
    };
    Rashunal *data3[] = {
        ni_Rashunal(2),
        ni_Rashunal(3),
        ni_Rashunal(4),
        ni_Rashunal(5),
        ni_Rashunal(7),
        ni_Rashunal(8),
        ni_Rashunal(9),
        ni_Rashunal(10),
        ni_Rashunal(12),
        ni_Rashunal(3),
        ni_Rashunal(4),
        ni_Rashunal(5),
    };

    RMatrix *m1 = new_RMatrix(3, 4, data1);
    RMatrix *m2 = new_RMatrix(3, 4, data2);
    RMatrix *expected = new_RMatrix(3, 4, data3);

    RMatrix *actual = RMatrix_add(m1, m2);

    TEST_ASSERT_TRUE(RMatrix_cmp(expected, actual) == 0);

    free_RMatrix(m1);
    free_RMatrix(m2);
    free_RMatrix(expected);
    free_RMatrix(actual);
    for (int i = 0; i < 12; ++i) {
        free((void *)data1[i]);
        free((void *)data2[i]);
        free((void *)data3[i]);
    }
}

void test_RMatrix_transpose()
{
    Rashunal *data1[] = {
        ni_Rashunal(1),
        ni_Rashunal(2),
        ni_Rashunal(3),
        ni_Rashunal(4),
        ni_Rashunal(5),
        ni_Rashunal(6),
        ni_Rashunal(7),
        ni_Rashunal(8),
        ni_Rashunal(9),
        ni_Rashunal(0),
        ni_Rashunal(1),
        ni_Rashunal(2),
    };
    Rashunal *data2[] = {
        ni_Rashunal(1),
        ni_Rashunal(5),
        ni_Rashunal(9),
        ni_Rashunal(2),
        ni_Rashunal(6),
        ni_Rashunal(0),
        ni_Rashunal(3),
        ni_Rashunal(7),
        ni_Rashunal(1),
        ni_Rashunal(4),
        ni_Rashunal(8),
        ni_Rashunal(2),
    };
    RMatrix *m = new_RMatrix(3, 4, data1);
    RMatrix *expected = new_RMatrix(4, 3, data2);

    RMatrix *actual = RMatrix_transpose(m);

    TEST_ASSERT_TRUE(RMatrix_cmp(expected, actual) == 0);

    free_RMatrix(m);
    free_RMatrix(expected);
    free_RMatrix(actual);
    for (int i = 0; i < 12; ++i) {
        free((void *)data1[i]);
        free((void *)data2[i]);
    }
}

void test_RMatrix_mul()
{
    Rashunal *data1[] = {
        ni_Rashunal(1),
        ni_Rashunal(2),
        ni_Rashunal(3),
        ni_Rashunal(4),
        ni_Rashunal(5),
        ni_Rashunal(6),
        ni_Rashunal(7),
        ni_Rashunal(8),
        ni_Rashunal(9),
        ni_Rashunal(0),
        ni_Rashunal(1),
        ni_Rashunal(2),
    };
    Rashunal *data2[] = {
        ni_Rashunal(1),
        ni_Rashunal(2),
        ni_Rashunal(-1),
        ni_Rashunal(-2),
        ni_Rashunal(0),
        ni_Rashunal(3),
        ni_Rashunal(1),
        ni_Rashunal(0),
    };
    Rashunal *data3[] = {
        ni_Rashunal(3),
        ni_Rashunal(7),
        ni_Rashunal(7),
        ni_Rashunal(19),
        ni_Rashunal(11),
        ni_Rashunal(21),
    };

    RMatrix *m1 = new_RMatrix(3, 4, data1);
    RMatrix *m2 = new_RMatrix(4, 2, data2);
    RMatrix *expected = new_RMatrix(3, 2, data3);

    RMatrix *actual = RMatrix_mul(m1, m2);

    TEST_ASSERT_TRUE(RMatrix_cmp(expected, actual) == 0);

    free_RMatrix(m1);
    free_RMatrix(m2);
    free_RMatrix(expected);
    free_RMatrix(actual);
    for (int i = 0; i < 12; ++i) {
        free((void *)data1[i]);
    }
    for (int i = 0; i < 8; ++i) {
        free((void *)data2[i]);
    }
    for (int i = 0; i < 6; ++i) {
        free((void *)data3[i]);
    }
}

void test_RMatrix_to_string_array()
{
    Rashunal *data[] = {
        ni_Rashunal(1),
        ni_Rashunal(2),
        ni_Rashunal(3),
        ni_Rashunal(4),
        n_Rashunal(1, 2),
        n_Rashunal(10, 3),
    };
    RMatrix *m = new_RMatrix(2, 3, data);
    char** str = RMatrix_to_string_array(m);
    TEST_ASSERT_EQUAL_STRING("[ 1 2      3     ]", str[0]);
    TEST_ASSERT_EQUAL_STRING("[ 4 1 / 2 10 / 3 ]", str[1]);

    for (int i = 0; i < 6; ++i) {
        free((void *)data[i]);
    }
    free_RMatrix(m);
    for (int i = 0; i < 2; ++i) {
        free(str[i]);
    }
    free(str);
}

void test_RMatrix_cmp()
{
    Rashunal *data1[] = {
        ni_Rashunal(1),
        ni_Rashunal(2),
        ni_Rashunal(3),
        ni_Rashunal(4),
        ni_Rashunal(5),
        ni_Rashunal(6),
    };
    Rashunal *data2[] = {
        ni_Rashunal(1),
        ni_Rashunal(2),
        ni_Rashunal(3),
        ni_Rashunal(4),
        ni_Rashunal(5),
        ni_Rashunal(9),
    };
    RMatrix *m1 = new_RMatrix(2, 3, data1);
    RMatrix *m2 = new_RMatrix(3, 2, data1);
    RMatrix *m3 = new_RMatrix(2, 3, data2);
    RMatrix *m4 = new_RMatrix(2, 3, data1);

    TEST_ASSERT_TRUE(RMatrix_cmp(m1, m2) != 0);
    TEST_ASSERT_TRUE(RMatrix_cmp(m1, m3) != 0);
    TEST_ASSERT_TRUE(RMatrix_cmp(m1, m4) == 0);

    free_RMatrix(m1);
    free_RMatrix(m2);
    free_RMatrix(m3);
    free_RMatrix(m4);

    for (int i = 0; i < 6; ++i) {
        free((void *)data1[i]);
        free((void *)data2[i]);
    }
}

void test_RMatrix_set()
{
    Rashunal *data1[] = {
        ni_Rashunal(1),
        ni_Rashunal(2),
        ni_Rashunal(3),
        ni_Rashunal(4),
        ni_Rashunal(5),
        ni_Rashunal(6),
        ni_Rashunal(7),
        ni_Rashunal(8),
        ni_Rashunal(9),
        ni_Rashunal(0),
        ni_Rashunal(1),
        ni_Rashunal(2),
    };
    Rashunal *data2[] = {
        ni_Rashunal(1),
        ni_Rashunal(2),
        ni_Rashunal(3),
        ni_Rashunal(4),
        ni_Rashunal(5),
        ni_Rashunal(6),
        ni_Rashunal(7),
        ni_Rashunal(8),
        ni_Rashunal(9),
        n_Rashunal(2, 3),
        ni_Rashunal(1),
        ni_Rashunal(2),
    };
    Rashunal *e = n_Rashunal(2, 3);
    RMatrix *m = new_RMatrix(3, 4, data1);
    RMatrix *expected = new_RMatrix(3, 4, data2);

    RMatrix *actual = RMatrix_set(m, e, 3, 2);

    TEST_ASSERT_TRUE(RMatrix_cmp(expected, actual) == 0);

    free_RMatrix(m);
    free_RMatrix(expected);
    free_RMatrix(actual);
    free(e);
    for (int i = 0; i < 12; ++i) {
        free((void *)data1[i]);
        free((void *)data2[i]);
    }
}

void test_RMatrix_row_mul()
{
    Rashunal *data1[] = {
        ni_Rashunal(1),
        ni_Rashunal(2),
        ni_Rashunal(3),
        ni_Rashunal(4),
        ni_Rashunal(5),
        ni_Rashunal(6),
        ni_Rashunal(7),
        ni_Rashunal(8),
        ni_Rashunal(9),
        ni_Rashunal(0),
        ni_Rashunal(1),
        ni_Rashunal(2),
    };
    Rashunal *data2[] = {
        ni_Rashunal(1),
        ni_Rashunal(2),
        ni_Rashunal(3),
        ni_Rashunal(4),
        n_Rashunal(10, 3),
        ni_Rashunal(4),
        n_Rashunal(14, 3),
        n_Rashunal(16, 3),
        ni_Rashunal(9),
        ni_Rashunal(0),
        ni_Rashunal(1),
        ni_Rashunal(2),
    };
    Rashunal *e = n_Rashunal(2, 3);
    RMatrix *m = new_RMatrix(3, 4, data1);
    RMatrix *expected = new_RMatrix(3, 4, data2);

    RMatrix *actual = RMatrix_row_mul(m, e, 2);

    TEST_ASSERT_TRUE(RMatrix_cmp(expected, actual) == 0);

    free_RMatrix(m);
    free_RMatrix(expected);
    free_RMatrix(actual);
    free(e);
    for (int i = 0; i < 12; ++i) {
        free((void *)data1[i]);
        free((void *)data2[i]);
    }
}

void test_RMatrix_row_swap()
{
    Rashunal *data1[] = {
        ni_Rashunal(1),
        ni_Rashunal(2),
        ni_Rashunal(3),
        ni_Rashunal(4),
        ni_Rashunal(5),
        ni_Rashunal(6),
        ni_Rashunal(7),
        ni_Rashunal(8),
        ni_Rashunal(9),
        ni_Rashunal(0),
        ni_Rashunal(1),
        ni_Rashunal(2),
    };
    Rashunal *data2[] = {
        ni_Rashunal(1),
        ni_Rashunal(2),
        ni_Rashunal(3),
        ni_Rashunal(4),
        ni_Rashunal(9),
        ni_Rashunal(0),
        ni_Rashunal(1),
        ni_Rashunal(2),
        ni_Rashunal(5),
        ni_Rashunal(6),
        ni_Rashunal(7),
        ni_Rashunal(8),
    };
    RMatrix *m = new_RMatrix(3, 4, data1);
    RMatrix *expected = new_RMatrix(3, 4, data2);

    RMatrix *actual = RMatrix_row_swap(m, 2, 3);

    TEST_ASSERT_TRUE(RMatrix_cmp(expected, actual) == 0);

    free_RMatrix(m);
    free_RMatrix(expected);
    free_RMatrix(actual);
    for (int i = 0; i < 12; ++i) {
        free((void *)data1[i]);
        free((void *)data2[i]);
    }
}

void test_RMatrix_lc()
{
    Rashunal *data1[] = {
        ni_Rashunal(1),
        ni_Rashunal(2),
        ni_Rashunal(3),
        ni_Rashunal(4),
        ni_Rashunal(5),
        ni_Rashunal(6),
        ni_Rashunal(7),
        ni_Rashunal(8),
        ni_Rashunal(9),
        ni_Rashunal(0),
        ni_Rashunal(1),
        ni_Rashunal(2),
    };
    Rashunal *data2[] = {
        ni_Rashunal(1),
        ni_Rashunal(2),
        ni_Rashunal(3),
        ni_Rashunal(4),
        ni_Rashunal(5),
        ni_Rashunal(6),
        ni_Rashunal(7),
        ni_Rashunal(8),
        ni_Rashunal(0),
        n_Rashunal(-54, 5),
        n_Rashunal(-58, 5),
        n_Rashunal(-62, 5),
    };
    Rashunal *scale = n_Rashunal(-9, 5);
    RMatrix *m = new_RMatrix(3, 4, data1);
    RMatrix *expected = new_RMatrix(3, 4, data2);

    RMatrix *actual = RMatrix_lc(m, scale, 2, 3);

    TEST_ASSERT_TRUE(RMatrix_cmp(expected, actual) == 0);

    free(scale);
    free_RMatrix(m);
    free_RMatrix(expected);
    free_RMatrix(actual);
    for (int i = 0; i < 12; ++i) {
        free((void *)data1[i]);
        free((void *)data2[i]);
    }
}

void test_RMatrix_invert_returns_null_and_sets_errno_if_rectangular()
{
    Rashunal *data[] = {
        ni_Rashunal(1),
        ni_Rashunal(2),
        ni_Rashunal(3),
        ni_Rashunal(4),
        ni_Rashunal(5),
        ni_Rashunal(6),
        ni_Rashunal(7),
        ni_Rashunal(8),
        ni_Rashunal(9),
        ni_Rashunal(0),
        ni_Rashunal(1),
        ni_Rashunal(2),
    };
    RMatrix *m = new_RMatrix(3, 4, data);
    RMatrix *inv = RMatrix_invert(m);

    TEST_ASSERT_NULL(inv);
    TEST_ASSERT_EQUAL(EINVAL, errno);

    free_RMatrix(m);
    for (int i = 0; i < 12; ++i) {
        free((void *)data[i]);
    }
}

void test_RMatrix_invert_returns_null_and_sets_errno_if_singular()
{
    Rashunal *data[] = {
        ni_Rashunal(1),
        ni_Rashunal(2),
        ni_Rashunal(3),
        ni_Rashunal(4),
        ni_Rashunal(5),
        ni_Rashunal(6),
        ni_Rashunal(3),
        ni_Rashunal(6),
        ni_Rashunal(9),
    };
    RMatrix *m = new_RMatrix(3, 3, data);
    RMatrix *inv = RMatrix_invert(m);

    TEST_ASSERT_NULL(inv);
    TEST_ASSERT_EQUAL(EINVAL, errno);

    free_RMatrix(m);
    for (int i = 0; i < 9; ++i) {
        free((void *)data[i]);
    }
}

void test_RMatrix_invert()
{
    Rashunal *data[] = {
        ni_Rashunal(2),
        ni_Rashunal(-1),
        ni_Rashunal(0),
        ni_Rashunal(-1),
        ni_Rashunal(2),
        ni_Rashunal(-1),
        ni_Rashunal(0),
        ni_Rashunal(-1),
        ni_Rashunal(2),
    };
    Rashunal *data2[] = {
        n_Rashunal(3, 4),
        n_Rashunal(1, 2),
        n_Rashunal(1, 4),
        n_Rashunal(1, 2),
        ni_Rashunal(1),
        n_Rashunal(1, 2),
        n_Rashunal(1, 4),
        n_Rashunal(1, 2),
        n_Rashunal(3, 4),
    };
    RMatrix *m = new_RMatrix(3, 3, data);
    RMatrix *exp = new_RMatrix(3, 3, data2);

    RMatrix *inv = RMatrix_invert(m);

    TEST_ASSERT_EQUAL(0, RMatrix_cmp(exp, inv));

    free_RMatrix(m);
    free_RMatrix(exp);
    free_RMatrix(inv);
    for (int i = 0; i < 9; ++i) {
        free((void *)data[i]);
        free((void *)data2[i]);
    }
}

void test_RMatrix_Gauss_Factorization()
{
    Rashunal *data[4] = {
        ni_Rashunal(1),
        ni_Rashunal(2),
        ni_Rashunal(3),
        ni_Rashunal(4),
    };
    Rashunal *el_data[4] = {
        ni_Rashunal(1),
        ni_Rashunal(0),
        ni_Rashunal(3),
        ni_Rashunal(1),
    };
    Rashunal *ed_data[4] = {
        ni_Rashunal(1),
        ni_Rashunal(0),
        ni_Rashunal(0),
        ni_Rashunal(-2),
    };
    Rashunal *eu_data[4] = {
        ni_Rashunal(1),
        ni_Rashunal(2),
        ni_Rashunal(0),
        ni_Rashunal(1),
    };
    RMatrix *m = new_RMatrix(2, 2, data);
    RMatrix *expected_p = new_identity_RMatrix(2);
    RMatrix *expected_l = new_RMatrix(2, 2, el_data);
    RMatrix *expected_d = new_RMatrix(2, 2, ed_data);
    RMatrix *expected_u = new_RMatrix(2, 2, eu_data);

    Gauss_Factorization *f = RMatrix_gelim(m);

    TEST_ASSERT_EQUAL(RMatrix_cmp(f->pi, expected_p), 0);
    TEST_ASSERT_EQUAL(RMatrix_cmp(f->l, expected_l), 0);
    TEST_ASSERT_EQUAL(RMatrix_cmp(f->d, expected_d), 0);
    TEST_ASSERT_EQUAL(RMatrix_cmp(f->u, expected_u), 0);

    free_RMatrix(m);
    free_RMatrix(expected_p);
    free_RMatrix(expected_l);
    free_RMatrix(expected_d);
    free_RMatrix(expected_u);
    free_RMatrix((RMatrix *)f->pi);
    free_RMatrix((RMatrix *)f->l);
    free_RMatrix((RMatrix *)f->d);
    free_RMatrix((RMatrix *)f->u);
    free(f);
    for (int i = 0; i < 4; ++i) {
        free((void *)data[i]);
        free((void *)el_data[i]);
        free((void *)ed_data[i]);
        free((void *)eu_data[i]);
    }
}

void test_RMatrix_Gauss_Factorization_with_row_exchange()
{
    Rashunal *data[9] = {
        ni_Rashunal(0),
        ni_Rashunal(1),
        ni_Rashunal(1),
        ni_Rashunal(1),
        ni_Rashunal(0),
        ni_Rashunal(1),
        ni_Rashunal(2),
        ni_Rashunal(3),
        ni_Rashunal(4),
    };
    Rashunal *epi_data[9] = {
        ni_Rashunal(0),
        ni_Rashunal(1),
        ni_Rashunal(0),
        ni_Rashunal(1),
        ni_Rashunal(0),
        ni_Rashunal(0),
        ni_Rashunal(0),
        ni_Rashunal(0),
        ni_Rashunal(1),
    };
    Rashunal *el_data[9] = {
        ni_Rashunal(1),
        ni_Rashunal(0),
        ni_Rashunal(0),
        ni_Rashunal(0),
        ni_Rashunal(1),
        ni_Rashunal(0),
        ni_Rashunal(2),
        ni_Rashunal(3),
        ni_Rashunal(1),
    };
    Rashunal *ed_data[9] = {
        ni_Rashunal(1),
        ni_Rashunal(0),
        ni_Rashunal(0),
        ni_Rashunal(0),
        ni_Rashunal(1),
        ni_Rashunal(0),
        ni_Rashunal(0),
        ni_Rashunal(0),
        ni_Rashunal(-1),
    };
    Rashunal *eu_data[9] = {
        ni_Rashunal(1),
        ni_Rashunal(0),
        ni_Rashunal(1),
        ni_Rashunal(0),
        ni_Rashunal(1),
        ni_Rashunal(1),
        ni_Rashunal(0),
        ni_Rashunal(0),
        ni_Rashunal(1),
    };
    RMatrix *m = new_RMatrix(3, 3, data);
    RMatrix *expected_p = new_RMatrix(3, 3, epi_data);
    RMatrix *expected_l = new_RMatrix(3, 3, el_data);
    RMatrix *expected_d = new_RMatrix(3, 3, ed_data);
    RMatrix *expected_u = new_RMatrix(3, 3, eu_data);

    Gauss_Factorization *f = RMatrix_gelim(m);

    TEST_ASSERT_EQUAL(RMatrix_cmp(f->pi, expected_p), 0);
    TEST_ASSERT_EQUAL(RMatrix_cmp(f->l, expected_l), 0);
    TEST_ASSERT_EQUAL(RMatrix_cmp(f->d, expected_d), 0);
    TEST_ASSERT_EQUAL(RMatrix_cmp(f->u, expected_u), 0);

    free_RMatrix(m);
    free_RMatrix(expected_p);
    free_RMatrix(expected_l);
    free_RMatrix(expected_d);
    free_RMatrix(expected_u);
    free_RMatrix((RMatrix *)f->pi);
    free_RMatrix((RMatrix *)f->l);
    free_RMatrix((RMatrix *)f->d);
    free_RMatrix((RMatrix *)f->u);
    free(f);
    for (int i = 0; i < 9; ++i) {
        free((void *)data[i]);
        free((void *)epi_data[i]);
        free((void *)el_data[i]);
        free((void *)ed_data[i]);
        free((void *)eu_data[i]);
    }
}

void test_RMatrix_Gauss_Factorization_of_rectangular_matrix()
{
    Rashunal *data[12] = {
        ni_Rashunal(1),
        ni_Rashunal(3),
        ni_Rashunal(3),
        ni_Rashunal(2),
        ni_Rashunal(2),
        ni_Rashunal(6),
        ni_Rashunal(9),
        ni_Rashunal(5),
        ni_Rashunal(-1),
        ni_Rashunal(-3),
        ni_Rashunal(3),
        ni_Rashunal(0),
    };
    Rashunal *el_data[9] = {
        ni_Rashunal(1),
        ni_Rashunal(0),
        ni_Rashunal(0),
        ni_Rashunal(2),
        ni_Rashunal(1),
        ni_Rashunal(0),
        ni_Rashunal(-1),
        ni_Rashunal(2),
        ni_Rashunal(1),
    };
    Rashunal *eu_data[12] = {
        ni_Rashunal(1),
        ni_Rashunal(3),
        ni_Rashunal(3),
        ni_Rashunal(2),
        ni_Rashunal(0),
        ni_Rashunal(0),
        ni_Rashunal(3),
        ni_Rashunal(1),
        ni_Rashunal(0),
        ni_Rashunal(0),
        ni_Rashunal(0),
        ni_Rashunal(0),
    };
    RMatrix *m = new_RMatrix(3, 4, data);
    RMatrix *expected_l = new_RMatrix(3, 3, el_data);
    RMatrix *expected_u = new_RMatrix(3, 4, eu_data);

    Gauss_Factorization *f = RMatrix_gelim(m);

    TEST_ASSERT_EQUAL(RMatrix_cmp(f->l, expected_l), 0);
    TEST_ASSERT_NULL(f->d);
    TEST_ASSERT_EQUAL(RMatrix_cmp(f->u, expected_u), 0);

    free_RMatrix(m);
    free_RMatrix(expected_l);
    free_RMatrix(expected_u);
    free_RMatrix((RMatrix *)f->pi);
    free_RMatrix((RMatrix *)f->l);
    free_RMatrix((RMatrix *)f->u);
    free(f);
    for (int i = 0; i < 12; ++i) {
        free((void *)data[i]);
        free((void *)eu_data[i]);
    }
    for (int i = 0; i < 9; ++i) {
        free((void *)el_data[i]);
    }
}

void tearDown(void)
{

}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_new_RMatrix_returns_matrix);
    RUN_TEST(test_new_RMatrix_with_invalid_dimensions_return_void_and_sets_errno);
    RUN_TEST(test_new_identity_RMatrix_returns_identity);
    RUN_TEST(test_RMatrix_add);
    RUN_TEST(test_RMatrix_mul);
    RUN_TEST(test_RMatrix_transpose);
    RUN_TEST(test_RMatrix_to_string_array);
    RUN_TEST(test_RMatrix_cmp);
    RUN_TEST(test_RMatrix_set);
    RUN_TEST(test_RMatrix_row_mul);
    RUN_TEST(test_RMatrix_row_swap);
    RUN_TEST(test_RMatrix_lc);
    RUN_TEST(test_RMatrix_invert_returns_null_and_sets_errno_if_rectangular);
    RUN_TEST(test_RMatrix_invert_returns_null_and_sets_errno_if_singular);
    RUN_TEST(test_RMatrix_invert);
    RUN_TEST(test_RMatrix_Gauss_Factorization);
    RUN_TEST(test_RMatrix_Gauss_Factorization_with_row_exchange);
    RUN_TEST(test_RMatrix_Gauss_Factorization_of_rectangular_matrix);

    return UNITY_END();
}