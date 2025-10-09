
#include "unity.h"
#include "temperature_utils.h"
#include "temperature_sensor.h"

// Note: Source code for the functions is not provided.
// Tests are written based on inferred behavior from function names and common use cases.
// Specific thresholds and ranges are assumed for functions like is_temperature_stable,
// is_temperature_safe, get_temperature_trend, and get_temperature_status.

// setUp and tearDown are part of the Unity test framework
void setUp(void) {
    // Set up code, if any, goes here
}

void tearDown(void) {
    // Clean up code, if any, goes here
}

// -------------------- Tests for temperature_utils.h --------------------

// Tests for calculate_temperature_difference
void test_calculate_temperature_difference_positive(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 5.5f, calculate_temperature_difference(25.5f, 20.0f));
}

void test_calculate_temperature_difference_negative(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -5.5f, calculate_temperature_difference(20.0f, 25.5f));
}

void test_calculate_temperature_difference_zero(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, calculate_temperature_difference(22.3f, 22.3f));
}

void test_calculate_temperature_difference_with_negative_numbers(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 5.0f, calculate_temperature_difference(-10.0f, -15.0f));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -25.0f, calculate_temperature_difference(-10.0f, 15.0f));
}

// Tests for is_temperature_stable (assuming stable if |diff| <= 0.5)
void test_is_temperature_stable_when_stable(void) {
    TEST_ASSERT_TRUE(is_temperature_stable(25.1f, 25.4f)); // diff = 0.3
}

void test_is_temperature_stable_when_unstable(void) {
    TEST_ASSERT_FALSE(is_temperature_stable(25.1f, 25.7f)); // diff = 0.6
}

void test_is_temperature_stable_at_boundary_inclusive(void) {
    TEST_ASSERT_TRUE(is_temperature_stable(25.0f, 25.5f)); // diff = 0.5
    TEST_ASSERT_TRUE(is_temperature_stable(25.5f, 25.0f)); // diff = -0.5
}

void test_is_temperature_stable_just_outside_boundary(void) {
    TEST_ASSERT_FALSE(is_temperature_stable(25.0f, 25.51f)); // diff = 0.51
    TEST_ASSERT_FALSE(is_temperature_stable(25.51f, 25.0f)); // diff = -0.51
}

void test_is_temperature_stable_when_identical(void) {
    TEST_ASSERT_TRUE(is_temperature_stable(20.0f, 20.0f));
}

// Tests for get_temperature_trend (assuming "Stable" for |diff| <= 0.5)
void test_get_temperature_trend_rising(void) {
    TEST_ASSERT_EQUAL_STRING("Rising", get_temperature_trend(26.0f, 25.0f));
}

void test_get_temperature_trend_falling(void) {
    TEST_ASSERT_EQUAL_STRING("Falling", get_temperature_trend(24.0f, 25.0f));
}

void test_get_temperature_trend_stable_small_change(void) {
    TEST_ASSERT_EQUAL_STRING("Stable", get_temperature_trend(25.2f, 25.0f));
}

void test_get_temperature_trend_stable_no_change(void) {
    TEST_ASSERT_EQUAL_STRING("Stable", get_temperature_trend(25.0f, 25.0f));
}

void test_get_temperature_trend_stable_at_boundary(void) {
    TEST_ASSERT_EQUAL_STRING("Stable", get_temperature_trend(25.5f, 25.0f));
}

// -------------------- Tests for temperature_sensor.h --------------------

// Test for get_temperature - Since it simulates a sensor, we can't assert a specific value.
// A basic "smoke test" to ensure it returns a value without crashing.
void test_get_temperature_runs_without_error(void) {
    // This is a weak test due to the non-deterministic nature of the function.
    // We just call it to ensure it completes.
    float temp = get_temperature();
    // A sanity check could be to assert it's within a very wide, plausible range.
    TEST_ASSERT_TRUE(temp > -100.0f && temp < 200.0f);
}

// Tests for is_temperature_safe (assuming safe range is 0°C to 50°C inclusive)
void test_is_temperature_safe_within_range(void) {
    TEST_ASSERT_TRUE(is_temperature_safe(25.0f));
}

void test_is_temperature_safe_at_lower_boundary(void) {
    TEST_ASSERT_TRUE(is_temperature_safe(0.0f));
}

void test_is_temperature_safe_at_upper_boundary(void) {
    TEST_ASSERT_TRUE(is_temperature_safe(50.0f));
}

void test_is_temperature_safe_below_range(void) {
    TEST_ASSERT_FALSE(is_temperature_safe(-0.1f));
    TEST_ASSERT_FALSE(is_temperature_safe(-20.0f));
}

void test_is_temperature_safe_above_range(void) {
    TEST_ASSERT_FALSE(is_temperature_safe(50.1f));
    TEST_ASSERT_FALSE(is_temperature_safe(100.0f));
}

// Tests for Celsius to Fahrenheit conversion
void test_celsius_to_fahrenheit_freezing_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 32.0f, celsius_to_fahrenheit(0.0f));
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 212.0f, celsius_to_fahrenheit(100.0f));
}

void test_celsius_to_fahrenheit_body_temperature(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 98.6f, celsius_to_fahrenheit(37.0f));
}

void test_celsius_to_fahrenheit_negative_temperature(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -40.0f, celsius_to_fahrenheit(-40.0f));
}

// Tests for Fahrenheit to Celsius conversion
void test_fahrenheit_to_celsius_freezing_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, fahrenheit_to_celsius(32.0f));
}

void test_fahrenheit_to_celsius_boiling_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 100.0f, fahrenheit_to_celsius(212.0f));
}

void test_fahrenheit_to_celsius_body_temperature(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 37.0f, fahrenheit_to_celsius(98.6f));
}

