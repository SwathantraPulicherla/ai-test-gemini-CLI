
#include "unity.h"
#include "temperature_utils.h"
#include <string.h>

// setUp and tearDown functions, if needed
void setUp(void) {
    // Set up tasks before each test
}

void tearDown(void) {
    // Clean up tasks after each test
}

// Tests for calculate_temperature_difference
void test_calculate_temperature_difference_positive_values(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 5.5f, calculate_temperature_difference(25.5f, 20.0f));
}

void test_calculate_temperature_difference_swapped_positive_values(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 5.5f, calculate_temperature_difference(20.0f, 25.5f));
}

void test_calculate_temperature_difference_equal_values(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, calculate_temperature_difference(10.0f, 10.0f));
}

void test_calculate_temperature_difference_negative_values(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 5.0f, calculate_temperature_difference(-5.0f, -10.0f));
}

void test_calculate_temperature_difference_swapped_negative_values(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 5.0f, calculate_temperature_difference(-10.0f, -5.0f));
}

void test_calculate_temperature_difference_mixed_sign_values(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 10.0f, calculate_temperature_difference(5.0f, -5.0f));
}

void test_calculate_temperature_difference_zero_involved(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 15.0f, calculate_temperature_difference(15.0f, 0.0f));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 15.0f, calculate_temperature_difference(0.0f, -15.0f));
}

// Tests for is_temperature_stable
void test_is_temperature_stable_within_limit(void) {
    TEST_ASSERT_TRUE(is_temperature_stable(22.0f, 20.0f));
}

void test_is_temperature_stable_at_boundary(void) {
    TEST_ASSERT_TRUE(is_temperature_stable(25.0f, 20.0f));
}

void test_is_temperature_stable_at_boundary_swapped(void) {
    TEST_ASSERT_TRUE(is_temperature_stable(20.0f, 25.0f));
}

void test_is_temperature_stable_zero_difference(void) {
    TEST_ASSERT_TRUE(is_temperature_stable(20.0f, 20.0f));
}

void test_is_temperature_stable_just_over_limit(void) {
    TEST_ASSERT_FALSE(is_temperature_stable(25.001f, 20.0f));
}

void test_is_temperature_stable_large_difference(void) {
    TEST_ASSERT_FALSE(is_temperature_stable(30.0f, 20.0f));
}

void test_is_temperature_stable_negative_values_stable(void) {
    TEST_ASSERT_TRUE(is_temperature_stable(-10.0f, -14.5f));
}

void test_is_temperature_stable_negative_values_unstable(void) {
    TEST_ASSERT_FALSE(is_temperature_stable(-10.0f, -20.0f));
}

// Tests for get_temperature_trend
void test_get_temperature_trend_rising(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Rising", get_temperature_trend(25.0f, 20.0f)));
}

void test_get_temperature_trend_falling(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Falling", get_temperature_trend(20.0f, 25.0f)));
}

void test_get_temperature_trend_stable(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Stable", get_temperature_trend(20.0f, 20.0f)));
}

void test_get_temperature_trend_rising_from_negative(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Rising", get_temperature_trend(-5.0f, -10.0f)));
}

void test_get_temperature_trend_falling_to_negative(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Falling", get_temperature_trend(-10.0f, -5.0f)));
}

void test_get_temperature_trend_stable_at_negative(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Stable", get_temperature_trend(-10.0f, -10.0f)));
}

void test_get_temperature_trend_crossing_zero_rising(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Rising", get_temperature_trend(2.0f, -2.0f)));
}

void test_get_temperature_trend_crossing_zero_falling(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Falling", get_temperature_trend(-2.0f, 2.0f)));
}

// Main function to run all tests
int main(void) {
    UNITY_BEGIN();

    // Run tests for calculate_temperature_difference
    RUN_TEST(test_calculate_temperature_difference_positive_values);
    RUN_TEST(test_calculate_temperature_difference_swapped_positive_values);
    RUN_TEST(test_calculate_temperature_difference_equal_values);
    RUN_TEST(test_calculate_temperature_difference_negative_values);
    RUN_TEST(test_calculate_temperature_difference_swapped_negative_values);
    RUN_TEST(test_calculate_temperature_difference_mixed_sign_values);
    RUN_TEST(test_calculate_temperature_difference_zero_involved);

    // Run tests for is_temperature_stable
    RUN_TEST(test_is_temperature_stable_within_limit);
    RUN_TEST(test_is_temperature_stable_at_boundary);
    RUN_TEST(test_is_temperature_stable_at_boundary_swapped);
    RUN_TEST(test_is_temperature_stable_zero_difference);
    RUN_TEST(test_is_temperature_stable_just_over_limit);
    RUN_TEST(test_is_temperature_stable_large_difference);
    RUN_TEST(test_is_temperature_stable_negative_values_stable);
    RUN_TEST(test_is_temperature_stable_negative_values_unstable);

    // Run tests for get_temperature_trend
    RUN_TEST(test_get_temperature_trend_rising);
    RUN_TEST(test_get_temperature_trend_falling);
    RUN_TEST(test_get_temperature_trend_stable);
    RUN_TEST(test_get_temperature_trend_rising_from_negative);
    RUN_TEST(test_get_temperature_trend_falling_to_negative);
    RUN_TEST(test_get_temperature_trend_stable_at_negative);
    RUN_TEST(test_get_temperature_trend_crossing_zero_rising);
    RUN_TEST(test_get_temperature_trend_crossing_zero_falling);

    return UNITY_END();
}
