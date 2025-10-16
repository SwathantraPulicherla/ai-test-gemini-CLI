
#include "unity.h"
#include "temperature_sensor.h"
#include <string.h>

// setUp and tearDown functions are called before and after each test
void setUp(void) {
    // No setup needed for these tests
}

void tearDown(void) {
    // No teardown needed for these tests
}

//==================================================
// Test cases for get_temperature()
//==================================================

void test_get_temperature_returns_fixed_value(void) {
    // Behavior: Always returns 25.5f
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 25.5f, get_temperature());
}

//==================================================
// Test cases for is_temperature_safe()
//==================================================

void test_is_temperature_safe_within_range(void) {
    // Behavior: Returns 1 if temp is in range [0.0, 100.0]
    TEST_ASSERT_TRUE(is_temperature_safe(50.0f));
}

void test_is_temperature_safe_at_lower_boundary(void) {
    TEST_ASSERT_TRUE(is_temperature_safe(0.0f));
}

void test_is_temperature_safe_at_upper_boundary(void) {
    TEST_ASSERT_TRUE(is_temperature_safe(100.0f));
}

void test_is_temperature_safe_below_range(void) {
    TEST_ASSERT_FALSE(is_temperature_safe(-0.1f));
    TEST_ASSERT_FALSE(is_temperature_safe(-100.0f));
}

void test_is_temperature_safe_above_range(void) {
    TEST_ASSERT_FALSE(is_temperature_safe(100.1f));
    TEST_ASSERT_FALSE(is_temperature_safe(200.0f));
}

//==================================================
// Test cases for celsius_to_fahrenheit()
//==================================================

void test_celsius_to_fahrenheit_zero(void) {
    // 0 C = 32 F
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 32.0f, celsius_to_fahrenheit(0.0f));
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    // 100 C = 212 F
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 212.0f, celsius_to_fahrenheit(100.0f));
}

void test_celsius_to_fahrenheit_negative_value(void) {
    // -40 C = -40 F
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -40.0f, celsius_to_fahrenheit(-40.0f));
}

void test_celsius_to_fahrenheit_room_temperature(void) {
    // 25 C = 77 F
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 77.0f, celsius_to_fahrenheit(25.0f));
}

//==================================================
// Test cases for fahrenheit_to_celsius()
//==================================================

void test_fahrenheit_to_celsius_freezing_point(void) {
    // 32 F = 0 C
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, fahrenheit_to_celsius(32.0f));
}

void test_fahrenheit_to_celsius_boiling_point(void) {
    // 212 F = 100 C
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 100.0f, fahrenheit_to_celsius(212.0f));
}

void test_fahrenheit_to_celsius_negative_value(void) {
    // -40 F = -40 C
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -40.0f, fahrenheit_to_celsius(-40.0f));
}

void test_fahrenheit_to_celsius_room_temperature(void) {
    // 77 F = 25 C
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 25.0f, fahrenheit_to_celsius(77.0f));
}

//==================================================
// Test cases for celsius_to_kelvin()
//==================================================

void test_celsius_to_kelvin_absolute_zero(void) {
    // -273.15 C = 0 K
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, celsius_to_kelvin(-273.15f));
}

void test_celsius_to_kelvin_freezing_point(void) {
    // 0 C = 273.15 K
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 273.15f, celsius_to_kelvin(0.0f));
}

void test_celsius_to_kelvin_boiling_point(void) {
    // 100 C = 373.15 K
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 373.15f, celsius_to_kelvin(100.0f));
}

//==================================================
// Test cases for kelvin_to_celsius()
//==================================================

void test_kelvin_to_celsius_absolute_zero(void) {
    // 0 K = -273.15 C
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -273.15f, kelvin_to_celsius(0.0f));
}

void test_kelvin_to_celsius_freezing_point(void) {
    // 273.15 K = 0 C
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, kelvin_to_celsius(273.15f));
}

void test_kelvin_to_celsius_boiling_point(void) {
    // 373.15 K = 100 C
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 100.0f, kelvin_to_celsius(373.15f));
}

//==================================================
// Test cases for get_temperature_status()
//==================================================

void test_get_temperature_status_cold(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Cold", get_temperature_status(9.9f)));
    TEST_ASSERT_EQUAL(0, strcmp("Cold", get_temperature_status(-10.0f)));
}

void test_get_temperature_status_normal(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Normal", get_temperature_status(10.0f))); // Lower boundary
    TEST_ASSERT_EQUAL(0, strcmp("Normal", get_temperature_status(15.0f))); // Mid-range
    TEST_ASSERT_EQUAL(0, strcmp("Normal", get_temperature_status(24.99f))); // Near upper boundary
}

void test_get_temperature_status_warm(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Warm", get_temperature_status(25.0f))); // Lower boundary
    TEST_ASSERT_EQUAL(0, strcmp("Warm", get_temperature_status(30.0f))); // Mid-range
    TEST_ASSERT_EQUAL(0, strcmp("Warm", get_temperature_status(34.99f))); // Near upper boundary
}

void test_get_temperature_status_hot(void) {
    TEST_ASSERT_EQUAL(0, strcmp("Hot", get_temperature_status(35.0f))); // Lower boundary
    TEST_ASSERT_EQUAL(0, strcmp("Hot", get_temperature_status(100.0f))); // Far above
}


// Main function to run all the tests
int main(void) {
    UNITY_BEGIN();

    // Run tests for get_temperature
    RUN_TEST(test_get_temperature_returns_fixed_value);

    // Run tests for is_temperature_safe
    RUN_TEST(test_is_temperature_safe_within_range);
    RUN_TEST(test_is_temperature_safe_at_lower_boundary);
    RUN_TEST(test_is_temperature_safe_at_upper_boundary);
    RUN_TEST(test_is_temperature_safe_below_range);
    RUN_TEST(test_is_temperature_safe_above_range);

    // Run tests for celsius_to_fahrenheit
    RUN_TEST(test_celsius_to_fahrenheit_zero);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_negative_value);
    RUN_TEST(test_celsius_to_fahrenheit_room_temperature);

    // Run tests for fahrenheit_to_celsius
    RUN_TEST(test_fahrenheit_to_celsius_freezing_point);
    RUN_TEST(test_fahrenheit_to_celsius_boiling_point);
    RUN_TEST(test_fahrenheit_to_celsius_negative_value);
    RUN_TEST(test_fahrenheit_to_celsius_room_temperature);

    // Run tests for celsius_to_kelvin
    RUN_TEST(test_celsius_to_kelvin_absolute_zero);
    RUN_TEST(test_celsius_to_kelvin_freezing_point);
    RUN_TEST(test_celsius_to_kelvin_boiling_point);
    
    // Run tests for kelvin_to_celsius
    RUN_TEST(test_kelvin_to_celsius_absolute_zero);
    RUN_TEST(test_kelvin_to_celsius_freezing_point);
    RUN_TEST(test_kelvin_to_celsius_boiling_point);
    
    // Run tests for get_temperature_status
    RUN_TEST(test_get_temperature_status_cold);
    RUN_TEST(test_get_temperature_status_normal);
    RUN_TEST(test_get_temperature_status_warm);
    RUN_TEST(test_get_temperature_status_hot);

    return UNITY_END();
}
