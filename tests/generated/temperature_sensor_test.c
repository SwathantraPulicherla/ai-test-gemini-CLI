
#include "unity.h"
#include "temperature_sensor.h"
#include <string.h>

// Note: The problem description did not provide the source for temperature_utils.h/c
// so tests for those functions are omitted. This file only tests temperature_sensor.c

void setUp(void) {
    // Set up code, if needed
}

void tearDown(void) {
    // Clean up code, if needed
}

// Tests for get_temperature()
void test_get_temperature_should_return_fixed_stub_value(void) {
    // Behavior: Always returns 25.5f as a stub implementation
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 25.5f, get_temperature());
}

// Tests for is_temperature_safe()
void test_is_temperature_safe_should_return_true_for_values_within_range(void) {
    // Behavior: Returns 1 if temp is in range [0.0, 100.0]
    TEST_ASSERT_EQUAL(1, is_temperature_safe(50.0f));
    TEST_ASSERT_EQUAL(1, is_temperature_safe(0.1f));
    TEST_ASSERT_EQUAL(1, is_temperature_safe(99.9f));
}

void test_is_temperature_safe_should_return_true_for_boundary_values(void) {
    // Behavior: Returns 1 if temp is in range [0.0, 100.0]
    TEST_ASSERT_EQUAL(1, is_temperature_safe(0.0f));
    TEST_ASSERT_EQUAL(1, is_temperature_safe(100.0f));
}

void test_is_temperature_safe_should_return_false_for_values_outside_range(void) {
    // Behavior: Returns 0 otherwise
    TEST_ASSERT_EQUAL(0, is_temperature_safe(-0.1f));
    TEST_ASSERT_EQUAL(0, is_temperature_safe(100.1f));
    TEST_ASSERT_EQUAL(0, is_temperature_safe(-50.0f));
    TEST_ASSERT_EQUAL(0, is_temperature_safe(200.0f));
}

// Tests for celsius_to_fahrenheit()
void test_celsius_to_fahrenheit_should_convert_correctly(void) {
    // Behavior: Returns (celsius * 9.0f / 5.0f) + 32.0f
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 32.0f, celsius_to_fahrenheit(0.0f));      // Freezing point
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 212.0f, celsius_to_fahrenheit(100.0f));   // Boiling point
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -40.0f, celsius_to_fahrenheit(-40.0f));   // Crossover point
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 77.0f, celsius_to_fahrenheit(25.0f));     // Room temperature
}

// Tests for fahrenheit_to_celsius()
void test_fahrenheit_to_celsius_should_convert_correctly(void) {
    // Behavior: Returns (fahrenheit - 32.0f) * 5.0f / 9.0f
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, fahrenheit_to_celsius(32.0f));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 100.0f, fahrenheit_to_celsius(212.0f));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -40.0f, fahrenheit_to_celsius(-40.0f));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 25.0f, fahrenheit_to_celsius(77.0f));
}

// Tests for celsius_to_kelvin()
void test_celsius_to_kelvin_should_convert_correctly(void) {
    // Behavior: Returns celsius + 273.15f
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 273.15f, celsius_to_kelvin(0.0f));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 373.15f, celsius_to_kelvin(100.0f));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, celsius_to_kelvin(-273.15f));      // Absolute zero
}

// Tests for kelvin_to_celsius()
void test_kelvin_to_celsius_should_convert_correctly(void) {
    // Behavior: Returns kelvin - 273.15f
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, kelvin_to_celsius(273.15f));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 100.0f, kelvin_to_celsius(373.15f));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -273.15f, kelvin_to_celsius(0.0f));
}

// Tests for get_temperature_status()
void test_get_temperature_status_should_return_cold(void) {
    // Behavior: Returns "Cold" if temp < 10
    TEST_ASSERT_EQUAL(0, strcmp("Cold", get_temperature_status(9.9f)));
    TEST_ASSERT_EQUAL(0, strcmp("Cold", get_temperature_status(0.0f)));
    TEST_ASSERT_EQUAL(0, strcmp("Cold", get_temperature_status(-20.0f)));
}

void test_get_temperature_status_should_return_normal(void) {
    // Behavior: Returns "Normal" if 10 <= temp < 25
    TEST_ASSERT_EQUAL(0, strcmp("Normal", get_temperature_status(10.0f))); // Lower boundary
    TEST_ASSERT_EQUAL(0, strcmp("Normal", get_temperature_status(17.5f)));
    TEST_ASSERT_EQUAL(0, strcmp("Normal", get_temperature_status(24.9f))); // Upper boundary
}

void test_get_temperature_status_should_return_warm(void) {
    // Behavior: Returns "Warm" if 25 <= temp < 35
    TEST_ASSERT_EQUAL(0, strcmp("Warm", get_temperature_status(25.0f)));   // Lower boundary
    TEST_ASSERT_EQUAL(0, strcmp("Warm", get_temperature_status(30.0f)));
    TEST_ASSERT_EQUAL(0, strcmp("Warm", get_temperature_status(34.9f)));   // Upper boundary
}

void test_get_temperature_status_should_return_hot(void) {
    // Behavior: Returns "Hot" if temp >= 35
    TEST_ASSERT_EQUAL(0, strcmp("Hot", get_temperature_status(35.0f)));    // Lower boundary
    TEST_ASSERT_EQUAL(0, strcmp("Hot", get_temperature_status(50.0f)));
    TEST_ASSERT_EQUAL(0, strcmp("Hot", get_temperature_status(100.0f)));
}


int main(void) {
    UNITY_BEGIN();

    // Tests for temperature_sensor.c functions
    RUN_TEST(test_get_temperature_should_return_fixed_stub_value);
    RUN_TEST(test_is_temperature_safe_should_return_true_for_values_within_range);
    RUN_TEST(test_is_temperature_safe_should_return_true_for_boundary_values);
    RUN_TEST(test_is_temperature_safe_should_return_false_for_values_outside_range);
    RUN_TEST(test_celsius_to_fahrenheit_should_convert_correctly);
    RUN_TEST(test_fahrenheit_to_celsius_should_convert_correctly);
    RUN_TEST(test_celsius_to_kelvin_should_convert_correctly);
    RUN_TEST(test_kelvin_to_celsius_should_convert_correctly);
    RUN_TEST(test_get_temperature_status_should_return_cold);
    RUN_TEST(test_get_temperature_status_should_return_normal);
    RUN_TEST(test_get_temperature_status_should_return_warm);
    RUN_TEST(test_get_temperature_status_should_return_hot);
    
    return UNITY_END();
}
