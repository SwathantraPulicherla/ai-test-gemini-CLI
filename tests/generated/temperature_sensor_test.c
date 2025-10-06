
#include "unity.h"
#include "temperature_sensor.h"
#include <string.h>

// setUp and tearDown functions are optional but good practice
void setUp(void) {
    // Set up code, if any, to run before each test
}

void tearDown(void) {
    // Clean up code, if any, to run after each test
}

// Test for get_temperature()
void test_get_temperature_should_return_fixed_value(void) {
    // Behavior: Always returns 25.5f
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 25.5f, get_temperature());
}

// Tests for is_temperature_safe()
void test_is_temperature_safe_should_return_true_for_mid_range(void) {
    // Behavior: Returns 1 if temp is in range [0.0, 100.0]
    TEST_ASSERT_TRUE(is_temperature_safe(50.0f));
}

void test_is_temperature_safe_should_return_true_for_lower_boundary(void) {
    // Behavior: Returns 1 for the lower boundary 0.0f
    TEST_ASSERT_TRUE(is_temperature_safe(0.0f));
}

void test_is_temperature_safe_should_return_true_for_upper_boundary(void) {
    // Behavior: Returns 1 for the upper boundary 100.0f
    TEST_ASSERT_TRUE(is_temperature_safe(100.0f));
}

void test_is_temperature_safe_should_return_false_below_range(void) {
    // Behavior: Returns 0 if temp is < 0.0f
    TEST_ASSERT_FALSE(is_temperature_safe(-0.1f));
}

void test_is_temperature_safe_should_return_false_above_range(void) {
    // Behavior: Returns 0 if temp is > 100.0f
    TEST_ASSERT_FALSE(is_temperature_safe(100.1f));
}

// Tests for celsius_to_fahrenheit()
void test_celsius_to_fahrenheit_should_convert_zero(void) {
    // 0°C should be 32°F
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 32.0f, celsius_to_fahrenheit(0.0f));
}

void test_celsius_to_fahrenheit_should_convert_boiling_point(void) {
    // 100°C should be 212°F
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 212.0f, celsius_to_fahrenheit(100.0f));
}

void test_celsius_to_fahrenheit_should_convert_negative_40(void) {
    // -40°C should be -40°F
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -40.0f, celsius_to_fahrenheit(-40.0f));
}

// Tests for fahrenheit_to_celsius()
void test_fahrenheit_to_celsius_should_convert_freezing_point(void) {
    // 32°F should be 0°C
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, fahrenheit_to_celsius(32.0f));
}

void test_fahrenheit_to_celsius_should_convert_boiling_point(void) {
    // 212°F should be 100°C
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 100.0f, fahrenheit_to_celsius(212.0f));
}

void test_fahrenheit_to_celsius_should_convert_negative_40(void) {
    // -40°F should be -40°C
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -40.0f, fahrenheit_to_celsius(-40.0f));
}

// Tests for celsius_to_kelvin()
void test_celsius_to_kelvin_should_convert_zero_celsius(void) {
    // 0°C should be 273.15 K
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 273.15f, celsius_to_kelvin(0.0f));
}

void test_celsius_to_kelvin_should_convert_absolute_zero(void) {
    // -273.15°C should be 0 K
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, celsius_to_kelvin(-273.15f));
}

void test_celsius_to_kelvin_should_convert_positive_value(void) {
    // 100°C should be 373.15 K
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 373.15f, celsius_to_kelvin(100.0f));
}

// Tests for kelvin_to_celsius()
void test_kelvin_to_celsius_should_convert_absolute_zero(void) {
    // 0 K should be -273.15°C
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -273.15f, kelvin_to_celsius(0.0f));
}

void test_kelvin_to_celsius_should_convert_to_zero_celsius(void) {
    // 273.15 K should be 0°C
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, kelvin_to_celsius(273.15f));
}

