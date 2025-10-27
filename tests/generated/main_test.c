
#include "unity.h"
#include "temperature_sensor.h"
#include "temperature_utils.h"
#include <string.h>

// Define a small delta for float comparisons
#define FLOAT_DELTA 0.001f

// setUp and tearDown can be empty if not needed
void setUp(void) {
    // set up code, if any
}

void tearDown(void) {
    // clean up code, if any
}

//--- Tests for temperature_utils.h ---

// Tests for calculate_temperature_difference
void test_calculate_temperature_difference_positive_values(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 5.0f, calculate_temperature_difference(10.0f, 5.0f));
}

void test_calculate_temperature_difference_order_independent(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 5.0f, calculate_temperature_difference(5.0f, 10.0f));
}

void test_calculate_temperature_difference_zero_difference(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 0.0f, calculate_temperature_difference(10.0f, 10.0f));
}

void test_calculate_temperature_difference_with_negative_values(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 10.0f, calculate_temperature_difference(-5.0f, 5.0f));
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 5.0f, calculate_temperature_difference(-5.0f, -10.0f));
}

// Tests for is_temperature_stable (assuming stability threshold is 0.5)
void test_is_temperature_stable_within_threshold(void) {
    TEST_ASSERT_TRUE(is_temperature_stable(25.1f, 25.0f));
    TEST_ASSERT_TRUE(is_temperature_stable(24.9f, 25.0f));
}

void test_is_temperature_stable_at_threshold(void) {
    TEST_ASSERT_TRUE(is_temperature_stable(25.5f, 25.0f));
    TEST_ASSERT_TRUE(is_temperature_stable(24.5f, 25.0f));
}

void test_is_temperature_stable_outside_threshold(void) {
    TEST_ASSERT_FALSE(is_temperature_stable(25.6f, 25.0f));
    TEST_ASSERT_FALSE(is_temperature_stable(24.4f, 25.0f));
}

void test_is_temperature_stable_no_change(void) {
    TEST_ASSERT_TRUE(is_temperature_stable(25.0f, 25.0f));
}

// Tests for get_temperature_trend
void test_get_temperature_trend_rising(void) {
    const char* trend = get_temperature_trend(25.1f, 25.0f);
    TEST_ASSERT_NOT_NULL(trend);
    TEST_ASSERT_EQUAL(0, strcmp("Rising", trend));
}

void test_get_temperature_trend_falling(void) {
    const char* trend = get_temperature_trend(24.9f, 25.0f);
    TEST_ASSERT_NOT_NULL(trend);
    TEST_ASSERT_EQUAL(0, strcmp("Falling", trend));
}

void test_get_temperature_trend_stable(void) {
    const char* trend = get_temperature_trend(25.0f, 25.0f);
    TEST_ASSERT_NOT_NULL(trend);
    TEST_ASSERT_EQUAL(0, strcmp("Stable", trend));
}

//--- Tests for temperature_sensor.h ---

// Tests for is_temperature_safe (assuming safe range is 0 to 100 C)
void test_is_temperature_safe_within_range(void) {
    TEST_ASSERT_TRUE(is_temperature_safe(50.0f));
}

void test_is_temperature_safe_at_boundaries(void) {
    TEST_ASSERT_TRUE(is_temperature_safe(0.0f));
    TEST_ASSERT_TRUE(is_temperature_safe(100.0f));
}

void test_is_temperature_safe_outside_range(void) {
    TEST_ASSERT_FALSE(is_temperature_safe(-0.1f));
    TEST_ASSERT_FALSE(is_temperature_safe(100.1f));
}

// Tests for celsius_to_fahrenheit
void test_celsius_to_fahrenheit_freezing_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 32.0f, celsius_to_fahrenheit(0.0f));
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 212.0f, celsius_to_fahrenheit(100.0f));
}

void test_celsius_to_fahrenheit_crossover_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, -40.0f, celsius_to_fahrenheit(-40.0f));
}

// Tests for fahrenheit_to_celsius
void test_fahrenheit_to_celsius_freezing_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 0.0f, fahrenheit_to_celsius(32.0f));
}

void test_fahrenheit_to_celsius_boiling_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 100.0f, fahrenheit_to_celsius(212.0f));
}

void test_fahrenheit_to_celsius_crossover_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, -40.0f, fahrenheit_to_celsius(-40.0f));
}

// Tests for celsius_to_kelvin
void test_celsius_to_kelvin_absolute_zero(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 0.0f, celsius_to_kelvin(-273.15f));
}

