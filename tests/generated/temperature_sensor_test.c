
#include "unity.h"
#include "temperature_sensor.h"
#include <string.h>

// setUp and tearDown functions are optional but good practice
void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

// Test for get_temperature()
void test_get_temperature_should_return_fixed_stub_value(void) {
    // Behavior: Always returns 25.5f as a stub implementation
    float expected_temp = 25.5f;
    float delta = 0.001f;
    TEST_ASSERT_FLOAT_WITHIN(delta, expected_temp, get_temperature());
}

// Tests for is_temperature_safe()
void test_is_temperature_safe_should_return_true_for_mid_range_value(void) {
    // Behavior: Returns 1 if temp is in range [0.0, 100.0]
    TEST_ASSERT_TRUE(is_temperature_safe(50.0f));
}

void test_is_temperature_safe_should_return_true_for_lower_boundary(void) {
    // Behavior: Returns 1 if temp is in range [0.0, 100.0]
    TEST_ASSERT_TRUE(is_temperature_safe(0.0f));
}

void test_is_temperature_safe_should_return_true_for_upper_boundary(void) {
    // Behavior: Returns 1 if temp is in range [0.0, 100.0]
    TEST_ASSERT_TRUE(is_temperature_safe(100.0f));
}

void test_is_temperature_safe_should_return_false_for_value_below_range(void) {
    // Behavior: Returns 0 if temp is outside range [0.0, 100.0]
    TEST_ASSERT_FALSE(is_temperature_safe(-0.1f));
    TEST_ASSERT_FALSE(is_temperature_safe(-10.0f));
}

void test_is_temperature_safe_should_return_false_for_value_above_range(void) {
    // Behavior: Returns 0 if temp is outside range [0.0, 100.0]
    TEST_ASSERT_FALSE(is_temperature_safe(100.1f));
    TEST_ASSERT_FALSE(is_temperature_safe(110.0f));
}

// Tests for celsius_to_fahrenheit()
void test_celsius_to_fahrenheit_should_convert_zero_correctly(void) {
    // 0 C = 32 F
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 32.0f, celsius_to_fahrenheit(0.0f));
}

void test_celsius_to_fahrenheit_should_convert_boiling_point_correctly(void) {
    // 100 C = 212 F
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 212.0f, celsius_to_fahrenheit(100.0f));
}

void test_celsius_to_fahrenheit_should_convert_negative_value_correctly(void) {
    // -40 C = -40 F
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -40.0f, celsius_to_fahrenheit(-40.0f));
}

// Tests for fahrenheit_to_celsius()
void test_fahrenheit_to_celsius_should_convert_freezing_point_correctly(void) {
    // 32 F = 0 C
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, fahrenheit_to_celsius(32.0f));
}

void test_fahrenheit_to_celsius_should_convert_boiling_point_correctly(void) {
    // 212 F = 100 C
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 100.0f, fahrenheit_to_celsius(212.0f));
}

void test_fahrenheit_to_celsius_should_convert_negative_value_correctly(void) {
    // -40 F = -40 C
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -40.0f, fahrenheit_to_celsius(-40.0f));
}

// Tests for celsius_to_kelvin()
void test_celsius_to_kelvin_should_convert_zero_celsius_correctly(void) {
    // 0 C = 273.15 K
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 273.15f, celsius_to_kelvin(0.0f));
}

void test_celsius_to_kelvin_should_convert_absolute_zero_correctly(void) {
    // -273.15 C = 0 K
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, celsius_to_kelvin(-273.15f));
}

// Tests for kelvin_to_celsius()
void test_kelvin_to_celsius_should_convert_absolute_zero_correctly(void) {
    // 0 K = -273.15 C
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -273.15f, kelvin_to_celsius(0.0f));
}

void test_kelvin_to_celsius_should_convert_freezing_point_correctly(void) {
    // 273.15 K = 0 C
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, kelvin_to_celsius(273.15f));
}