void test_kelvin_to_celsius_should_convert_positive_value(void) {
    // 373.15 K should be 100°C
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 100.0f, kelvin_to_celsius(373.15f));
}

// Tests for get_temperature_status()
void test_get_temperature_status_should_return_cold(void) {
    // Temp < 10.0f is "Cold"
    TEST_ASSERT_EQUAL(0, strcmp("Cold", get_temperature_status(9.9f)));
    TEST_ASSERT_EQUAL(0, strcmp("Cold", get_temperature_status(-10.0f)));
}

void test_get_temperature_status_should_return_normal(void) {
    // Temp >= 10.0f and < 25.0f is "Normal"
    TEST_ASSERT_EQUAL(0, strcmp("Normal", get_temperature_status(15.0f)));
}

void test_get_temperature_status_should_return_warm(void) {
    // Temp >= 25.0f and < 35.0f is "Warm"
    TEST_ASSERT_EQUAL(0, strcmp("Warm", get_temperature_status(30.0f)));
}

void test_get_temperature_status_should_return_hot(void) {
    // Temp >= 35.0f is "Hot"
    TEST_ASSERT_EQUAL(0, strcmp("Hot", get_temperature_status(40.0f)));
}

void test_get_temperature_status_boundary_cold_to_normal(void) {
    // Boundary at 10.0f should be "Normal"
    TEST_ASSERT_EQUAL(0, strcmp("Normal", get_temperature_status(10.0f)));
}

void test_get_temperature_status_boundary_normal_to_warm(void) {
    // Boundary at 25.0f should be "Warm"
    TEST_ASSERT_EQUAL(0, strcmp("Warm", get_temperature_status(25.0f)));
}

void test_get_temperature_status_boundary_warm_to_hot(void) {
    // Boundary at 35.0f should be "Hot"
    TEST_ASSERT_EQUAL(0, strcmp("Hot", get_temperature_status(35.0f)));
}

// Main function to run all tests
int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_get_temperature_should_return_fixed_value);

    RUN_TEST(test_is_temperature_safe_should_return_true_for_mid_range);
    RUN_TEST(test_is_temperature_safe_should_return_true_for_lower_boundary);
    RUN_TEST(test_is_temperature_safe_should_return_true_for_upper_boundary);
    RUN_TEST(test_is_temperature_safe_should_return_false_below_range);
    RUN_TEST(test_is_temperature_safe_should_return_false_above_range);

    RUN_TEST(test_celsius_to_fahrenheit_should_convert_zero);
    RUN_TEST(test_celsius_to_fahrenheit_should_convert_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_should_convert_negative_40);

    RUN_TEST(test_fahrenheit_to_celsius_should_convert_freezing_point);
    RUN_TEST(test_fahrenheit_to_celsius_should_convert_boiling_point);
    RUN_TEST(test_fahrenheit_to_celsius_should_convert_negative_40);

    RUN_TEST(test_celsius_to_kelvin_should_convert_zero_celsius);
    RUN_TEST(test_celsius_to_kelvin_should_convert_absolute_zero);
    RUN_TEST(test_celsius_to_kelvin_should_convert_positive_value);

    RUN_TEST(test_kelvin_to_celsius_should_convert_absolute_zero);
    RUN_TEST(test_kelvin_to_celsius_should_convert_to_zero_celsius);
    RUN_TEST(test_kelvin_to_celsius_should_convert_positive_value);

    RUN_TEST(test_get_temperature_status_should_return_cold);
    RUN_TEST(test_get_temperature_status_should_return_normal);
    RUN_TEST(test_get_temperature_status_should_return_warm);
    RUN_TEST(test_get_temperature_status_should_return_hot);
    RUN_TEST(test_get_temperature_status_boundary_cold_to_normal);
    RUN_TEST(test_get_temperature_status_boundary_normal_to_warm);
    RUN_TEST(test_get_temperature_status_boundary_warm_to_hot);

    return UNITY_END();
}
