
#include "unity.h"
#include "temperature_utils.h"
#include <string.h>

void setUp(void) {
    // Set up code, if any
}

void tearDown(void) {
    // Clean up code, if any
}

// Tests for calculate_temperature_difference
void test_calculate_temperature_difference_positive_values(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 5.0f, calculate_temperature_difference(25.0f, 20.0f));
}

void test_calculate_temperature_difference_order_swapped(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 5.0f, calculate_temperature_difference(20.0f, 25.0f));
}

void test_calculate_temperature_difference_no_difference(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, calculate_temperature_difference(22.5f, 22.5f));
}

void test_calculate_temperature_difference_with_negative_value(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 15.0f, calculate_temperature_difference(-10.0f, 5.0f));
}

void test_calculate_temperature_difference_both_negative(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 5.0f, calculate_temperature_difference(-10.0f, -15.0f));
}

void test_calculate_temperature_difference_with_zero(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 10.0f, calculate_temperature_difference(10.0f, 0.0f));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 10.0f, calculate_temperature_difference(0.0f, -10.0f));
}


// Tests for is_temperature_stable
void test_is_temperature_stable_within_threshold(void) {
    // Difference is 4.0, which is <= 5.0
    TEST_ASSERT_TRUE(is_temperature_stable(24.0f, 20.0f));
}

void test_is_temperature_stable_at_boundary(void) {
    // Difference is exactly 5.0, which is <= 5.0
    TEST_ASSERT_TRUE(is_temperature_stable(25.0f, 20.0f));
    TEST_ASSERT_TRUE(is_temperature_stable(20.0f, 25.0f));
}

void test_is_temperature_stable_just_outside_boundary(void) {
    // Difference is 5.001, which is > 5.0
    TEST_ASSERT_FALSE(is_temperature_stable(25.001f, 20.0f));
}

void test_is_temperature_stable_well_outside_threshold(void) {
    // Difference is 10.0, which is > 5.0
    TEST_ASSERT_FALSE(is_temperature_stable(30.0f, 20.0f));
}

void test_is_temperature_stable_no_change(void) {
    // Difference is 0.0, which is <= 5.0
    TEST_ASSERT_TRUE(is_temperature_stable(22.0f, 22.0f));
}

void test_is_temperature_stable_negative_values(void) {
    // Difference is 4.0, which is <= 5.0
    TEST_ASSERT_TRUE(is_temperature_stable(-2.0f, 2.0f));
    // Difference is 6.0, which is > 5.0
    TEST_ASSERT_FALSE(is_temperature_stable(-10.0f, -4.0f));
}

// Tests for get_temperature_trend
void test_get_temperature_trend_rising(void) {
    const char* trend = get_temperature_trend(25.0f, 20.0f);
    TEST_ASSERT_EQUAL(0, strcmp("Rising", trend));
}

void test_get_temperature_trend_falling(void) {
    const char* trend = get_temperature_trend(20.0f, 25.0f);
    TEST_ASSERT_EQUAL(0, strcmp("Falling", trend));
}

void test_get_temperature_trend_stable(void) {
    const char* trend = get_temperature_trend(20.0f, 20.0f);
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

void test_get_temperature_trend_crossing_zero(void) {
    const char* rising_trend = get_temperature_trend(2.0f, -2.0f);
    const char* falling_trend = get_temperature_trend(-2.0f, 2.0f);
    TEST_ASSERT_EQUAL(0, strcmp("Rising", rising_trend));
    TEST_ASSERT_EQUAL(0, strcmp("Falling", falling_trend));
}

int main(void) {
    UNITY_BEGIN();

    // Run tests for calculate_temperature_difference
    RUN_TEST(test_calculate_temperature_difference_positive_values);
    RUN_TEST(test_calculate_temperature_difference_order_swapped);
    RUN_TEST(test_calculate_temperature_difference_no_difference);
    RUN_TEST(test_calculate_temperature_difference_with_negative_value);
    RUN_TEST(test_calculate_temperature_difference_both_negative);
    RUN_TEST(test_calculate_temperature_difference_with_zero);

    // Run tests for is_temperature_stable
    RUN_TEST(test_is_temperature_stable_within_threshold);
    RUN_TEST(test_is_temperature_stable_at_boundary);
    RUN_TEST(test_is_temperature_stable_just_outside_boundary);
    RUN_TEST(test_is_temperature_stable_well_outside_threshold);
    RUN_TEST(test_is_temperature_stable_no_change);
    RUN_TEST(test_is_temperature_stable_negative_values);

    // Run tests for get_temperature_trend
    RUN_TEST(test_get_temperature_trend_rising);
    RUN_TEST(test_get_temperature_trend_falling);
    RUN_TEST(test_get_temperature_trend_stable);
    RUN_TEST(test_get_temperature_trend_rising_with_negative_values);
    RUN_TEST(test_get_temperature_trend_falling_with_negative_values);
    RUN_TEST(test_get_temperature_trend_stable_with_negative_values);
    RUN_TEST(test_get_temperature_trend_crossing_zero);

    return UNITY_END();
}
