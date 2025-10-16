
#include "unity.h"
#include "temperature_utils.h"
#include <string.h>

// setUp and tearDown functions are optional but good practice
void setUp(void) {
    // Set up any necessary resources before each test
}

void tearDown(void) {
    // Clean up any resources after each test
}

// =================================================================
// Test suite for calculate_temperature_difference
// =================================================================

void test_calculate_temperature_difference_positive_result(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 5.0f, calculate_temperature_difference(25.0f, 20.0f));
}

void test_calculate_temperature_difference_negative_result_is_absolute(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 5.0f, calculate_temperature_difference(20.0f, 25.0f));
}

void test_calculate_temperature_difference_zero_difference(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, calculate_temperature_difference(22.5f, 22.5f));
}

void test_calculate_temperature_difference_with_negative_temperatures(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 5.0f, calculate_temperature_difference(-10.0f, -5.0f));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 5.0f, calculate_temperature_difference(-5.0f, -10.0f));
}

void test_calculate_temperature_difference_across_zero(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 10.0f, calculate_temperature_difference(5.0f, -5.0f));
}

void test_calculate_temperature_difference_with_fractional_values(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 5.3f, calculate_temperature_difference(25.5f, 20.2f));
}

// =================================================================
// Test suite for is_temperature_stable
// =================================================================

void test_is_temperature_stable_when_difference_is_small(void) {
    TEST_ASSERT_EQUAL(1, is_temperature_stable(23.0f, 20.0f)); // Diff = 3.0
}

void test_is_temperature_stable_at_boundary(void) {
    TEST_ASSERT_EQUAL(1, is_temperature_stable(25.0f, 20.0f)); // Diff = 5.0
    TEST_ASSERT_EQUAL(1, is_temperature_stable(20.0f, 25.0f)); // Diff = 5.0
}

void test_is_temperature_stable_just_outside_boundary(void) {
    TEST_ASSERT_EQUAL(0, is_temperature_stable(25.1f, 20.0f)); // Diff = 5.1
    TEST_ASSERT_EQUAL(0, is_temperature_stable(19.9f, 25.0f)); // Diff = 5.1
}

void test_is_temperature_stable_for_zero_difference(void) {
    TEST_ASSERT_EQUAL(1, is_temperature_stable(22.2f, 22.2f));
}

void test_is_temperature_stable_with_large_difference(void) {
    TEST_ASSERT_EQUAL(0, is_temperature_stable(30.0f, 20.0f)); // Diff = 10.0
}

void test_is_temperature_stable_with_negative_values_within_limit(void) {
    TEST_ASSERT_EQUAL(1, is_temperature_stable(-10.0f, -14.0f)); // Diff = 4.0
}

void test_is_temperature_stable_with_negative_values_outside_limit(void) {
    TEST_ASSERT_EQUAL(0, is_temperature_stable(-10.0f, -16.0f)); // Diff = 6.0
}


// =================================================================
// Test suite for get_temperature_trend
// =================================================================

void test_get_temperature_trend_rising(void) {
    const char* trend = get_temperature_trend(25.0f, 20.0f);
    TEST_ASSERT_EQUAL(0, strcmp("Rising", trend));
}

void test_get_temperature_trend_falling(void) {
    const char* trend = get_temperature_trend(20.0f, 25.0f);
    TEST_ASSERT_EQUAL(0, strcmp("Falling", trend));
}

void test_get_temperature_trend_stable(void) {
    const char* trend = get_temperature_trend(22.5f, 22.5f);
    TEST_ASSERT_EQUAL(0, strcmp("Stable", trend));
}

void test_get_temperature_trend_rising_with_negative_values(void) {
    const char* trend = get_temperature_trend(-5.0f, -10.0f);
    TEST_ASSERT_EQUAL(0, strcmp("Rising", trend));
}

void test_get_temperature_trend_falling_with_negative_values(void) {
    const char* trend = get_temperature_trend(-10.0f, -5.0f);
    TEST_ASSERT_EQUAL(0, strcmp("Falling", trend));
}

void test_get_temperature_trend_stable_with_negative_values(void) {
    const char* trend = get_temperature_trend(-10.0f, -10.0f);
    TEST_ASSERT_EQUAL(0, strcmp("Stable", trend));
}

void test_get_temperature_trend_rising_across_zero(void) {
    const char* trend = get_temperature_trend(2.0f, -2.0f);
    TEST_ASSERT_EQUAL(0, strcmp("Rising", trend));
}

// Main function to run all the tests
int main(void) {
    UNITY_BEGIN();

    // Run tests for calculate_temperature_difference
    RUN_TEST(test_calculate_temperature_difference_positive_result);
    RUN_TEST(test_calculate_temperature_difference_negative_result_is_absolute);
    RUN_TEST(test_calculate_temperature_difference_zero_difference);
    RUN_TEST(test_calculate_temperature_difference_with_negative_temperatures);
    RUN_TEST(test_calculate_temperature_difference_across_zero);
    RUN_TEST(test_calculate_temperature_difference_with_fractional_values);

    // Run tests for is_temperature_stable
    RUN_TEST(test_is_temperature_stable_when_difference_is_small);
    RUN_TEST(test_is_temperature_stable_at_boundary);
    RUN_TEST(test_is_temperature_stable_just_outside_boundary);
    RUN_TEST(test_is_temperature_stable_for_zero_difference);
    RUN_TEST(test_is_temperature_stable_with_large_difference);
    RUN_TEST(test_is_temperature_stable_with_negative_values_within_limit);
    RUN_TEST(test_is_temperature_stable_with_negative_values_outside_limit);

    // Run tests for get_temperature_trend
    RUN_TEST(test_get_temperature_trend_rising);
    RUN_TEST(test_get_temperature_trend_falling);
    RUN_TEST(test_get_temperature_trend_stable);
    RUN_TEST(test_get_temperature_trend_rising_with_negative_values);
    RUN_TEST(test_get_temperature_trend_falling_with_negative_values);
    RUN_TEST(test_get_temperature_trend_stable_with_negative_values);
    RUN_TEST(test_get_temperature_trend_rising_across_zero);

    return UNITY_END();
}
