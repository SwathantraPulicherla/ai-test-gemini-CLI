
#include "unity.h"
#include "temperature_sensor.h"
#include "temperature_utils.h"
#include <string.h>

// setUp and tearDown functions can be used for test setup and cleanup
void setUp(void) {
    // This function is called before each test
}

void tearDown(void) {
    // This function is called after each test
}

//================================================================================
// Tests for temperature_utils.h
//================================================================================

void test_calculate_temperature_difference_positive(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 5.0f, calculate_temperature_difference(25.0f, 20.0f));
}

void test_calculate_temperature_difference_swapped_args(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 5.0f, calculate_temperature_difference(20.0f, 25.0f));
}

void test_calculate_temperature_difference_with_negative_values(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 15.0f, calculate_temperature_difference(-5.0f, 10.0f));
}

void test_calculate_temperature_difference_both_negative(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 5.0f, calculate_temperature_difference(-10.0f, -15.0f));
}

void test_calculate_temperature_difference_zero_difference(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, calculate_temperature_difference(33.3f, 33.3f));
}

void test_is_temperature_stable_within_threshold(void) {
    // Assumes stable if difference <= 0.5
    TEST_ASSERT_TRUE(is_temperature_stable(25.4f, 25.0f));
}

void test_is_temperature_stable_at_threshold(void) {
    // Assumes stable if difference <= 0.5
    TEST_ASSERT_TRUE(is_temperature_stable(25.5f, 25.0f));
}

void test_is_temperature_stable_outside_threshold(void) {
    // Assumes stable if difference <= 0.5
    TEST_ASSERT_FALSE(is_temperature_stable(25.6f, 25.0f));
}

void test_is_temperature_stable_no_change(void) {
    TEST_ASSERT_TRUE(is_temperature_stable(30.0f, 30.0f));
}

void test_is_temperature_stable_negative_values(void) {
    // Assumes stable if difference <= 0.5
    TEST_ASSERT_TRUE(is_temperature_stable(-10.2f, -10.5f));
    TEST_ASSERT_FALSE(is_temperature_stable(-10.2f, -10.8f));
}

void test_get_temperature_trend_stable(void) {
    // Assumes stable if difference is within +/- 0.5
    TEST_ASSERT_EQUAL(0, strcmp("STABLE", get_temperature_trend(25.3f, 25.0f)));
    TEST_ASSERT_EQUAL(0, strcmp("STABLE", get_temperature_trend(24.8f, 25.0f)));
}

void test_get_temperature_trend_rising(void) {
    TEST_ASSERT_EQUAL(0, strcmp("RISING", get_temperature_trend(26.0f, 25.0f)));
}

void test_get_temperature_trend_falling(void) {
    TEST_ASSERT_EQUAL(0, strcmp("FALLING", get_temperature_trend(24.0f, 25.0f)));
}

void test_get_temperature_trend_stable_at_boundary(void) {
    // Assumes stable if difference is within +/- 0.5
    TEST_ASSERT_EQUAL(0, strcmp("STABLE", get_temperature_trend(25.5f, 25.0f)));
    TEST_ASSERT_EQUAL(0, strcmp("STABLE", get_temperature_trend(24.5f, 25.0f)));
}

//================================================================================
// Tests for temperature_sensor.h
//================================================================================

void test_get_temperature_plausible_range(void) {
    // This is a sanity check since the exact value is unpredictable
    float temp = get_temperature();
    TEST_ASSERT_TRUE(temp >= -100.0f && temp <= 200.0f);
}

void test_is_temperature_safe_within_range(void) {
    // Assumes safe range is [0, 100]
    TEST_ASSERT_TRUE(is_temperature_safe(25.0f));
    TEST_ASSERT_TRUE(is_temperature_safe(50.5f));
}

void test_is_temperature_safe_at_boundaries(void) {
    TEST_ASSERT_TRUE(is_temperature_safe(0.0f));
    TEST_ASSERT_TRUE(is_temperature_safe(100.0f));
}

void test_is_temperature_safe_outside_range(void) {
    TEST_ASSERT_FALSE(is_temperature_safe(-0.1f));
    TEST_ASSERT_FALSE(is_temperature_safe(100.1f));
    TEST_ASSERT_FALSE(is_temperature_safe(-273.0f));
}

