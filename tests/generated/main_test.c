
#include "unity.h"
#include "temperature_sensor.h"
#include <string.h>

// setUp and tearDown are run before and after each test
void setUp(void) {
    // No setup needed for these tests
}

void tearDown(void) {
    // No teardown needed for these tests
}

// Since the implementation of get_temperature is a simulation and could be non-deterministic,
// we can only test that it returns a value within a very broad, plausible range.
void test_get_temperature_returns_plausible_value(void) {
    float temp = get_temperature();
    // A plausible range for a general purpose sensor in Celsius
    TEST_ASSERT_TRUE(temp >= -100.0f && temp <= 200.0f);
}

// Test suite for is_temperature_safe
// NOTE: We must assume a "safe" range. For these tests, we assume [0.0, 50.0] Celsius.
void test_is_temperature_safe_within_range(void) {
    TEST_ASSERT_TRUE(is_temperature_safe(25.0f));
}

void test_is_temperature_safe_at_lower_boundary(void) {
    TEST_ASSERT_TRUE(is_temperature_safe(0.0f));
}

void test_is_temperature_safe_at_upper_boundary(void) {
    TEST_ASSERT_TRUE(is_temperature_safe(50.0f));
}

void test_is_temperature_safe_below_range(void) {
    TEST_ASSERT_FALSE(is_temperature_safe(-10.0f));
}

void test_is_temperature_safe_just_below_range(void) {
    TEST_ASSERT_FALSE(is_temperature_safe(-0.01f));
}

void test_is_temperature_safe_above_range(void) {
    TEST_ASSERT_FALSE(is_temperature_safe(60.0f));
}

void test_is_temperature_safe_just_above_range(void) {
    TEST_ASSERT_FALSE(is_temperature_safe(50.01f));
}

// Test suite for celsius_to_fahrenheit
void test_celsius_to_fahrenheit_freezing_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 32.0f, celsius_to_fahrenheit(0.0f));
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 212.0f, celsius_to_fahrenheit(100.0f));
}

void test_celsius_to_fahrenheit_negative_value(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, -4.0f, celsius_to_fahrenheit(-20.0f));
}

void test_celsius_to_fahrenheit_crossover_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, -40.0f, celsius_to_fahrenheit(-40.0f));
}

// Test suite for fahrenheit_to_celsius
void test_fahrenheit_to_celsius_freezing_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 0.0f, fahrenheit_to_celsius(32.0f));
}

void test_fahrenheit_to_celsius_boiling_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 100.0f, fahrenheit_to_celsius(212.0f));
}

void test_fahrenheit_to_celsius_negative_value(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, -17.78f, fahrenheit_to_celsius(0.0f));
}

void test_fahrenheit_to_celsius_crossover_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, -40.0f, fahrenheit_to_celsius(-40.0f));
}

// Test suite for celsius_to_kelvin
void test_celsius_to_kelvin_absolute_zero(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 0.0f, celsius_to_kelvin(-273.15f));
}

void test_celsius_to_kelvin_freezing_point_water(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 273.15f, celsius_to_kelvin(0.0f));
}

void test_celsius_to_kelvin_positive_value(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 298.15f, celsius_to_kelvin(25.0f));
}

// Test suite for kelvin_to_celsius
void test_kelvin_to_celsius_absolute_zero(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, -273.15f, kelvin_to_celsius(0.0f));
}

void test_kelvin_to_celsius_freezing_point_water(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 0.0f, kelvin_to_celsius(273.15f));
}

void test_kelvin_to_celsius_positive_value(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 26.85f, kelvin_to_celsius(300.0f));
}

// Test suite for get_temperature_status
// NOTE: We must assume the status logic. For these tests, we assume:
// temp < 10 is "Cold", 10 <= temp <= 30 is "Normal", temp > 30 is "Hot".
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
    const char* status = get_temperature_status(35.0f);
    TEST_ASSERT_NOT_NULL(status);
    TEST_ASSERT_EQUAL(0, strcmp("Hot", status));
}

void test_get_temperature_status_boundary_cold_to_normal(void) {
    const char* status = get_temperature_status(10.0f);
    TEST_ASSERT_NOT_NULL(status);
    TEST_ASSERT_EQUAL(0, strcmp("Normal", status));
}

void test_get_temperature_status_boundary_normal_to_hot(void) {
    const char* status = get_temperature_status(30.0f);
    TEST_ASSERT_NOT_NULL(status);
    TEST_ASSERT_EQUAL(0, strcmp("Normal", status));
}

void test_get_temperature_status_boundary_just_below_normal(void) {
    const char* status = get_temperature_status(9.99f);
    TEST_ASSERT_NOT_NULL(status);
    TEST_ASSERT_EQUAL(0, strcmp("Cold", status));
}

void test_get_temperature_status_boundary_just_above_hot(void) {
    const char* status = get_temperature_status(30.01f);
    TEST_ASSERT_NOT_NULL(status);
    TEST_ASSERT_EQUAL(0, strcmp("Hot", status));
}

// Main test runner function
int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_get_temperature_returns_plausible_value);

    RUN_TEST(test_is_temperature_safe_within_range);
    RUN_TEST(test_is_temperature_safe_at_lower_boundary);
    RUN_TEST(test_is_temperature_safe_at_upper_boundary);
    RUN_TEST(test_is_temperature_safe_below_range);
    RUN_TEST(test_is_temperature_safe_just_below_range);
    RUN_TEST(test_is_temperature_safe_above_range);
    RUN_TEST(test_is_temperature_safe_just_above_range);

    RUN_TEST(test_celsius_to_fahrenheit_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_negative_value);
    RUN_TEST(test_celsius_to_fahrenheit_crossover_point);

    RUN_TEST(test_fahrenheit_to_celsius_freezing_point);
    RUN_TEST(test_fahrenheit_to_celsius_boiling_point);
    RUN_TEST(test_fahrenheit_to_celsius_negative_value);
    RUN_TEST(test_fahrenheit_to_celsius_crossover_point);

    RUN_TEST(test_celsius_to_kelvin_absolute_zero);
    RUN_TEST(test_celsius_to_kelvin_freezing_point_water);
    RUN_TEST(test_celsius_to_kelvin_positive_value);

    RUN_TEST(test_kelvin_to_celsius_absolute_zero);
    RUN_TEST(test_kelvin_to_celsius_freezing_point_water);
    RUN_TEST(test_kelvin_to_celsius_positive_value);

    RUN_TEST(test_get_temperature_status_cold);
    RUN_TEST(test_get_temperature_status_normal);
    RUN_TEST(test_get_temperature_status_hot);
    RUN_TEST(test_get_temperature_status_boundary_cold_to_normal);
    RUN_TEST(test_get_temperature_status_boundary_normal_to_hot);
    RUN_TEST(test_get_temperature_status_boundary_just_below_normal);
    RUN_TEST(test_get_temperature_status_boundary_just_above_hot);

    return UNITY_END();
}
