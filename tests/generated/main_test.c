
#include "unity.h"
#include "temperature_sensor.h"

void setUp(void) {}
void tearDown(void) {}

void test_get_temperature_normal(void) {
  // Expecting a reasonable temperature reading.  Adjust expected value as needed.
  float temp = get_temperature();
  TEST_ASSERT_FLOAT_WITHIN(0.1, 25.0, temp); //Example, adjust as needed based on your sensor's output.
}

void test_is_temperature_safe_within_range(void) {
  TEST_ASSERT_EQUAL(1, is_temperature_safe(25.0)); 
}

void test_is_temperature_safe_below_range(void) {
  TEST_ASSERT_EQUAL(0, is_temperature_safe(0.0));
}

void test_is_temperature_safe_above_range(void) {
  TEST_ASSERT_EQUAL(0, is_temperature_safe(100.0));
}


void test_celsius_to_fahrenheit_normal(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.1, 77.0, celsius_to_fahrenheit(25.0));
}

void test_celsius_to_fahrenheit_freezing(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.1, 32.0, celsius_to_fahrenheit(0.0));
}

void test_celsius_to_fahrenheit_boiling(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.1, 212.0, celsius_to_fahrenheit(100.0));
}

void test_fahrenheit_to_celsius_normal(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.1, 25.0, fahrenheit_to_celsius(77.0));
}

void test_fahrenheit_to_celsius_freezing(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.1, 0.0, fahrenheit_to_celsius(32.0));
}

void test_fahrenheit_to_celsius_boiling(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.1, 100.0, fahrenheit_to_celsius(212.0));
}

void test_celsius_to_kelvin_normal(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.1, 298.15, celsius_to_kelvin(25.0));
}

void test_celsius_to_kelvin_freezing(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.1, 273.15, celsius_to_kelvin(0.0));
}

void test_celsius_to_kelvin_boiling(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.1, 373.15, celsius_to_kelvin(100.0));
}

void test_get_temperature_status_safe(void) {
  const char* status = get_temperature_status(25.0);
  TEST_ASSERT_EQUAL_STRING("Safe", status);
}

void test_get_temperature_status_unsafe(void) {
    const char* status = get_temperature_status(100.0);
    TEST_ASSERT_EQUAL_STRING("Unsafe", status);
}


int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_get_temperature_normal);
  RUN_TEST(test_is_temperature_safe_within_range);
  RUN_TEST(test_is_temperature_safe_below_range);
  RUN_TEST(test_is_temperature_safe_above_range);
  RUN_TEST(test_celsius_to_fahrenheit_normal);
  RUN_TEST(test_celsius_to_fahrenheit_freezing);
  RUN_TEST(test_celsius_to_fahrenheit_boiling);
  RUN_TEST(test_fahrenheit_to_celsius_normal);
  RUN_TEST(test_fahrenheit_to_celsius_freezing);
  RUN_TEST(test_fahrenheit_to_celsius_boiling);
  RUN_TEST(test_celsius_to_kelvin_normal);
  RUN_TEST(test_celsius_to_kelvin_freezing);
  RUN_TEST(test_celsius_to_kelvin_boiling);
  RUN_TEST(test_get_temperature_status_safe);
  RUN_TEST(test_get_temperature_status_unsafe);
  return UNITY_END();
}
