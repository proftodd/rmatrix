#include <errno.h>
#include <stdlib.h>
#include "rmatrix.h"
#include "unity.h"

void setUp(void) {

}

void test_new_RMatrix_returns_matrix()
{
    const Rashunal *data[] = {
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
    const Rashunal *data[] = {};
    RMatrix *m = new_RMatrix(2, 0, data);
    TEST_ASSERT_NULL(m);
    TEST_ASSERT_EQUAL(EINVAL, errno);
}

void test_new_identity_RMatrix_returns_identity()
{
    const Rashunal *data[] = {
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
    const Rashunal *data1[] = {
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
    const Rashunal *data2[] = {
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
    const Rashunal *data3[] = {
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
    const Rashunal *data1[] = {
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
    const Rashunal *data2[] = {
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
    const Rashunal *data1[] = {
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
    const Rashunal *data2[] = {
        ni_Rashunal(1),
        ni_Rashunal(2),
        ni_Rashunal(-1),
        ni_Rashunal(-2),
        ni_Rashunal(0),
        ni_Rashunal(3),
        ni_Rashunal(1),
        ni_Rashunal(0),
    };
    const Rashunal *data3[] = {
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
    const Rashunal *data[] = {
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
    const Rashunal *data1[] = {
        ni_Rashunal(1),
        ni_Rashunal(2),
        ni_Rashunal(3),
        ni_Rashunal(4),
        ni_Rashunal(5),
        ni_Rashunal(6),
    };
    const Rashunal *data2[] = {
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
    const Rashunal *data1[] = {
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
    const Rashunal *data2[] = {
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
    const Rashunal *data1[] = {
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
    const Rashunal *data2[] = {
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
    const Rashunal *data1[] = {
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
    const Rashunal *data2[] = {
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
    const Rashunal *data1[] = {
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
    const Rashunal *data2[] = {
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

    return UNITY_END();
}