void test_celsius_to_kelvin_freezing_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 273.15f, celsius_to_kelvin(0.0f));
}

// Tests for kelvin_to_celsius
void test_kelvin_to_celsius_absolute_zero(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, -273.15f, kelvin_to_celsius(0.0f));
}

void test_kelvin_to_celsius_freezing_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 0.0f, kelvin_to_celsius(273.15f));
}

// Tests for get_temperature_status (assuming Cold < 10, Normal 10-30, Hot > 30)
void test_get_temperature_status_cold(void) {
    const char* status = get_temperature_status(5.0f);
    TEST_ASSERT_NOT_NULL(status);
    TEST_ASSERT_EQUAL(0, strcmp("Cold", status));
}

void test_get_temperature_status_cold_boundary(void) {
    const char* status = get_temperature_status(9.99f);
    TEST_ASSERT_NOT_NULL(status);
    TEST_ASSERT_EQUAL(0, strcmp("Cold", status));
}

void test_get_temperature_status_normal(void) {
    const char* status = get_temperature_status(20.0f);
    TEST_ASSERT_NOT_NULL(status);
    TEST_ASSERT_EQUAL(0, strcmp("Normal", status));
}

void test_get_temperature_status_normal_lower_boundary(void) {
    const char* status = get_temperature_status(10.0f);
    TEST_ASSERT_NOT_NULL(status);
    TEST_ASSERT_EQUAL(0, strcmp("Normal", status));
}

void test_get_temperature_status_normal_upper_boundary(void) {
    const char* status = get_temperature_status(30.0f);
    TEST_ASSERT_NOT_NULL(status);
    TEST_ASSERT_EQUAL(0, strcmp("Normal", status));
}

void test_get_temperature_status_hot(void) {
    const char* status = get_temperature_status(40.0f);
    TEST_ASSERT_NOT_NULL(status);
    TEST_ASSERT_EQUAL(0, strcmp("Hot", status));
}

void test_get_temperature_status_hot_boundary(void) {
    const char* status = get_temperature_status(30.01f);
    TEST_ASSERT_NOT_NULL(status);
    TEST_ASSERT_EQUAL(0, strcmp("Hot", status));
}

// Main function to run the tests
int main(void) {
    UNITY_BEGIN();

    // temperature_utils.h tests
    RUN_TEST(test_calculate_temperature_difference_positive_values);
    RUN_TEST(test_calculate_temperature_difference_order_independent);
    RUN_TEST(test_calculate_temperature_difference_zero_difference);
    RUN_TEST(test_calculate_temperature_difference_with_negative_values);
    
    RUN_TEST(test_is_temperature_stable_within_threshold);
    RUN_TEST(test_is_temperature_stable_at_threshold);
    RUN_TEST(test_is_temperature_stable_outside_threshold);
    RUN_TEST(test_is_temperature_stable_no_change);
    
    RUN_TEST(test_get_temperature_trend_rising);
    RUN_TEST(test_get_temperature_trend_falling);
    RUN_TEST(test_get_temperature_trend_stable);
    
    // temperature_sensor.h tests
    RUN_TEST(test_is_temperature_safe_within_range);
    RUN_TEST(test_is_temperature_safe_at_boundaries);
    RUN_TEST(test_is_temperature_safe_outside_range);
    
    RUN_TEST(test_celsius_to_fahrenheit_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_crossover_point);

    RUN_TEST(test_fahrenheit_to_celsius_freezing_point);
    RUN_TEST(test_fahrenheit_to_celsius_boiling_point);
    RUN_TEST(test_fahrenheit_to_celsius_crossover_point);

    RUN_TEST(test_celsius_to_kelvin_absolute_zero);
    RUN_TEST(test_celsius_to_kelvin_freezing_point);
    
    RUN_TEST(test_kelvin_to_celsius_absolute_zero);
    RUN_TEST(test_kelvin_to_celsius_freezing_point);
    
    RUN_TEST(test_get_temperature_status_cold);
    RUN_TEST(test_get_temperature_status_cold_boundary);
    RUN_TEST(test_get_temperature_status_normal);
    RUN_TEST(test_get_temperature_status_normal_lower_boundary);
    RUN_TEST(test_get_temperature_status_normal_upper_boundary);
    RUN_TEST(test_get_temperature_status_hot);
    RUN_TEST(test_get_temperature_status_hot_boundary);

    return UNITY_END();
}
