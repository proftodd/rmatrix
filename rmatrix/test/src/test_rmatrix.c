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
        free(data[i]);
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
    const char** str = RMatrix_to_string_array(m);
    TEST_ASSERT_EQUAL_STRING("[ 1 2      3     ]", str[0]);
    TEST_ASSERT_EQUAL_STRING("[ 4 1 / 2 10 / 3 ]", str[1]);

    for (int i = 0; i < 6; ++i) {
        free(data[i]);
    }
    free_RMatrix(m);
    for (int i = 0; i < 2; ++i) {
        free(str[i]);
    }
    free(str);
}

void tearDown(void) {

}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_new_RMatrix_returns_matrix);
    RUN_TEST(test_new_RMatrix_with_invalid_dimensions_return_void_and_sets_errno);
    RUN_TEST(test_RMatrix_to_string_array);

    return UNITY_END();
}