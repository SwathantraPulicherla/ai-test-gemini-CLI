
#include "unity.h"
#include "temperature_sensor.h"
#include "temperature_utils.h"
#include <string.h>

// Precision for float comparisons
#define FLOAT_PRECISION 0.001f

// setUp and tearDown functions
void setUp(void) {
    // This function is called before each test
}

void tearDown(void) {
    // This function is called after each test
}

//================================================================================
// Test Functions for temperature_utils.h
//================================================================================

// Tests for calculate_temperature_difference
void test_calculate_temperature_difference_positive(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 5.5f, calculate_temperature_difference(25.5f, 20.0f));
}

void test_calculate_temperature_difference_swapped_args(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 5.5f, calculate_temperature_difference(20.0f, 25.5f));
}

void test_calculate_temperature_difference_with_negative(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 15.0f, calculate_temperature_difference(-5.0f, 10.0f));
}

void test_calculate_temperature_difference_both_negative(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 5.0f, calculate_temperature_difference(-10.0f, -5.0f));
}

void test_calculate_temperature_difference_zero(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 0.0f, calculate_temperature_difference(30.0f, 30.0f));
}

// Tests for is_temperature_stable
// Assuming stability threshold is <= 0.5f difference
void test_is_temperature_stable_true(void) {
    TEST_ASSERT_TRUE(is_temperature_stable(25.2f, 25.0f));
}

void test_is_temperature_stable_at_threshold(void) {
    TEST_ASSERT_TRUE(is_temperature_stable(25.5f, 25.0f));
}

void test_is_temperature_stable_false(void) {
    TEST_ASSERT_FALSE(is_temperature_stable(26.0f, 25.0f));
}

void test_is_temperature_stable_identical(void) {
    TEST_ASSERT_TRUE(is_temperature_stable(25.0f, 25.0f));
}

void test_is_temperature_stable_negative_temps(void) {
    TEST_ASSERT_TRUE(is_temperature_stable(-10.0f, -10.4f));
    TEST_ASSERT_FALSE(is_temperature_stable(-10.0f, -11.0f));
}

// Tests for get_temperature_trend
// Assuming "Stable" is for identical temps, otherwise "Rising" or "Falling"
void test_get_temperature_trend_rising(void) {
    const char* trend = get_temperature_trend(25.5f, 25.0f);
    TEST_ASSERT_NOT_NULL(trend);
    TEST_ASSERT_EQUAL(0, strcmp("Rising", trend));
}

void test_get_temperature_trend_falling(void) {
    const char* trend = get_temperature_trend(24.5f, 25.0f);
    TEST_ASSERT_NOT_NULL(trend);
    TEST_ASSERT_EQUAL(0, strcmp("Falling", trend));
}

void test_get_temperature_trend_stable(void) {
    const char* trend = get_temperature_trend(25.0f, 25.0f);
    TEST_ASSERT_NOT_NULL(trend);
    TEST_ASSERT_EQUAL(0, strcmp("Stable", trend));
}

//================================================================================
// Test Functions for temperature_sensor.h
//================================================================================

// Test for get_temperature
void test_get_temperature_plausible_range(void) {
    // Cannot test exact value, but can test if it's within a reasonable range
    float temp = get_temperature();
    TEST_ASSERT_TRUE(temp >= -100.0f && temp <= 200.0f);
}

// Tests for is_temperature_safe
// Assuming safe range is 0.0f to 85.0f inclusive
void test_is_temperature_safe_within_range(void) {
    TEST_ASSERT_TRUE(is_temperature_safe(25.0f));
}

void test_is_temperature_safe_lower_boundary(void) {
    TEST_ASSERT_TRUE(is_temperature_safe(0.0f));
}

void test_is_temperature_safe_upper_boundary(void) {
    TEST_ASSERT_TRUE(is_temperature_safe(85.0f));
}

void test_is_temperature_safe_below_range(void) {
    TEST_ASSERT_FALSE(is_temperature_safe(-0.1f));
}

void test_is_temperature_safe_above_range(void) {
    TEST_ASSERT_FALSE(is_temperature_safe(85.1f));
}

// Tests for celsius_to_fahrenheit
void test_celsius_to_fahrenheit_freezing(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 32.0f, celsius_to_fahrenheit(0.0f));
}

void test_celsius_to_fahrenheit_boiling(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 212.0f, celsius_to_fahrenheit(100.0f));
}

void test_celsius_to_fahrenheit_body_temp(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 98.6f, celsius_to_fahrenheit(37.0f));
}

void test_celsius_to_fahrenheit_negative(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, -40.0f, celsius_to_fahrenheit(-40.0f));
}