void test_fahrenheit_to_celsius_negative_temperature(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -40.0f, fahrenheit_to_celsius(-40.0f));
}

// Tests for Celsius to Kelvin conversion
void test_celsius_to_kelvin_absolute_zero(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, celsius_to_kelvin(-273.15f));
}

void test_celsius_to_kelvin_freezing_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 273.15f, celsius_to_kelvin(0.0f));
}

// Tests for Kelvin to Celsius conversion
void test_kelvin_to_celsius_absolute_zero(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -273.15f, kelvin_to_celsius(0.0f));
}

void test_kelvin_to_celsius_freezing_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, kelvin_to_celsius(273.15f));
}

// Tests for get_temperature_status (assuming ranges: <=0 Freezing, >0-15 Cold, >15-25 Normal, >=25-100 Hot, >=100 Boiling)
void test_get_temperature_status_freezing(void) {
    TEST_ASSERT_EQUAL_STRING("Freezing", get_temperature_status(-10.5f));
}

void test_get_temperature_status_freezing_boundary(void) {
    TEST_ASSERT_EQUAL_STRING("Freezing", get_temperature_status(0.0f));
}

void test_get_temperature_status_cold(void) {
    TEST_ASSERT_EQUAL_STRING("Cold", get_temperature_status(10.0f));
}

void test_get_temperature_status_cold_boundaries(void) {
    TEST_ASSERT_EQUAL_STRING("Cold", get_temperature_status(0.1f));
    TEST_ASSERT_EQUAL_STRING("Cold", get_temperature_status(15.0f));
}

void test_get_temperature_status_normal(void) {
    TEST_ASSERT_EQUAL_STRING("Normal", get_temperature_status(20.0f));
}

void test_get_temperature_status_normal_boundaries(void) {
    TEST_ASSERT_EQUAL_STRING("Normal", get_temperature_status(15.1f));
    TEST_ASSERT_EQUAL_STRING("Normal", get_temperature_status(24.9f));
}

void test_get_temperature_status_hot(void) {
    TEST_ASSERT_EQUAL_STRING("Hot", get_temperature_status(30.0f));
}

void test_get_temperature_status_hot_boundaries(void) {
    TEST_ASSERT_EQUAL_STRING("Hot", get_temperature_status(25.0f));
    TEST_ASSERT_EQUAL_STRING("Hot", get_temperature_status(99.9f));
}

void test_get_temperature_status_boiling(void) {
    TEST_ASSERT_EQUAL_STRING("Boiling", get_temperature_status(105.0f));
}

void test_get_temperature_status_boiling_boundary(void) {
    TEST_ASSERT_EQUAL_STRING("Boiling", get_temperature_status(100.0f));
}


// Main function to run all tests
int main(void) {
    UNITY_BEGIN();

    // Run tests for temperature_utils.h
    RUN_TEST(test_calculate_temperature_difference_positive);
    RUN_TEST(test_calculate_temperature_difference_negative);
    RUN_TEST(test_calculate_temperature_difference_zero);
    RUN_TEST(test_calculate_temperature_difference_with_negative_numbers);
    RUN_TEST(test_is_temperature_stable_when_stable);
    RUN_TEST(test_is_temperature_stable_when_unstable);
    RUN_TEST(test_is_temperature_stable_at_boundary_inclusive);
    RUN_TEST(test_is_temperature_stable_just_outside_boundary);
    RUN_TEST(test_is_temperature_stable_when_identical);
    RUN_TEST(test_get_temperature_trend_rising);
    RUN_TEST(test_get_temperature_trend_falling);
    RUN_TEST(test_get_temperature_trend_stable_small_change);
    RUN_TEST(test_get_temperature_trend_stable_no_change);
    RUN_TEST(test_get_temperature_trend_stable_at_boundary);
    
    // Run tests for temperature_sensor.h
    RUN_TEST(test_get_temperature_runs_without_error);
    RUN_TEST(test_is_temperature_safe_within_range);
    RUN_TEST(test_is_temperature_safe_at_lower_boundary);
    RUN_TEST(test_is_temperature_safe_at_upper_boundary);
    RUN_TEST(test_is_temperature_safe_below_range);
    RUN_TEST(test_is_temperature_safe_above_range);
    RUN_TEST(test_celsius_to_fahrenheit_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_body_temperature);
    RUN_TEST(test_celsius_to_fahrenheit_negative_temperature);
    RUN_TEST(test_fahrenheit_to_celsius_freezing_point);
    RUN_TEST(test_fahrenheit_to_celsius_boiling_point);
    RUN_TEST(test_fahrenheit_to_celsius_body_temperature);
    RUN_TEST(test_fahrenheit_to_celsius_negative_temperature);
    RUN_TEST(test_celsius_to_kelvin_absolute_zero);
    RUN_TEST(test_celsius_to_kelvin_freezing_point);
    RUN_TEST(test_kelvin_to_celsius_absolute_zero);
    RUN_TEST(test_kelvin_to_celsius_freezing_point);
    RUN_TEST(test_get_temperature_status_freezing);
    RUN_TEST(test_get_temperature_status_freezing_boundary);
    RUN_TEST(test_get_temperature_status_cold);
    RUN_TEST(test_get_temperature_status_cold_boundaries);
    RUN_TEST(test_get_temperature_status_normal);
    RUN_TEST(test_get_temperature_status_normal_boundaries);
    RUN_TEST(test_get_temperature_status_hot);
    RUN_TEST(test_get_temperature_status_hot_boundaries);
    RUN_TEST(test_get_temperature_status_boiling);
    RUN_TEST(test_get_temperature_status_boiling_boundary);

    return UNITY_END();
}
