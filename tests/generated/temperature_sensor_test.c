
#include "unity.h"
#include "temperature_sensor.h"
#include <string.h>

// Define a small delta for float comparisons
#define FLOAT_DELTA 0.001f

// setUp and tearDown functions
void setUp(void) {
    // Set up code, if any
}

void tearDown(void) {
    // Clean up code, if any
}

// Test for get_temperature()
void test_get_temperature_returns_fixed_value(void) {
    // Behavior: Always returns 25.5f
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 25.5f, get_temperature());
}

// Tests for is_temperature_safe()
void test_is_temperature_safe_within_range(void) {
    // Behavior: Returns 1 if temp is in range [0.0, 100.0]
    TEST_ASSERT_EQUAL(1, is_temperature_safe(50.0f));
}

void test_is_temperature_safe_at_lower_boundary(void) {
    TEST_ASSERT_EQUAL(1, is_temperature_safe(0.0f));
}

void test_is_temperature_safe_at_upper_boundary(void) {
    TEST_ASSERT_EQUAL(1, is_temperature_safe(100.0f));
}

void test_is_temperature_safe_below_range(void) {
    // Behavior: Returns 0 if temp is outside the range
    TEST_ASSERT_EQUAL(0, is_temperature_safe(-0.1f));
    TEST_ASSERT_EQUAL(0, is_temperature_safe(-50.0f));
}

void test_is_temperature_safe_above_range(void) {
    TEST_ASSERT_EQUAL(0, is_temperature_safe(100.1f));
    TEST_ASSERT_EQUAL(0, is_temperature_safe(200.0f));
}

// Tests for celsius_to_fahrenheit()
void test_celsius_to_fahrenheit_zero(void) {
    // 0 C = 32 F
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 32.0f, celsius_to_fahrenheit(0.0f));
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    // 100 C = 212 F
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 212.0f, celsius_to_fahrenheit(100.0f));
}

void test_celsius_to_fahrenheit_negative_value(void) {
    // -40 C = -40 F
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, -40.0f, celsius_to_fahrenheit(-40.0f));
}

void test_celsius_to_fahrenheit_positive_value(void) {
    // 37 C = 98.6 F
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 98.6f, celsius_to_fahrenheit(37.0f));
}

// Tests for fahrenheit_to_celsius()
void test_fahrenheit_to_celsius_zero(void) {
    // 32 F = 0 C
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 0.0f, fahrenheit_to_celsius(32.0f));
}

void test_fahrenheit_to_celsius_boiling_point(void) {
    // 212 F = 100 C
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 100.0f, fahrenheit_to_celsius(212.0f));
}

void test_fahrenheit_to_celsius_negative_value(void) {
    // -40 F = -40 C
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, -40.0f, fahrenheit_to_celsius(-40.0f));
}

void test_fahrenheit_to_celsius_positive_value(void) {
    // 98.6 F = 37 C
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 37.0f, fahrenheit_to_celsius(98.6f));
}

// Tests for celsius_to_kelvin()
void test_celsius_to_kelvin_absolute_zero(void) {
    // -273.15 C = 0 K
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 0.0f, celsius_to_kelvin(-273.15f));
}

void test_celsius_to_kelvin_freezing_point(void) {
    // 0 C = 273.15 K
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 273.15f, celsius_to_kelvin(0.0f));
}

void test_celsius_to_kelvin_positive_value(void) {
    // 100 C = 373.15 K
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 373.15f, celsius_to_kelvin(100.0f));
}

// Tests for kelvin_to_celsius()
void test_kelvin_to_celsius_absolute_zero(void) {
    // 0 K = -273.15 C
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, -273.15f, kelvin_to_celsius(0.0f));
}

void test_kelvin_to_celsius_water_freezing(void) {
    // 273.15 K = 0 C
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 0.0f, kelvin_to_celsius(273.15f));
}

void test_kelvin_to_celsius_positive_value(void) {
    // 373.15 K = 100 C
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 100.0f, kelvin_to_celsius(373.15f));
}

// Tests for get_temperature_status()
void test_get_temperature_status_cold(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Cold", get_temperature_status(9.9f)));
    TEST_ASSERT_EQUAL(0, strcmp("Cold", get_temperature_status(0.0f)));
    TEST_ASSERT_EQUAL(0, strcmp("Cold", get_temperature_status(-10.0f)));
}

void test_get_temperature_status_normal(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Normal", get_temperature_status(10.0f)));
    TEST_ASSERT_EQUAL(0, strcmp("Normal", get_temperature_status(15.0f)));
    TEST_ASSERT_EQUAL(0, strcmp("Normal", get_temperature_status(24.9f)));
}

void test_get_temperature_status_warm(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Warm", get_temperature_status(25.0f)));
    TEST_ASSERT_EQUAL(0, strcmp("Warm", get_temperature_status(30.0f)));
    TEST_ASSERT_EQUAL(0, strcmp("Warm", get_temperature_status(34.9f)));
}

void test_get_temperature_status_hot(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Hot", get_temperature_status(35.0f)));
    TEST_ASSERT_EQUAL(0, strcmp("Hot", get_temperature_status(50.0f)));
    TEST_ASSERT_EQUAL(0, strcmp("Hot", get_temperature_status(100.0f)));
}

// Main test runner
int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_get_temperature_returns_fixed_value);
    
    RUN_TEST(test_is_temperature_safe_within_range);
    RUN_TEST(test_is_temperature_safe_at_lower_boundary);
    RUN_TEST(test_is_temperature_safe_at_upper_boundary);
    RUN_TEST(test_is_temperature_safe_below_range);
    RUN_TEST(test_is_temperature_safe_above_range);
    
    RUN_TEST(test_celsius_to_fahrenheit_zero);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_negative_value);
    RUN_TEST(test_celsius_to_fahrenheit_positive_value);
    
    RUN_TEST(test_fahrenheit_to_celsius_zero);
    RUN_TEST(test_fahrenheit_to_celsius_boiling_point);
    RUN_TEST(test_fahrenheit_to_celsius_negative_value);
    RUN_TEST(test_fahrenheit_to_celsius_positive_value);
    
    RUN_TEST(test_celsius_to_kelvin_absolute_zero);
    RUN_TEST(test_celsius_to_kelvin_freezing_point);
    RUN_TEST(test_celsius_to_kelvin_positive_value);
    
    RUN_TEST(test_kelvin_to_celsius_absolute_zero);
    RUN_TEST(test_kelvin_to_celsius_water_freezing);
    RUN_TEST(test_kelvin_to_celsius_positive_value);
    
    RUN_TEST(test_get_temperature_status_cold);
    RUN_TEST(test_get_temperature_status_normal);
    RUN_TEST(test_get_temperature_status_warm);
    RUN_TEST(test_get_temperature_status_hot);

    return UNITY_END();
}
