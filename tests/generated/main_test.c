
#include "unity.h"
#include "temperature_sensor.h"
#include "temperature_utils.h"
#include <string.h>

// setUp and tearDown functions are required by Unity
void setUp(void) {
    // This is run before EACH test
}

void tearDown(void) {
    // This is run after EACH test
}

//================================================================================
// Test Group for temperature_sensor.h
//================================================================================

//--- Tests for get_temperature ---
void test_get_temperature_plausible_range(void) {
    // Since we don't know the implementation, we can only do a sanity check.
    // A plausible temperature range is between absolute zero and something very hot.
    float temp = get_temperature();
    TEST_ASSERT_TRUE(temp > -273.16f && temp < 500.0f);
}

//--- Tests for is_temperature_safe ---
// Assuming a "safe" range is between 0.0 and 50.0 degrees Celsius.
void test_is_temperature_safe_within_range(void) {
    TEST_ASSERT_TRUE(is_temperature_safe(25.0f));
}

void test_is_temperature_safe_at_lower_boundary(void) {
    TEST_ASSERT_TRUE(is_temperature_safe(0.0f));
}

void test_is_temperature_safe_at_upper_boundary(void) {
    TEST_ASSERT_TRUE(is_temperature_safe(50.0f));
}

void test_is_temperature_safe_just_below_range(void) {
    TEST_ASSERT_FALSE(is_temperature_safe(-0.1f));
}

void test_is_temperature_safe_just_above_range(void) {
    TEST_ASSERT_FALSE(is_temperature_safe(50.1f));
}

void test_is_temperature_safe_very_low(void) {
    TEST_ASSERT_FALSE(is_temperature_safe(-100.0f));
}

void test_is_temperature_safe_very_high(void) {
    TEST_ASSERT_FALSE(is_temperature_safe(100.0f));
}

//--- Tests for celsius_to_fahrenheit ---
void test_celsius_to_fahrenheit_at_freezing(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 32.0f, celsius_to_fahrenheit(0.0f));
}

void test_celsius_to_fahrenheit_at_boiling(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 212.0f, celsius_to_fahrenheit(100.0f));
}

void test_celsius_to_fahrenheit_at_crossover(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, -40.0f, celsius_to_fahrenheit(-40.0f));
}

void test_celsius_to_fahrenheit_normal_temp(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 68.0f, celsius_to_fahrenheit(20.0f));
}

//--- Tests for fahrenheit_to_celsius ---
void test_fahrenheit_to_celsius_at_freezing(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 0.0f, fahrenheit_to_celsius(32.0f));
}

void test_fahrenheit_to_celsius_at_boiling(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 100.0f, fahrenheit_to_celsius(212.0f));
}

void test_fahrenheit_to_celsius_at_crossover(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, -40.0f, fahrenheit_to_celsius(-40.0f));
}

void test_fahrenheit_to_celsius_normal_temp(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 20.0f, fahrenheit_to_celsius(68.0f));
}

//--- Tests for celsius_to_kelvin ---
void test_celsius_to_kelvin_at_freezing(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 273.15f, celsius_to_kelvin(0.0f));
}

void test_celsius_to_kelvin_at_absolute_zero(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 0.0f, celsius_to_kelvin(-273.15f));
}

void test_celsius_to_kelvin_at_boiling(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 373.15f, celsius_to_kelvin(100.0f));
}

//--- Tests for kelvin_to_celsius ---
void test_kelvin_to_celsius_at_freezing(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 0.0f, kelvin_to_celsius(273.15f));
}

void test_kelvin_to_celsius_at_absolute_zero(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, -273.15f, kelvin_to_celsius(0.0f));
}

void test_kelvin_to_celsius_at_boiling(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 100.0f, kelvin_to_celsius(373.15f));
}

//--- Tests for get_temperature_status ---
// Assuming ranges: <0 Freezing, [0,15) Cold, [15,25) Normal, [25, 35) Warm, >=35 Hot
void test_get_temperature_status_freezing(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Freezing", get_temperature_status(-10.5f)));
}

void test_get_temperature_status_cold(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Cold", get_temperature_status(5.0f)));
}

void test_get_temperature_status_normal(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Normal", get_temperature_status(20.0f)));
}

void test_get_temperature_status_warm(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Warm", get_temperature_status(30.0f)));
}

void test_get_temperature_status_hot(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Hot", get_temperature_status(40.0f)));
}

void test_get_temperature_status_boundary_freezing_cold(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Cold", get_temperature_status(0.0f)));
}

void test_get_temperature_status_boundary_cold_normal(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Normal", get_temperature_status(15.0f)));
}

void test_get_temperature_status_boundary_normal_warm(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Warm", get_temperature_status(25.0f)));
}

void test_get_temperature_status_boundary_warm_hot(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Hot", get_temperature_status(35.0f)));
}

//================================================================================
// Test Group for temperature_utils.h
//================================================================================

//--- Tests for calculate_temperature_difference ---
void test_calculate_temperature_difference_positive_values(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 5.5f, calculate_temperature_difference(25.5f, 20.0f));
}

void test_calculate_temperature_difference_order_independent(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 5.5f, calculate_temperature_difference(20.0f, 25.5f));
}

void test_calculate_temperature_difference_with_negative_value(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 15.0f, calculate_temperature_difference(10.0f, -5.0f));
}

void test_calculate_temperature_difference_all_negative_values(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 5.0f, calculate_temperature_difference(-10.0f, -15.0f));
}

void test_calculate_temperature_difference_no_difference(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 0.0f, calculate_temperature_difference(22.3f, 22.3f));
}

