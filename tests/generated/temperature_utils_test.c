
#include "unity.h"
#include "temperature_utils.h"
#include <string.h>

// setUp and tearDown functions
void setUp(void) {
    // Set up tasks, if any
}

void tearDown(void) {
    // Clean up tasks, if any
}

// Tests for calculate_temperature_difference
void test_calculate_temperature_difference_positive(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 5.0f, calculate_temperature_difference(25.0f, 20.0f));
}

void test_calculate_temperature_difference_order_is_irrelevant(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 5.0f, calculate_temperature_difference(20.0f, 25.0f));
}

void test_calculate_temperature_difference_zero(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, calculate_temperature_difference(20.0f, 20.0f));
}

void test_calculate_temperature_difference_with_negative_numbers(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 5.0f, calculate_temperature_difference(-10.0f, -15.0f));
}

void test_calculate_temperature_difference_mixed_sign_numbers(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 20.0f, calculate_temperature_difference(10.0f, -10.0f));
}

void test_calculate_temperature_difference_with_fractions(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.2f, calculate_temperature_difference(22.5f, 21.3f));
}

// Tests for is_temperature_stable
void test_is_temperature_stable_within_range(void) {
    TEST_ASSERT_TRUE(is_temperature_stable(25.0f, 22.0f)); // diff = 3.0
}

void test_is_temperature_stable_at_boundary(void) {
    TEST_ASSERT_TRUE(is_temperature_stable(25.0f, 20.0f)); // diff = 5.0
}

void test_is_temperature_stable_just_outside_range(void) {
    TEST_ASSERT_FALSE(is_temperature_stable(25.1f, 20.0f)); // diff = 5.1
}

void test_is_temperature_stable_far_outside_range(void) {
    TEST_ASSERT_FALSE(is_temperature_stable(35.0f, 20.0f)); // diff = 15.0
}

void test_is_temperature_stable_no_change(void) {
    TEST_ASSERT_TRUE(is_temperature_stable(30.0f, 30.0f)); // diff = 0.0
}

void test_is_temperature_stable_negative_values_stable(void) {
    TEST_ASSERT_TRUE(is_temperature_stable(-10.0f, -14.5f)); // diff = 4.5
}

void test_is_temperature_stable_negative_values_unstable(void) {
    TEST_ASSERT_FALSE(is_temperature_stable(-10.0f, -16.0f)); // diff = 6.0
}

// Tests for get_temperature_trend
void test_get_temperature_trend_rising(void) {
    const char* trend = get_temperature_trend(25.0f, 20.0f);
    TEST_ASSERT_NOT_NULL(trend);
    TEST_ASSERT_EQUAL(0, strcmp("Rising", trend));
}

void test_get_temperature_trend_falling(void) {
    const char* trend = get_temperature_trend(20.0f, 25.0f);
    TEST_ASSERT_NOT_NULL(trend);
    TEST_ASSERT_EQUAL(0, strcmp("Falling", trend));
}

void test_get_temperature_trend_stable(void) {
    const char* trend = get_temperature_trend(20.0f, 20.0f);
    TEST_ASSERT_NOT_NULL(trend);
    TEST_ASSERT_EQUAL(0, strcmp("Stable", trend));
}

void test_get_temperature_trend_rising_with_negatives(void) {
    const char* trend = get_temperature_trend(-5.0f, -10.0f);
    TEST_ASSERT_NOT_NULL(trend);
    TEST_ASSERT_EQUAL(0, strcmp("Rising", trend));
}

void test_get_temperature_trend_falling_with_negatives(void) {
    const char* trend = get_temperature_trend(-10.0f, -5.0f);
    TEST_ASSERT_NOT_NULL(trend);
    TEST_ASSERT_EQUAL(0, strcmp("Falling", trend));
}

void test_get_temperature_trend_stable_with_negatives(void) {
    const char* trend = get_temperature_trend(-10.0f, -10.0f);
    TEST_ASSERT_NOT_NULL(trend);
    TEST_ASSERT_EQUAL(0, strcmp("Stable", trend));
}

// Main function to run all tests
int main(void) {
    UNITY_BEGIN();

    // Run tests for calculate_temperature_difference
    RUN_TEST(test_calculate_temperature_difference_positive);
    RUN_TEST(test_calculate_temperature_difference_order_is_irrelevant);
    RUN_TEST(test_calculate_temperature_difference_zero);
    RUN_TEST(test_calculate_temperature_difference_with_negative_numbers);
    RUN_TEST(test_calculate_temperature_difference_mixed_sign_numbers);
    RUN_TEST(test_calculate_temperature_difference_with_fractions);

    // Run tests for is_temperature_stable
    RUN_TEST(test_is_temperature_stable_within_range);
    RUN_TEST(test_is_temperature_stable_at_boundary);
    RUN_TEST(test_is_temperature_stable_just_outside_range);
    RUN_TEST(test_is_temperature_stable_far_outside_range);
    RUN_TEST(test_is_temperature_stable_no_change);
    RUN_TEST(test_is_temperature_stable_negative_values_stable);
    RUN_TEST(test_is_temperature_stable_negative_values_unstable);

    // Run tests for get_temperature_trend
    RUN_TEST(test_get_temperature_trend_rising);
    RUN_TEST(test_get_temperature_trend_falling);
    RUN_TEST(test_get_temperature_trend_stable);
    RUN_TEST(test_get_temperature_trend_rising_with_negatives);
    RUN_TEST(test_get_temperature_trend_falling_with_negatives);
    RUN_TEST(test_get_temperature_trend_stable_with_negatives);

    return UNITY_END();
}
