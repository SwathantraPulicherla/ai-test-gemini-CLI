
#include "unity.h"
#include "temperature_sensor.h"
#include <string.h>

// setUp and tearDown functions are required by Unity
void setUp(void) {
    // Set up code, if any, before each test
}

void tearDown(void) {
    // Clean up code, if any, after each test
}

// Test for get_temperature()
// Behavior: Always returns 25.5f
void test_get_temperature_should_return_fixed_value(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 25.5f, get_temperature());
}

// Test for is_temperature_safe()
// Behavior: Returns 1 if temp is in range [0.0, 100.0], otherwise returns 0
void test_is_temperature_safe_with_various_inputs(void) {
    // Test within safe range
    TEST_ASSERT_TRUE(is_temperature_safe(50.0f));
    
    // Test boundary conditions
    TEST_ASSERT_TRUE(is_temperature_safe(0.0f));    // Lower boundary
    TEST_ASSERT_TRUE(is_temperature_safe(100.0f));   // Upper boundary
    
    // Test just outside the safe range
    TEST_ASSERT_FALSE(is_temperature_safe(-0.1f));   // Just below lower boundary
    TEST_ASSERT_FALSE(is_temperature_safe(100.1f));  // Just above upper boundary
    
    // Test clearly unsafe values
    TEST_ASSERT_FALSE(is_temperature_safe(-200.0f)); // Negative temperature
    TEST_ASSERT_FALSE(is_temperature_safe(200.0f));  // High temperature
}

// Test for celsius_to_fahrenheit()
// Behavior: Returns (celsius * 9.0f / 5.0f) + 32.0f
void test_celsius_to_fahrenheit_conversions(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 32.0f, celsius_to_fahrenheit(0.0f));      // Freezing point
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 212.0f, celsius_to_fahrenheit(100.0f));   // Boiling point
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -40.0f, celsius_to_fahrenheit(-40.0f));  // Crossover point
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 77.0f, celsius_to_fahrenheit(25.0f));    // Room temperature
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 14.0f, celsius_to_fahrenheit(-10.0f));   // Negative temperature
}

// Test for fahrenheit_to_celsius()
// Behavior: Returns (fahrenheit - 32.0f) * 5.0f / 9.0f
void test_fahrenheit_to_celsius_conversions(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, fahrenheit_to_celsius(32.0f));      // Freezing point
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 100.0f, fahrenheit_to_celsius(212.0f));   // Boiling point
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -40.0f, fahrenheit_to_celsius(-40.0f));  // Crossover point
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 10.0f, fahrenheit_to_celsius(50.0f));    // Common temperature
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -10.0f, fahrenheit_to_celsius(14.0f));   // Negative temperature
}

// Test for celsius_to_kelvin()
// Behavior: Returns celsius + 273.15f
void test_celsius_to_kelvin_conversions(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 273.15f, celsius_to_kelvin(0.0f));        // Freezing point of water
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 373.15f, celsius_to_kelvin(100.0f));      // Boiling point of water
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, celsius_to_kelvin(-273.15f));      // Absolute zero
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 293.15f, celsius_to_kelvin(20.0f));       // Room temperature
}

// Test for kelvin_to_celsius()
// Behavior: Returns kelvin - 273.15f
void test_kelvin_to_celsius_conversions(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, kelvin_to_celsius(273.15f));        // Freezing point of water
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 100.0f, kelvin_to_celsius(373.15f));      // Boiling point of water
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -273.15f, kelvin_to_celsius(0.0f));      // Absolute zero
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 26.85f, kelvin_to_celsius(300.0f));       // Common temperature
}

// Test for get_temperature_status()
// Behavior: Returns "Cold" if temp < 10, "Normal" if 10-25, "Warm" if 25-35, "Hot" if > 35
void test_get_temperature_status_with_various_temps(void) {
    // Test "Cold" category
    TEST_ASSERT_EQUAL(0, strcmp("Cold", get_temperature_status(9.9f)));
    TEST_ASSERT_EQUAL(0, strcmp("Cold", get_temperature_status(0.0f)));
    TEST_ASSERT_EQUAL(0, strcmp("Cold", get_temperature_status(-50.0f)));

    // Test "Normal" category
    TEST_ASSERT_EQUAL(0, strcmp("Normal", get_temperature_status(10.0f)));  // Lower boundary
    TEST_ASSERT_EQUAL(0, strcmp("Normal", get_temperature_status(17.5f)));
    TEST_ASSERT_EQUAL(0, strcmp("Normal", get_temperature_status(24.9f)));  // Upper boundary - 1

    // Test "Warm" category
    TEST_ASSERT_EQUAL(0, strcmp("Warm", get_temperature_status(25.0f)));    // Lower boundary
    TEST_ASSERT_EQUAL(0, strcmp("Warm", get_temperature_status(30.0f)));
    TEST_ASSERT_EQUAL(0, strcmp("Warm", get_temperature_status(34.9f)));    // Upper boundary - 1

    // Test "Hot" category
    TEST_ASSERT_EQUAL(0, strcmp("Hot", get_temperature_status(35.0f)));     // Lower boundary
    TEST_ASSERT_EQUAL(0, strcmp("Hot", get_temperature_status(50.0f)));
    TEST_ASSERT_EQUAL(0, strcmp("Hot", get_temperature_status(150.0f)));
}

// Main function to run all tests
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_get_temperature_should_return_fixed_value);
    RUN_TEST(test_is_temperature_safe_with_various_inputs);
    RUN_TEST(test_celsius_to_fahrenheit_conversions);
    RUN_TEST(test_fahrenheit_to_celsius_conversions);
    RUN_TEST(test_celsius_to_kelvin_conversions);
    RUN_TEST(test_kelvin_to_celsius_conversions);
    RUN_TEST(test_get_temperature_status_with_various_temps);
    return UNITY_END();
}
