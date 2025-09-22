
#include "unity.h"
#include "temperature_sensor.h"
#include <string.h>

// Note: Implementations for functions in temperature_sensor.h are assumed to exist.
// This test file will call them, but their source is not provided here.
// Assumptions about behavior are made based on function names and standard conventions.

// For float comparisons
#define FLOAT_PRECISION 0.001f

// Optional: setUp and tearDown functions
void setUp(void) {
    // Set up tasks before each test
}

void tearDown(void) {
    // Clean up tasks after each test
}

// Test cases for is_temperature_safe
// Assuming a "safe" range is between 0 and 70 degrees Celsius (inclusive)
void test_is_temperature_safe_within_normal_range(void) {
    TEST_ASSERT_EQUAL(1, is_temperature_safe(25.0f));
}

void test_is_temperature_safe_at_lower_boundary(void) {
    TEST_ASSERT_EQUAL(1, is_temperature_safe(0.0f));
}

void test_is_temperature_safe_at_upper_boundary(void) {
    TEST_ASSERT_EQUAL(1, is_temperature_safe(70.0f));
}

void test_is_temperature_safe_below_range(void) {
    TEST_ASSERT_EQUAL(0, is_temperature_safe(-10.5f));
}

void test_is_temperature_safe_above_range(void) {
    TEST_ASSERT_EQUAL(0, is_temperature_safe(85.0f));
}

// Test cases for celsius_to_fahrenheit
void test_celsius_to_fahrenheit_freezing_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 32.0f, celsius_to_fahrenheit(0.0f));
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 212.0f, celsius_to_fahrenheit(100.0f));
}

void test_celsius_to_fahrenheit_negative_temp(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, -4.0f, celsius_to_fahrenheit(-20.0f));
}

void test_celsius_to_fahrenheit_crossover_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, -40.0f, celsius_to_fahrenheit(-40.0f));
}

void test_celsius_to_fahrenheit_body_temp(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 98.6f, celsius_to_fahrenheit(37.0f));
}

// Test cases for fahrenheit_to_celsius
void test_fahrenheit_to_celsius_freezing_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 0.0f, fahrenheit_to_celsius(32.0f));
}

void test_fahrenheit_to_celsius_boiling_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 100.0f, fahrenheit_to_celsius(212.0f));
}

void test_fahrenheit_to_celsius_negative_temp(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, -10.0f, fahrenheit_to_celsius(14.0f));
}

void test_fahrenheit_to_celsius_crossover_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, -40.0f, fahrenheit_to_celsius(-40.0f));
}

void test_fahrenheit_to_celsius_body_temp(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 37.0f, fahrenheit_to_celsius(98.6f));
}

// Test cases for celsius_to_kelvin
void test_celsius_to_kelvin_absolute_zero(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 0.0f, celsius_to_kelvin(-273.15f));
}

void test_celsius_to_kelvin_freezing_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 273.15f, celsius_to_kelvin(0.0f));
}

void test_celsius_to_kelvin_boiling_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_PRECISION, 373.15f, celsius_to_kelvin(100.0f));
}

// Test cases for get_temperature_status
// Assuming status boundaries: <0 "Freezing", 0-15 "Cold", 15-25 "Normal", >25 "Hot"
void test_get_temperature_status_freezing(void) {
    const char* status = get_temperature_status(-10.0f);
    TEST_ASSERT_NOT_NULL(status);
    TEST_ASSERT_EQUAL(0, strcmp("Freezing", status));
}

void test_get_temperature_status_cold(void) {
    const char* status = get_temperature_status(5.0f);
    TEST_ASSERT_NOT_NULL(status);
    TEST_ASSERT_EQUAL(0, strcmp("Cold", status));
}

void test_get_temperature_status_normal(void) {
    const char* status = get_temperature_status(20.0f);
    TEST_ASSERT_NOT_NULL(status);
    TEST_ASSERT_EQUAL(0, strcmp("Normal", status));
}

void test_get_temperature_status_hot(void) {
    const char* status = get_temperature_status(30.0f);
    TEST_ASSERT_NOT_NULL(status);
    TEST_ASSERT_EQUAL(0, strcmp("Hot", status));
}

void test_get_temperature_status_at_zero_boundary(void) {
    const char* status = get_temperature_status(0.0f);
    TEST_ASSERT_NOT_NULL(status);
    TEST_ASSERT_EQUAL(0, strcmp("Cold", status)); // Assuming 0 is Cold
}

void test_get_temperature_status_at_fifteen_boundary(void) {
    const char* status = get_temperature_status(15.0f);
    TEST_ASSERT_NOT_NULL(status);
    TEST_ASSERT_EQUAL(0, strcmp("Normal", status)); // Assuming 15 is Normal
}

void test_get_temperature_status_at_twenty_five_boundary(void) {
    const char* status = get_temperature_status(25.0f);
    TEST_ASSERT_NOT_NULL(status);
    TEST_ASSERT_EQUAL(0, strcmp("Hot", status)); // Assuming 25 is Hot
}


// Main function to run all tests
int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_is_temperature_safe_within_normal_range);
    RUN_TEST(test_is_temperature_safe_at_lower_boundary);
    RUN_TEST(test_is_temperature_safe_at_upper_boundary);
    RUN_TEST(test_is_temperature_safe_below_range);
    RUN_TEST(test_is_temperature_safe_above_range);

    RUN_TEST(test_celsius_to_fahrenheit_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_negative_temp);
    RUN_TEST(test_celsius_to_fahrenheit_crossover_point);
    RUN_TEST(test_celsius_to_fahrenheit_body_temp);

    RUN_TEST(test_fahrenheit_to_celsius_freezing_point);
    RUN_TEST(test_fahrenheit_to_celsius_boiling_point);
    RUN_TEST(test_fahrenheit_to_celsius_negative_temp);
    RUN_TEST(test_fahrenheit_to_celsius_crossover_point);
    RUN_TEST(test_fahrenheit_to_celsius_body_temp);

    RUN_TEST(test_celsius_to_kelvin_absolute_zero);
    RUN_TEST(test_celsius_to_kelvin_freezing_point);
    RUN_TEST(test_celsius_to_kelvin_boiling_point);

    RUN_TEST(test_get_temperature_status_freezing);
    RUN_TEST(test_get_temperature_status_cold);
    RUN_TEST(test_get_temperature_status_normal);
    RUN_TEST(test_get_temperature_status_hot);
    RUN_TEST(test_get_temperature_status_at_zero_boundary);
    RUN_TEST(test_get_temperature_status_at_fifteen_boundary);
    RUN_TEST(test_get_temperature_status_at_twenty_five_boundary);

    return UNITY_END();
}

