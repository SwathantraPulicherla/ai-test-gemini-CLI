
#include "unity.h"
#include "temperature_utils.h"
#include <string.h>

/*
NOTE: Implementations for functions in temperature_sensor.h were not provided.
As per the strict constraints "TEST ACTUAL IMPLEMENTATIONS" and "NO FUNCTION REDEFINITION",
tests for functions without a provided implementation cannot be generated.
Therefore, only functions from temperature_utils.c are tested.
*/

// setUp and tearDown functions are called before and after each test
void setUp(void) {
    // No setup needed
}

void tearDown(void) {
    // No teardown needed
}

// Test suite for calculate_temperature_difference
void test_calculate_temperature_difference_positive_temps_t1_greater(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 10.5f, calculate_temperature_difference(30.5f, 20.0f));
}

void test_calculate_temperature_difference_positive_temps_t2_greater(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 10.5f, calculate_temperature_difference(20.0f, 30.5f));
}

void test_calculate_temperature_difference_equal_temps(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, calculate_temperature_difference(25.0f, 25.0f));
}

void test_calculate_temperature_difference_negative_temps_t1_greater(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 10.5f, calculate_temperature_difference(-10.0f, -20.5f));
}

void test_calculate_temperature_difference_negative_temps_t2_greater(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 10.5f, calculate_temperature_difference(-20.5f, -10.0f));
}

void test_calculate_temperature_difference_mixed_sign_temps(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 20.0f, calculate_temperature_difference(10.0f, -10.0f));
}

void test_calculate_temperature_difference_mixed_sign_temps_reversed(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 20.0f, calculate_temperature_difference(-10.0f, 10.0f));
}

// Test suite for is_temperature_stable
void test_is_temperature_stable_when_diff_is_small_and_positive(void) {
    TEST_ASSERT_EQUAL(1, is_temperature_stable(25.0f, 24.0f));
}

void test_is_temperature_stable_when_diff_is_small_and_negative(void) {
    TEST_ASSERT_EQUAL(1, is_temperature_stable(24.0f, 25.0f));
}

void test_is_temperature_stable_at_upper_boundary(void) {
    TEST_ASSERT_EQUAL(1, is_temperature_stable(25.0f, 20.0f));
}

void test_is_temperature_stable_at_upper_boundary_reversed(void) {
    TEST_ASSERT_EQUAL(1, is_temperature_stable(20.0f, 25.0f));
}

void test_is_temperature_stable_just_outside_boundary(void) {
    TEST_ASSERT_EQUAL(0, is_temperature_stable(25.1f, 20.0f));
}

void test_is_temperature_stable_just_outside_boundary_reversed(void) {
    TEST_ASSERT_EQUAL(0, is_temperature_stable(20.0f, 25.1f));
}

void test_is_temperature_stable_when_equal(void) {
    TEST_ASSERT_EQUAL(1, is_temperature_stable(25.0f, 25.0f));
}

void test_is_temperature_stable_with_negative_temps_within_range(void) {
    TEST_ASSERT_EQUAL(1, is_temperature_stable(-5.0f, -9.0f));
}

void test_is_temperature_stable_with_negative_temps_at_boundary(void) {
    TEST_ASSERT_EQUAL(1, is_temperature_stable(-5.0f, -10.0f));
}

void test_is_temperature_stable_with_negative_temps_outside_range(void) {
    TEST_ASSERT_EQUAL(0, is_temperature_stable(-5.0f, -10.1f));
}

// Test suite for get_temperature_trend
void test_get_temperature_trend_is_rising(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Rising", get_temperature_trend(26.0f, 25.0f)));
}

void test_get_temperature_trend_is_falling(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Falling", get_temperature_trend(24.0f, 25.0f)));
}

void test_get_temperature_trend_is_stable(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Stable", get_temperature_trend(25.0f, 25.0f)));
}

void test_get_temperature_trend_is_rising_with_negative_values(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Rising", get_temperature_trend(-5.0f, -10.0f)));
}

void test_get_temperature_trend_is_falling_with_negative_values(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Falling", get_temperature_trend(-10.0f, -5.0f)));
}

void test_get_temperature_trend_is_stable_with_negative_values(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Stable", get_temperature_trend(-10.0f, -10.0f)));
}

// Main function to run all tests
int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_calculate_temperature_difference_positive_temps_t1_greater);
    RUN_TEST(test_calculate_temperature_difference_positive_temps_t2_greater);
    RUN_TEST(test_calculate_temperature_difference_equal_temps);
    RUN_TEST(test_calculate_temperature_difference_negative_temps_t1_greater);
    RUN_TEST(test_calculate_temperature_difference_negative_temps_t2_greater);
    RUN_TEST(test_calculate_temperature_difference_mixed_sign_temps);
    RUN_TEST(test_calculate_temperature_difference_mixed_sign_temps_reversed);

    RUN_TEST(test_is_temperature_stable_when_diff_is_small_and_positive);
    RUN_TEST(test_is_temperature_stable_when_diff_is_small_and_negative);
    RUN_TEST(test_is_temperature_stable_at_upper_boundary);
    RUN_TEST(test_is_temperature_stable_at_upper_boundary_reversed);
    RUN_TEST(test_is_temperature_stable_just_outside_boundary);
    RUN_TEST(test_is_temperature_stable_just_outside_boundary_reversed);
    RUN_TEST(test_is_temperature_stable_when_equal);
    RUN_TEST(test_is_temperature_stable_with_negative_temps_within_range);
    RUN_TEST(test_is_temperature_stable_with_negative_temps_at_boundary);
    RUN_TEST(test_is_temperature_stable_with_negative_temps_outside_range);

    RUN_TEST(test_get_temperature_trend_is_rising);
    RUN_TEST(test_get_temperature_trend_is_falling);
    RUN_TEST(test_get_temperature_trend_is_stable);
    RUN_TEST(test_get_temperature_trend_is_rising_with_negative_values);
    RUN_TEST(test_get_temperature_trend_is_falling_with_negative_values);
    RUN_TEST(test_get_temperature_trend_is_stable_with_negative_values);

    return UNITY_END();
}