// Tests for fahrenheit_to_celsius
void test_fahrenheit_to_celsius_freezing(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 0.0f, fahrenheit_to_celsius(32.0f));
}

void test_fahrenheit_to_celsius_boiling(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 100.0f, fahrenheit_to_celsius(212.0f));
}

void test_fahrenheit_to_celsius_body_temp(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 37.0f, fahrenheit_to_celsius(98.6f));
}

void test_fahrenheit_to_celsius_negative(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, -40.0f, fahrenheit_to_celsius(-40.0f));
}

// Tests for celsius_to_kelvin
void test_celsius_to_kelvin_absolute_zero(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 0.0f, celsius_to_kelvin(-273.15f));
}

void test_celsius_to_kelvin_freezing(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 273.15f, celsius_to_kelvin(0.0f));
}

void test_celsius_to_kelvin_positive(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 373.15f, celsius_to_kelvin(100.0f));
}

// Tests for kelvin_to_celsius
void test_kelvin_to_celsius_absolute_zero(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, -273.15f, kelvin_to_celsius(0.0f));
}

void test_kelvin_to_celsius_freezing(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 0.0f, kelvin_to_celsius(273.15f));
}

void test_kelvin_to_celsius_positive(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 100.0f, kelvin_to_celsius(373.15f));
}

// Tests for get_temperature_status
// Assuming: <10 "Cold", 10-30 "Normal", >30 "Hot"
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
    const char* status = get_temperature_status(45.0f);
    TEST_ASSERT_NOT_NULL(status);
    TEST_ASSERT_EQUAL(0, strcmp("Hot", status));
}

void test_get_temperature_status_hot_boundary(void) {
    const char* status = get_temperature_status(30.01f);
    TEST_ASSERT_NOT_NULL(status);
    TEST_ASSERT_EQUAL(0, strcmp("Hot", status));
}

// Main function to run all tests
int main(void) {
    UNITY_BEGIN();

    // Tests for temperature_utils.h
    RUN_TEST(test_calculate_temperature_difference_positive);
    RUN_TEST(test_calculate_temperature_difference_swapped_args);
    RUN_TEST(test_calculate_temperature_difference_with_negative);
    RUN_TEST(test_calculate_temperature_difference_both_negative);
    RUN_TEST(test_calculate_temperature_difference_zero);
    RUN_TEST(test_is_temperature_stable_true);
    RUN_TEST(test_is_temperature_stable_at_threshold);
    RUN_TEST(test_is_temperature_stable_false);
    RUN_TEST(test_is_temperature_stable_identical);
    RUN_TEST(test_is_temperature_stable_negative_temps);
    RUN_TEST(test_get_temperature_trend_rising);
    RUN_TEST(test_get_temperature_trend_falling);
    RUN_TEST(test_get_temperature_trend_stable);
    
    // Tests for temperature_sensor.h
    RUN_TEST(test_get_temperature_plausible_range);
    RUN_TEST(test_is_temperature_safe_within_range);
    RUN_TEST(test_is_temperature_safe_lower_boundary);
    RUN_TEST(test_is_temperature_safe_upper_boundary);
    RUN_TEST(test_is_temperature_safe_below_range);
    RUN_TEST(test_is_temperature_safe_above_range);
    RUN_TEST(test_celsius_to_fahrenheit_freezing);
    RUN_TEST(test_celsius_to_fahrenheit_boiling);
    RUN_TEST(test_celsius_to_fahrenheit_body_temp);
    RUN_TEST(test_celsius_to_fahrenheit_negative);
    RUN_TEST(test_fahrenheit_to_celsius_freezing);
    RUN_TEST(test_fahrenheit_to_celsius_boiling);
    RUN_TEST(test_fahrenheit_to_celsius_body_temp);
    RUN_TEST(test_fahrenheit_to_celsius_negative);
    RUN_TEST(test_celsius_to_kelvin_absolute_zero);
    RUN_TEST(test_celsius_to_kelvin_freezing);
    RUN_TEST(test_celsius_to_kelvin_positive);
    RUN_TEST(test_kelvin_to_celsius_absolute_zero);
    RUN_TEST(test_kelvin_to_celsius_freezing);
    RUN_TEST(test_kelvin_to_celsius_positive);
    RUN_TEST(test_get_temperature_status_cold);
    RUN_TEST(test_get_temperature_status_cold_boundary);
    RUN_TEST(test_get_temperature_status_normal_lower_boundary);
    RUN_TEST(test_get_temperature_status_normal_upper_boundary);
    RUN_TEST(test_get_temperature_status_hot);
    RUN_TEST(test_get_temperature_status_hot_boundary);

    return UNITY_END();
}