// Tests for get_temperature_status()
void test_get_temperature_status_should_return_cold(void) {
    // Behavior: "Cold" if temp < 10
    TEST_ASSERT_EQUAL(0, strcmp("Cold", get_temperature_status(9.9f)));
    TEST_ASSERT_EQUAL(0, strcmp("Cold", get_temperature_status(0.0f)));
    TEST_ASSERT_EQUAL(0, strcmp("Cold", get_temperature_status(-10.0f)));
}

void test_get_temperature_status_should_return_normal(void) {
    // Behavior: "Normal" if 10 <= temp < 25
    TEST_ASSERT_EQUAL(0, strcmp("Normal", get_temperature_status(10.0f))); // Lower boundary
    TEST_ASSERT_EQUAL(0, strcmp("Normal", get_temperature_status(15.0f)));
    TEST_ASSERT_EQUAL(0, strcmp("Normal", get_temperature_status(24.9f))); // Upper boundary
}

void test_get_temperature_status_should_return_warm(void) {
    // Behavior: "Warm" if 25 <= temp < 35
    TEST_ASSERT_EQUAL(0, strcmp("Warm", get_temperature_status(25.0f))); // Lower boundary
    TEST_ASSERT_EQUAL(0, strcmp("Warm", get_temperature_status(30.0f)));
    TEST_ASSERT_EQUAL(0, strcmp("Warm", get_temperature_status(34.9f))); // Upper boundary
}

void test_get_temperature_status_should_return_hot(void) {
    // Behavior: "Hot" if temp >= 35
    TEST_ASSERT_EQUAL(0, strcmp("Hot", get_temperature_status(35.0f))); // Lower boundary
    TEST_ASSERT_EQUAL(0, strcmp("Hot", get_temperature_status(50.0f)));
    TEST_ASSERT_EQUAL(0, strcmp("Hot", get_temperature_status(100.0f)));
}

// Main function to run all tests
int main(void) {
    UNITY_BEGIN();

    // Tests for temperature_sensor.c
    RUN_TEST(test_get_temperature_should_return_fixed_stub_value);
    
    RUN_TEST(test_is_temperature_safe_should_return_true_for_mid_range_value);
    RUN_TEST(test_is_temperature_safe_should_return_true_for_lower_boundary);
    RUN_TEST(test_is_temperature_safe_should_return_true_for_upper_boundary);
    RUN_TEST(test_is_temperature_safe_should_return_false_for_value_below_range);
    RUN_TEST(test_is_temperature_safe_should_return_false_for_value_above_range);

    RUN_TEST(test_celsius_to_fahrenheit_should_convert_zero_correctly);
    RUN_TEST(test_celsius_to_fahrenheit_should_convert_boiling_point_correctly);
    RUN_TEST(test_celsius_to_fahrenheit_should_convert_negative_value_correctly);
    
    RUN_TEST(test_fahrenheit_to_celsius_should_convert_freezing_point_correctly);
    RUN_TEST(test_fahrenheit_to_celsius_should_convert_boiling_point_correctly);
    RUN_TEST(test_fahrenheit_to_celsius_should_convert_negative_value_correctly);
    
    RUN_TEST(test_celsius_to_kelvin_should_convert_zero_celsius_correctly);
    RUN_TEST(test_celsius_to_kelvin_should_convert_absolute_zero_correctly);

    RUN_TEST(test_kelvin_to_celsius_should_convert_absolute_zero_correctly);
    RUN_TEST(test_kelvin_to_celsius_should_convert_freezing_point_correctly);

    RUN_TEST(test_get_temperature_status_should_return_cold);
    RUN_TEST(test_get_temperature_status_should_return_normal);
    RUN_TEST(test_get_temperature_status_should_return_warm);
    RUN_TEST(test_get_temperature_status_should_return_hot);

    return UNITY_END();
}
