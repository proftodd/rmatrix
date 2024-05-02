#include <stdlib.h>
#include "rmatrix.h"
#include "unity.h"

void setUp(void) {

}

void test_new_RMatrix_returns_matrix()
{
    RMatrix *m = new_RMatrix(2, 3);
    TEST_ASSERT_EQUAL(2, m->height);
    TEST_ASSERT_EQUAL(3, m->width);
    free_RMatrix(m);
}

void tearDown(void) {

}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_new_RMatrix_returns_matrix);

    return UNITY_END();
}