//--- Tests for is_temperature_stable ---
// Assuming "stable" is a difference of <= 0.5 degrees
void test_is_temperature_stable_with_small_increase(void) {
    TEST_ASSERT_TRUE(is_temperature_stable(20.2f, 20.0f));
}

void test_is_temperature_stable_with_small_decrease(void) {
    TEST_ASSERT_TRUE(is_temperature_stable(19.8f, 20.0f));
}

void test_is_temperature_stable_at_threshold(void) {
    TEST_ASSERT_TRUE(is_temperature_stable(20.5f, 20.0f));
    TEST_ASSERT_TRUE(is_temperature_stable(19.5f, 20.0f));
}

void test_is_temperature_stable_with_no_change(void) {
    TEST_ASSERT_TRUE(is_temperature_stable(20.0f, 20.0f));
}

void test_is_temperature_stable_when_unstable_increase(void) {
    TEST_ASSERT_FALSE(is_temperature_stable(20.6f, 20.0f));
}

void test_is_temperature_stable_when_unstable_decrease(void) {
    TEST_ASSERT_FALSE(is_temperature_stable(19.4f, 20.0f));
}

//--- Tests for get_temperature_trend ---
// Assuming "Stable" if diff <= 0.1, otherwise "Rising" or "Falling"
void test_get_temperature_trend_rising(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Rising", get_temperature_trend(21.0f, 20.0f)));
}

void test_get_temperature_trend_falling(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Falling", get_temperature_trend(19.0f, 20.0f)));
}

void test_get_temperature_trend_stable_no_change(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Stable", get_temperature_trend(20.0f, 20.0f)));
}

void test_get_temperature_trend_stable_at_threshold_rise(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Stable", get_temperature_trend(20.1f, 20.0f)));
}

void test_get_temperature_trend_stable_at_threshold_fall(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Stable", get_temperature_trend(19.9f, 20.0f)));
}

void test_get_temperature_trend_just_above_stable_threshold(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Rising", get_temperature_trend(20.11f, 20.0f)));
}

void test_get_temperature_trend_just_below_stable_threshold(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Falling", get_temperature_trend(19.89f, 20.0f)));
}


int main(void) {
    UNITY_BEGIN();

    // Run tests for temperature_sensor.h
    RUN_TEST(test_get_temperature_plausible_range);
    RUN_TEST(test_is_temperature_safe_within_range);
    RUN_TEST(test_is_temperature_safe_at_lower_boundary);
    RUN_TEST(test_is_temperature_safe_at_upper_boundary);
    RUN_TEST(test_is_temperature_safe_just_below_range);
    RUN_TEST(test_is_temperature_safe_just_above_range);
    RUN_TEST(test_is_temperature_safe_very_low);
    RUN_TEST(test_is_temperature_safe_very_high);
    RUN_TEST(test_celsius_to_fahrenheit_at_freezing);
    RUN_TEST(test_celsius_to_fahrenheit_at_boiling);
    RUN_TEST(test_celsius_to_fahrenheit_at_crossover);
    RUN_TEST(test_celsius_to_fahrenheit_normal_temp);
    RUN_TEST(test_fahrenheit_to_celsius_at_freezing);
    RUN_TEST(test_fahrenheit_to_celsius_at_boiling);
    RUN_TEST(test_fahrenheit_to_celsius_at_crossover);
    RUN_TEST(test_fahrenheit_to_celsius_normal_temp);
    RUN_TEST(test_celsius_to_kelvin_at_freezing);
    RUN_TEST(test_celsius_to_kelvin_at_absolute_zero);
    RUN_TEST(test_celsius_to_kelvin_at_boiling);
    RUN_TEST(test_kelvin_to_celsius_at_freezing);
    RUN_TEST(test_kelvin_to_celsius_at_absolute_zero);
    RUN_TEST(test_kelvin_to_celsius_at_boiling);
    RUN_TEST(test_get_temperature_status_freezing);
    RUN_TEST(test_get_temperature_status_cold);
    RUN_TEST(test_get_temperature_status_normal);
    RUN_TEST(test_get_temperature_status_warm);
    RUN_TEST(test_get_temperature_status_hot);
    RUN_TEST(test_get_temperature_status_boundary_freezing_cold);
    RUN_TEST(test_get_temperature_status_boundary_cold_normal);
    RUN_TEST(test_get_temperature_status_boundary_normal_warm);
    RUN_TEST(test_get_temperature_status_boundary_warm_hot);

    // Run tests for temperature_utils.h
    RUN_TEST(test_calculate_temperature_difference_positive_values);
    RUN_TEST(test_calculate_temperature_difference_order_independent);
    RUN_TEST(test_calculate_temperature_difference_with_negative_value);
    RUN_TEST(test_calculate_temperature_difference_all_negative_values);
    RUN_TEST(test_calculate_temperature_difference_no_difference);
    RUN_TEST(test_is_temperature_stable_with_small_increase);
    RUN_TEST(test_is_temperature_stable_with_small_decrease);
    RUN_TEST(test_is_temperature_stable_at_threshold);
    RUN_TEST(test_is_temperature_stable_with_no_change);
    RUN_TEST(test_is_temperature_stable_when_unstable_increase);
    RUN_TEST(test_is_temperature_stable_when_unstable_decrease);
    RUN_TEST(test_get_temperature_trend_rising);
    RUN_TEST(test_get_temperature_trend_falling);
    RUN_TEST(test_get_temperature_trend_stable_no_change);
    RUN_TEST(test_get_temperature_trend_stable_at_threshold_rise);
    RUN_TEST(test_get_temperature_trend_stable_at_threshold_fall);
    RUN_TEST(test_get_temperature_trend_just_above_stable_threshold);
    RUN_TEST(test_get_temperature_trend_just_below_stable_threshold);

    return UNITY_END();
}
