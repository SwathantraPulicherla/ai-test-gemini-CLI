
#include "unity.h"
#include "temperature_utils.h"
#include <string.h>

// setUp and tearDown functions can be used for test setup and cleanup.
void setUp(void) {
    // This function is called before each test.
}

void tearDown(void) {
    // This function is called after each test.
}

//================================================================================
// Test suite for calculate_temperature_difference
//================================================================================

// Test with temp1 > temp2, expecting a positive difference
void test_calculate_temperature_difference_positive_result(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 5.5f, calculate_temperature_difference(25.5f, 20.0f));
}

// Test with temp2 > temp1, expecting a positive (absolute) difference
void test_calculate_temperature_difference_negative_input_should_be_absolute(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 5.5f, calculate_temperature_difference(20.0f, 25.5f));
}

// Test with equal temperatures, expecting zero difference
void test_calculate_temperature_difference_zero_difference(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, calculate_temperature_difference(22.0f, 22.0f));
}

// Test with two negative temperatures
void test_calculate_temperature_difference_with_negative_temperatures(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 5.0f, calculate_temperature_difference(-5.0f, -10.0f));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 5.0f, calculate_temperature_difference(-10.0f, -5.0f));
}

// Test with one positive and one negative temperature
void test_calculate_temperature_difference_with_mixed_sign_temperatures(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 10.0f, calculate_temperature_difference(5.0f, -5.0f));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 10.0f, calculate_temperature_difference(-5.0f, 5.0f));
}

// Test with a temperature and zero
void test_calculate_temperature_difference_with_zero(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 10.0f, calculate_temperature_difference(10.0f, 0.0f));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 10.0f, calculate_temperature_difference(0.0f, 10.0f));
}

//================================================================================
// Test suite for is_temperature_stable
//================================================================================

// Test when difference is less than the 5.0 threshold
void test_is_temperature_stable_within_limit(void) {
    TEST_ASSERT_EQUAL(1, is_temperature_stable(24.9f, 20.0f));
}

// Test when difference is exactly at the 5.0 threshold (boundary condition)
void test_is_temperature_stable_at_upper_boundary(void) {
    TEST_ASSERT_EQUAL(1, is_temperature_stable(25.0f, 20.0f));
}

// Test when difference is just over the 5.0 threshold (boundary condition)
void test_is_temperature_stable_just_over_limit(void) {
    TEST_ASSERT_EQUAL(0, is_temperature_stable(25.001f, 20.0f));
}

// Test with no temperature change
void test_is_temperature_stable_zero_difference(void) {
    TEST_ASSERT_EQUAL(1, is_temperature_stable(22.0f, 22.0f));
}

// Test with swapped arguments to ensure absolute difference is used
void test_is_temperature_stable_swapped_args_within_limit(void) {
    TEST_ASSERT_EQUAL(1, is_temperature_stable(20.0f, 24.9f));
}

// Test with negative temperatures that are within the stable range
void test_is_temperature_stable_negative_temps_within_limit(void) {
    TEST_ASSERT_EQUAL(1, is_temperature_stable(-10.0f, -14.0f)); // diff = 4.0
}

// Test with negative temperatures that are outside the stable range
void test_is_temperature_stable_negative_temps_over_limit(void) {
    TEST_ASSERT_EQUAL(0, is_temperature_stable(-10.0f, -16.0f)); // diff = 6.0
}

//================================================================================
// Test suite for get_temperature_trend
//================================================================================

// Test for a rising temperature trend
void test_get_temperature_trend_rising(void) {
    const char* trend = get_temperature_trend(25.0f, 20.0f);
    TEST_ASSERT_NOT_NULL(trend);
    TEST_ASSERT_EQUAL(0, strcmp("Rising", trend));
}

// Test for a falling temperature trend
void test_get_temperature_trend_falling(void) {
    const char* trend = get_temperature_trend(20.0f, 25.0f);
    TEST_ASSERT_NOT_NULL(trend);
    TEST_ASSERT_EQUAL(0, strcmp("Falling", trend));
}

// Test for a stable temperature
void test_get_temperature_trend_stable(void) {
    const char* trend = get_temperature_trend(22.0f, 22.0f);
    TEST_ASSERT_NOT_NULL(trend);
    TEST_ASSERT_EQUAL(0, strcmp("Stable", trend));
}

// Test for stable negative temperatures
void test_get_temperature_trend_stable_with_negative_temps(void) {
    const char* trend = get_temperature_trend(-10.0f, -10.0f);
    TEST_ASSERT_NOT_NULL(trend);
    TEST_ASSERT_EQUAL(0, strcmp("Stable", trend));
}

// Test for rising trend with negative temperatures
void test_get_temperature_trend_rising_with_negative_temps(void) {
    const char* trend = get_temperature_trend(-10.0f, -15.0f);
    TEST_ASSERT_NOT_NULL(trend);
    TEST_ASSERT_EQUAL(0, strcmp("Rising", trend));
}

// Test for falling trend with negative temperatures
void test_get_temperature_trend_falling_with_negative_temps(void) {
    const char* trend = get_temperature_trend(-15.0f, -10.0f);
    TEST_ASSERT_NOT_NULL(trend);
    TEST_ASSERT_EQUAL(0, strcmp("Falling", trend));
}

// Test for trend crossing from negative to positive and vice-versa
void test_get_temperature_trend_crossing_zero(void) {
    const char* trend_rising = get_temperature_trend(2.0f, -2.0f);
    TEST_ASSERT_NOT_NULL(trend_rising);
    TEST_ASSERT_EQUAL(0, strcmp("Rising", trend_rising));
    
    const char* trend_falling = get_temperature_trend(-2.0f, 2.0f);
    TEST_ASSERT_NOT_NULL(trend_falling);
    TEST_ASSERT_EQUAL(0, strcmp("Falling", trend_falling));
}

// Main function to run all the tests
int main(void) {
    UNITY_BEGIN();

    // Run tests for calculate_temperature_difference
    RUN_TEST(test_calculate_temperature_difference_positive_result);
    RUN_TEST(test_calculate_temperature_difference_negative_input_should_be_absolute);
    RUN_TEST(test_calculate_temperature_difference_zero_difference);
    RUN_TEST(test_calculate_temperature_difference_with_negative_temperatures);
    RUN_TEST(test_calculate_temperature_difference_with_mixed_sign_temperatures);
    RUN_TEST(test_calculate_temperature_difference_with_zero);

    // Run tests for is_temperature_stable
    RUN_TEST(test_is_temperature_stable_within_limit);
    RUN_TEST(test_is_temperature_stable_at_upper_boundary);
    RUN_TEST(test_is_temperature_stable_just_over_limit);
    RUN_TEST(test_is_temperature_stable_zero_difference);
    RUN_TEST(test_is_temperature_stable_swapped_args_within_limit);
    RUN_TEST(test_is_temperature_stable_negative_temps_within_limit);
    RUN_TEST(test_is_temperature_stable_negative_temps_over_limit);

    // Run tests for get_temperature_trend
    RUN_TEST(test_get_temperature_trend_rising);
    RUN_TEST(test_get_temperature_trend_falling);
    RUN_TEST(test_get_temperature_trend_stable);
    RUN_TEST(test_get_temperature_trend_stable_with_negative_temps);
    RUN_TEST(test_get_temperature_trend_rising_with_negative_temps);
    RUN_TEST(test_get_temperature_trend_falling_with_negative_temps);
    RUN_TEST(test_get_temperature_trend_crossing_zero);
    
    return UNITY_END();
}
