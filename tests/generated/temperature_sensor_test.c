
#include "unity.h"
#include "temperature_sensor.h"

void setUp(void) {}
void tearDown(void) {}

void test_get_temperature_returns_25_5(void) {
  float temp = get_temperature();
  TEST_ASSERT_FLOAT_WITHIN(0.001, 25.5f, temp);
}

void test_is_temperature_safe_within_range(void) {
  TEST_ASSERT_EQUAL(1, is_temperature_safe(25.5f));
  TEST_ASSERT_EQUAL(1, is_temperature_safe(0.0f));
  TEST_ASSERT_EQUAL(1, is_temperature_safe(100.0f));
}

void test_is_temperature_safe_below_range(void) {
  TEST_ASSERT_EQUAL(0, is_temperature_safe(-1.0f));
}

void test_is_temperature_safe_above_range(void) {
  TEST_ASSERT_EQUAL(0, is_temperature_safe(100.1f));
}

void test_celsius_to_fahrenheit_zero_degrees(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.001, 32.0f, celsius_to_fahrenheit(0.0f));
}

void test_celsius_to_fahrenheit_positive_degrees(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.001, 77.0f, celsius_to_fahrenheit(25.0f));
}

void test_celsius_to_fahrenheit_negative_degrees(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.001, 14.0f, celsius_to_fahrenheit(-10.0f));
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001, 212.0f, celsius_to_fahrenheit(100.0f));
}


int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_get_temperature_returns_25_5);
  RUN_TEST(test_is_temperature_safe_within_range);
  RUN_TEST(test_is_temperature_safe_below_range);
  RUN_TEST(test_is_temperature_safe_above_range);
  RUN_TEST(test_celsius_to_fahrenheit_zero_degrees);
  RUN_TEST(test_celsius_to_fahrenheit_positive_degrees);
  RUN_TEST(test_celsius_to_fahrenheit_negative_degrees);
  RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
  return UNITY_END();
}
