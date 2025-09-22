
#include "unity.h"
#include "temperature_sensor.h"
#include <string.h>

// setUp and tearDown functions are called before and after each test
void setUp(void)
{
    // No setup needed for these tests
}

void tearDown(void)
{
    // No teardown needed for these tests
}

// Tests for get_temperature
void test_get_temperature_should_return_fixed_value(void)
{
    // Behavior: Always returns 25.5f as a stub implementation
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 25.5f, get_temperature());
}

// Tests for is_temperature_safe
void test_is_temperature_safe_should_return_true_at_lower_bound(void)
{
    // Behavior: Returns 1 if temp is in range [0.0, 100.0]
    TEST_ASSERT_TRUE(is_temperature_safe(0.0f));
}

void test_is_temperature_safe_should_return_true_at_upper_bound(void)
{
    // Behavior: Returns 1 if temp is in range [0.0, 100.0]
    TEST_ASSERT_TRUE(is_temperature_safe(100.0f));
}

void test_is_temperature_safe_should_return_true_within_range(void)
{
    // Behavior: Returns 1 if temp is in range [0.0, 100.0]
    TEST_ASSERT_TRUE(is_temperature_safe(50.0f));
}

void test_is_temperature_safe_should_return_false_below_range(void)
{
    // Behavior: Returns 0 if temp is outside range [0.0, 100.0]
    TEST_ASSERT_FALSE(is_temperature_safe(-0.1f));
}

void test_is_temperature_safe_should_return_false_above_range(void)
{
    // Behavior: Returns 0 if temp is outside range [0.0, 100.0]
    TEST_ASSERT_FALSE(is_temperature_safe(100.1f));
}

// Tests for celsius_to_fahrenheit
void test_celsius_to_fahrenheit_for_freezing_point(void)
{
    // 0°C should be 32°F
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 32.0f, celsius_to_fahrenheit(0.0f));
}

void test_celsius_to_fahrenheit_for_boiling_point(void)
{
    // 100°C should be 212°F
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 212.0f, celsius_to_fahrenheit(100.0f));
}

void test_celsius_to_fahrenheit_for_negative_temperature(void)
{
    // -40°C should be -40°F
    TEST_ASSERT_FLOAT_WITHIN(0.01f, -40.0f, celsius_to_fahrenheit(-40.0f));
}

void test_celsius_to_fahrenheit_for_body_temperature(void)
{
    // 37°C should be 98.6°F
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 98.6f, celsius_to_fahrenheit(37.0f));
}

// Tests for fahrenheit_to_celsius
void test_fahrenheit_to_celsius_for_freezing_point(void)
{
    // 32°F should be 0°C
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 0.0f, fahrenheit_to_celsius(32.0f));
}

void test_fahrenheit_to_celsius_for_boiling_point(void)
{
    // 212°F should be 100°C
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 100.0f, fahrenheit_to_celsius(212.0f));
}

void test_fahrenheit_to_celsius_for_negative_temperature(void)
{
    // -40°F should be -40°C
    TEST_ASSERT_FLOAT_WITHIN(0.01f, -40.0f, fahrenheit_to_celsius(-40.0f));
}

void test_fahrenheit_to_celsius_for_body_temperature(void)
{
    // 98.6°F should be 37°C
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 37.0f, fahrenheit_to_celsius(98.6f));
}

// Tests for celsius_to_kelvin
void test_celsius_to_kelvin_for_absolute_zero(void)
{
    // -273.15°C should be 0K
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 0.0f, celsius_to_kelvin(-273.15f));
}

void test_celsius_to_kelvin_for_freezing_point(void)
{
    // 0°C should be 273.15K
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 273.15f, celsius_to_kelvin(0.0f));
}

void test_celsius_to_kelvin_for_boiling_point(void)
{
    // 100°C should be 373.15K
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 373.15f, celsius_to_kelvin(100.0f));
}

// Tests for get_temperature_status
void test_get_temperature_status_should_return_cold(void)
{
    TEST_ASSERT_EQUAL(0, strcmp("Cold", get_temperature_status(9.99f)));
    TEST_ASSERT_EQUAL(0, strcmp("Cold", get_temperature_status(-20.0f)));
}

void test_get_temperature_status_should_return_normal(void)
{
    TEST_ASSERT_EQUAL(0, strcmp("Normal", get_temperature_status(10.0f)));
    TEST_ASSERT_EQUAL(0, strcmp("Normal", get_temperature_status(24.99f)));
}

void test_get_temperature_status_should_return_warm(void)
{
    TEST_ASSERT_EQUAL(0, strcmp("Warm", get_temperature_status(25.0f)));
    TEST_ASSERT_EQUAL(0, strcmp("Warm", get_temperature_status(34.99f)));
}

void test_get_temperature_status_should_return_hot(void)
{
    TEST_ASSERT_EQUAL(0, strcmp("Hot", get_temperature_status(35.0f)));
    TEST_ASSERT_EQUAL(0, strcmp("Hot", get_temperature_status(100.0f)));
}

// Main function to run all tests
int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_get_temperature_should_return_fixed_value);

    RUN_TEST(test_is_temperature_safe_should_return_true_at_lower_bound);
    RUN_TEST(test_is_temperature_safe_should_return_true_at_upper_bound);
    RUN_TEST(test_is_temperature_safe_should_return_true_within_range);
    RUN_TEST(test_is_temperature_safe_should_return_false_below_range);
    RUN_TEST(test_is_temperature_safe_should_return_false_above_range);

    RUN_TEST(test_celsius_to_fahrenheit_for_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_for_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_for_negative_temperature);
    RUN_TEST(test_celsius_to_fahrenheit_for_body_temperature);

    RUN_TEST(test_fahrenheit_to_celsius_for_freezing_point);
    RUN_TEST(test_fahrenheit_to_celsius_for_boiling_point);
    RUN_TEST(test_fahrenheit_to_celsius_for_negative_temperature);
    RUN_TEST(test_fahrenheit_to_celsius_for_body_temperature);

    RUN_TEST(test_celsius_to_kelvin_for_absolute_zero);
    RUN_TEST(test_celsius_to_kelvin_for_freezing_point);
    RUN_TEST(test_celsius_to_kelvin_for_boiling_point);

    RUN_TEST(test_get_temperature_status_should_return_cold);
    RUN_TEST(test_get_temperature_status_should_return_normal);
    RUN_TEST(test_get_temperature_status_should_return_warm);
    RUN_TEST(test_get_temperature_status_should_return_hot);

    return UNITY_END();
}
