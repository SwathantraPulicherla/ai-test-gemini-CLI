
#include "unity.h"
#include "temperature_sensor.h"
#include "temperature_utils.h"
#include <string.h>

// Precision for float comparisons
#define FLOAT_PRECISION 0.001f

void setUp(void) {
    // This is run before EACH test
}

void tearDown(void) {
    // This is run after EACH test
}

// =================================================================
// Tests for temperature_sensor.h
// =================================================================

// --- Tests for celsius_to_fahrenheit ---
void test_celsius_to_fahrenheit_zero_celsius(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 32.0f, celsius_to_fahrenheit(0.0f));
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 212.0f, celsius_to_fahrenheit(100.0f));
}

void test_celsius_to_fahrenheit_negative_crossover(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, -40.0f, celsius_to_fahrenheit(-40.0f));
}

void test_celsius_to_fahrenheit_normal_temp(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 68.0f, celsius_to_fahrenheit(20.0f));
}

// --- Tests for fahrenheit_to_celsius ---
void test_fahrenheit_to_celsius_freezing_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 0.0f, fahrenheit_to_celsius(32.0f));
}

void test_fahrenheit_to_celsius_boiling_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 100.0f, fahrenheit_to_celsius(212.0f));
}

void test_fahrenheit_to_celsius_negative_crossover(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, -40.0f, fahrenheit_to_celsius(-40.0f));
}

void test_fahrenheit_to_celsius_normal_temp(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 20.0f, fahrenheit_to_celsius(68.0f));
}

// --- Tests for celsius_to_kelvin ---
void test_celsius_to_kelvin_absolute_zero(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 0.0f, celsius_to_kelvin(-273.15f));
}

void test_celsius_to_kelvin_freezing_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 273.15f, celsius_to_kelvin(0.0f));
}

void test_celsius_to_kelvin_boiling_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 373.15f, celsius_to_kelvin(100.0f));
}

// --- Tests for kelvin_to_celsius ---
void test_kelvin_to_celsius_absolute_zero(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, -273.15f, kelvin_to_celsius(0.0f));
}

void test_kelvin_to_celsius_freezing_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 0.0f, kelvin_to_celsius(273.15f));
}

void test_kelvin_to_celsius_boiling_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 100.0f, kelvin_to_celsius(373.15f));
}

// --- Tests for is_temperature_safe ---
// Assuming safe range is [0, 100] degrees Celsius for these tests
void test_is_temperature_safe_within_range(void) {
    TEST_ASSERT_TRUE(is_temperature_safe(25.0f));
}

void test_is_temperature_safe_lower_boundary(void) {
    TEST_ASSERT_TRUE(is_temperature_safe(0.0f));
}

void test_is_temperature_safe_upper_boundary(void) {
    TEST_ASSERT_TRUE(is_temperature_safe(100.0f));
}

void test_is_temperature_safe_below_lower_boundary(void) {
    TEST_ASSERT_FALSE(is_temperature_safe(-0.1f));
}

void test_is_temperature_safe_above_upper_boundary(void) {
    TEST_ASSERT_FALSE(is_temperature_safe(100.1f));
}

// --- Tests for get_temperature_status ---
// Assuming ranges: <0 "Freezing", [0, 15) "Cold", [15, 25) "Normal", [25, 35) "Warm", >=35 "Hot"
void test_get_temperature_status_freezing(void) {
    const char* status = get_temperature_status(-10.5f);
    TEST_ASSERT_NOT_NULL(status);
    TEST_ASSERT_EQUAL(0, strcmp("Freezing", status));
}

void test_get_temperature_status_cold_boundary(void) {
    const char* status = get_temperature_status(0.0f);
    TEST_ASSERT_NOT_NULL(status);
    TEST_ASSERT_EQUAL(0, strcmp("Cold", status));
}

void test_get_temperature_status_cold(void) {
    const char* status = get_temperature_status(14.9f);
    TEST_ASSERT_NOT_NULL(status);
    TEST_ASSERT_EQUAL(0, strcmp("Cold", status));
}

void test_get_temperature_status_normal_boundary(void) {
    const char* status = get_temperature_status(15.0f);
    TEST_ASSERT_NOT_NULL(status);
    TEST_ASSERT_EQUAL(0, strcmp("Normal", status));
}

void test_get_temperature_status_warm_boundary(void) {
    const char* status = get_temperature_status(25.0f);
    TEST_ASSERT_NOT_NULL(status);
    TEST_ASSERT_EQUAL(0, strcmp("Warm", status));
}

void test_get_temperature_status_hot_boundary(void) {
    const char* status = get_temperature_status(35.0f);
    TEST_ASSERT_NOT_NULL(status);
    TEST_ASSERT_EQUAL(0, strcmp("Hot", status));
}

// =================================================================
// Tests for temperature_utils.h
// =================================================================

// --- Tests for calculate_temperature_difference ---
void test_calculate_temperature_difference_positive_temps(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 5.5f, calculate_temperature_difference(25.5f, 20.0f));
}

void test_calculate_temperature_difference_positive_temps_swapped(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 5.5f, calculate_temperature_difference(20.0f, 25.5f));
}

void test_calculate_temperature_difference_no_difference(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 0.0f, calculate_temperature_difference(20.0f, 20.0f));
}

void test_calculate_temperature_difference_negative_temps(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 5.0f, calculate_temperature_difference(-5.0f, -10.0f));
}

void test_calculate_temperature_difference_mixed_sign_temps(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 10.0f, calculate_temperature_difference(-5.0f, 5.0f));
}