void test_celsius_to_fahrenheit_conversions(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 32.0f, celsius_to_fahrenheit(0.0f));      // Freezing point
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 212.0f, celsius_to_fahrenheit(100.0f));   // Boiling point
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 98.6f, celsius_to_fahrenheit(37.0f));     // Body temperature
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -40.0f, celsius_to_fahrenheit(-40.0f));   // Crossover point
}

void test_fahrenheit_to_celsius_conversions(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, fahrenheit_to_celsius(32.0f));      // Freezing point
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 100.0f, fahrenheit_to_celsius(212.0f));   // Boiling point
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 37.0f, fahrenheit_to_celsius(98.6f));     // Body temperature
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -40.0f, fahrenheit_to_celsius(-40.0f));   // Crossover point
}

void test_celsius_to_kelvin_conversions(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 273.15f, celsius_to_kelvin(0.0f));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, celsius_to_kelvin(-273.15f));      // Absolute zero
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 373.15f, celsius_to_kelvin(100.0f));
}

void test_kelvin_to_celsius_conversions(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, kelvin_to_celsius(273.15f));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -273.15f, kelvin_to_celsius(0.0f));      // Absolute zero
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 100.0f, kelvin_to_celsius(373.15f));
}

void test_get_temperature_status_all_ranges(void) {
    // Assumes ranges: <0 Freezing, 0-15 Cold, 15-25 Normal, 25-35 Warm, >=35 Hot
    TEST_ASSERT_EQUAL(0, strcmp("Freezing", get_temperature_status(-10.0f)));
    TEST_ASSERT_EQUAL(0, strcmp("Freezing", get_temperature_status(-0.1f)));
    TEST_ASSERT_EQUAL(0, strcmp("Cold", get_temperature_status(0.0f)));
    TEST_ASSERT_EQUAL(0, strcmp("Cold", get_temperature_status(14.9f)));
    TEST_ASSERT_EQUAL(0, strcmp("Normal", get_temperature_status(15.0f)));
    TEST_ASSERT_EQUAL(0, strcmp("Normal", get_temperature_status(24.9f)));
    TEST_ASSERT_EQUAL(0, strcmp("Warm", get_temperature_status(25.0f)));
    TEST_ASSERT_EQUAL(0, strcmp("Warm", get_temperature_status(34.9f)));
    TEST_ASSERT_EQUAL(0, strcmp("Hot", get_temperature_status(35.0f)));
    TEST_ASSERT_EQUAL(0, strcmp("Hot", get_temperature_status(100.0f)));
}

// Main function to run all tests
int main(void) {
    UNITY_BEGIN();

    // Run tests for temperature_utils.h
    RUN_TEST(test_calculate_temperature_difference_positive);
    RUN_TEST(test_calculate_temperature_difference_swapped_args);
    RUN_TEST(test_calculate_temperature_difference_with_negative_values);
    RUN_TEST(test_calculate_temperature_difference_both_negative);
    RUN_TEST(test_calculate_temperature_difference_zero_difference);
    RUN_TEST(test_is_temperature_stable_within_threshold);
    RUN_TEST(test_is_temperature_stable_at_threshold);
    RUN_TEST(test_is_temperature_stable_outside_threshold);
    RUN_TEST(test_is_temperature_stable_no_change);
    RUN_TEST(test_is_temperature_stable_negative_values);
    RUN_TEST(test_get_temperature_trend_stable);
    RUN_TEST(test_get_temperature_trend_rising);
    RUN_TEST(test_get_temperature_trend_falling);
    RUN_TEST(test_get_temperature_trend_stable_at_boundary);

    // Run tests for temperature_sensor.h
    RUN_TEST(test_get_temperature_plausible_range);
    RUN_TEST(test_is_temperature_safe_within_range);
    RUN_TEST(test_is_temperature_safe_at_boundaries);
    RUN_TEST(test_is_temperature_safe_outside_range);
    RUN_TEST(test_celsius_to_fahrenheit_conversions);
    RUN_TEST(test_fahrenheit_to_celsius_conversions);
    RUN_TEST(test_celsius_to_kelvin_conversions);
    RUN_TEST(test_kelvin_to_celsius_conversions);
    RUN_TEST(test_get_temperature_status_all_ranges);

    return UNITY_END();
}
