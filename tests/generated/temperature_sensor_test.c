
#include "unity.h"
#include "temperature_sensor.h"

void setUp(void) {}
void tearDown(void) {}

void test_get_temperature_returns_25_5(void) {
  float temp = get_temperature();
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 25.5f, temp);
}

void test_is_temperature_safe_within_range(void) {
  TEST_ASSERT_EQUAL(1, is_temperature_safe(50.0f));
}

void test_is_temperature_safe_below_range(void) {
  TEST_ASSERT_EQUAL(0, is_temperature_safe(-10.0f));
}

void test_is_temperature_safe_above_range(void) {
  TEST_ASSERT_EQUAL(0, is_temperature_safe(110.0f));
}

void test_is_temperature_safe_lower_bound(void) {
  TEST_ASSERT_EQUAL(1, is_temperature_safe(0.0f));
}

void test_is_temperature_safe_upper_bound(void) {
  TEST_ASSERT_EQUAL(1, is_temperature_safe(100.0f));
}

void test_celsius_to_fahrenheit_zero_degrees(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 32.0f, celsius_to_fahrenheit(0.0f));
}

void test_celsius_to_fahrenheit_positive_degrees(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 68.0f, celsius_to_fahrenheit(20.0f));
}

void test_celsius_to_fahrenheit_negative_degrees(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 14.0f, celsius_to_fahrenheit(-10.0f));
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 212.0f, celsius_to_fahrenheit(100.0f));
}

void test_celsius_to_fahrenheit_freezing_point(void){
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 32.0f, celsius_to_fahrenheit(0.0f));
}