// --- Tests for is_temperature_stable ---
// Assuming stable if absolute difference <= 0.5 for these tests
void test_is_temperature_stable_is_stable_below_threshold(void) {
    TEST_ASSERT_TRUE(is_temperature_stable(20.2f, 20.0f));
}

void test_is_temperature_stable_is_stable_at_threshold(void) {
    TEST_ASSERT_TRUE(is_temperature_stable(20.5f, 20.0f));
}

void test_is_temperature_stable_is_unstable_above_threshold(void) {
    TEST_ASSERT_FALSE(is_temperature_stable(20.6f, 20.0f));
}

void test_is_temperature_stable_no_change(void) {
    TEST_ASSERT_TRUE(is_temperature_stable(20.0f, 20.0f));
}

// --- Tests for get_temperature_trend ---
// Assuming "Stable" if difference <= 0.1, otherwise "Rising" or "Falling" for these tests
void test_get_temperature_trend_rising(void) {
    const char* trend = get_temperature_trend(20.5f, 20.0f);
    TEST_ASSERT_NOT_NULL(trend);
    TEST_ASSERT_EQUAL(0, strcmp("Rising", trend));
}

void test_get_temperature_trend_falling(void) {
    const char* trend = get_temperature_trend(19.5f, 20.0f);
    TEST_ASSERT_NOT_NULL(trend);
    TEST_ASSERT_EQUAL(0, strcmp("Falling", trend));
}

void test_get_temperature_trend_stable_no_change(void) {
    const char* trend = get_temperature_trend(20.0f, 20.0f);
    TEST_ASSERT_NOT_NULL(trend);
    TEST_ASSERT_EQUAL(0, strcmp("Stable", trend));
}

void test_get_temperature_trend_stable_at_threshold(void) {
    const char* trend = get_temperature_trend(20.1f, 20.0f);
    TEST_ASSERT_NOT_NULL(trend);
    TEST_ASSERT_EQUAL(0, strcmp("Stable", trend));
}

void test_get_temperature_trend_rising_above_threshold(void) {
    const char* trend = get_temperature_trend(20.11f, 20.0f);
    TEST_ASSERT_NOT_NULL(trend);
    TEST_ASSERT_EQUAL(0, strcmp("Rising", trend));
}

void test_get_temperature_trend_falling_below_threshold(void) {
    const char* trend = get_temperature_trend(19.89f, 20.0f);
    TEST_ASSERT_NOT_NULL(trend);
    TEST_ASSERT_EQUAL(0, strcmp("Falling", trend));
}


int main(void) {
    UNITY_BEGIN();

    // Run tests for temperature_sensor.h
    RUN_TEST(test_celsius_to_fahrenheit_zero_celsius);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_negative_crossover);
    RUN_TEST(test_celsius_to_fahrenheit_normal_temp);
    RUN_TEST(test_fahrenheit_to_celsius_freezing_point);
    RUN_TEST(test_fahrenheit_to_celsius_boiling_point);
    RUN_TEST(test_fahrenheit_to_celsius_negative_crossover);
    RUN_TEST(test_fahrenheit_to_celsius_normal_temp);
    RUN_TEST(test_celsius_to_kelvin_absolute_zero);
    RUN_TEST(test_celsius_to_kelvin_freezing_point);
    RUN_TEST(test_celsius_to_kelvin_boiling_point);
    RUN_TEST(test_kelvin_to_celsius_absolute_zero);
    RUN_TEST(test_kelvin_to_celsius_freezing_point);
    RUN_TEST(test_kelvin_to_celsius_boiling_point);
    RUN_TEST(test_is_temperature_safe_within_range);
    RUN_TEST(test_is_temperature_safe_lower_boundary);
    RUN_TEST(test_is_temperature_safe_upper_boundary);
    RUN_TEST(test_is_temperature_safe_below_lower_boundary);
    RUN_TEST(test_is_temperature_safe_above_upper_boundary);
    RUN_TEST(test_get_temperature_status_freezing);
    RUN_TEST(test_get_temperature_status_cold_boundary);
    RUN_TEST(test_get_temperature_status_cold);
    RUN_TEST(test_get_temperature_status_normal_boundary);
    RUN_TEST(test_get_temperature_status_warm_boundary);
    RUN_TEST(test_get_temperature_status_hot_boundary);
    
    // Run tests for temperature_utils.h
    RUN_TEST(test_calculate_temperature_difference_positive_temps);
    RUN_TEST(test_calculate_temperature_difference_positive_temps_swapped);
    RUN_TEST(test_calculate_temperature_difference_no_difference);
    RUN_TEST(test_calculate_temperature_difference_negative_temps);
    RUN_TEST(test_calculate_temperature_difference_mixed_sign_temps);
    RUN_TEST(test_is_temperature_stable_is_stable_below_threshold);
    RUN_TEST(test_is_temperature_stable_is_stable_at_threshold);
    RUN_TEST(test_is_temperature_stable_is_unstable_above_threshold);
    RUN_TEST(test_is_temperature_stable_no_change);
    RUN_TEST(test_get_temperature_trend_rising);
    RUN_TEST(test_get_temperature_trend_falling);
    RUN_TEST(test_get_temperature_trend_stable_no_change);
    RUN_TEST(test_get_temperature_trend_stable_at_threshold);
    RUN_TEST(test_get_temperature_trend_rising_above_threshold);
    RUN_TEST(test_get_temperature_trend_falling_below_threshold);

    return UNITY_END();
}
