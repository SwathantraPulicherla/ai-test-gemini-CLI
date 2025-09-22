
#include "unity.h"
#include "temperature_sensor.h"

void setUp(void) {} // optional setup function
void tearDown(void) {} // optional teardown function

void test_get_temperature_positive(void) {
  // Assuming get_temperature() returns a reasonable value.  Replace with expected value if known.
  float temp = get_temperature();
  TEST_ASSERT_TRUE(temp >= -100.0 && temp <= 100.0); // Example range, adjust as needed
}


void test_is_temperature_safe_within_range(void) {
  TEST_ASSERT_EQUAL(1, is_temperature_safe(25.0)); // Example safe temperature
}

void test_is_temperature_safe_below_range(void) {
  TEST_ASSERT_EQUAL(0, is_temperature_safe(-50.0)); // Example unsafe temperature
}

void test_is_temperature_safe_above_range(void) {
  TEST_ASSERT_EQUAL(0, is_temperature_safe(150.0)); // Example unsafe temperature
}


void test_celsius_to_fahrenheit_positive(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.01, 77.0, celsius_to_fahrenheit(25.0)); 
}

void test_celsius_to_fahrenheit_zero(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.01, 32.0, celsius_to_fahrenheit(0.0));
}

void test_celsius_to_fahrenheit_negative(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.01, 14.0, celsius_to_fahrenheit(-10.0));
}


void test_fahrenheit_to_celsius_positive(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.01, 25.0, fahrenheit_to_celsius(77.0));
}

void test_fahrenheit_to_celsius_zero(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.01, 0.0, fahrenheit_to_celsius(32.0));
}

void test_fahrenheit_to_celsius_negative(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.01, -10.0, fahrenheit_to_celsius(14.0));
}


void test_get_temperature_status_safe(void) {
  const char* status = get_temperature_status(25.0); //Example safe temp
  TEST_ASSERT_EQUAL_STRING("Safe", status); //Assumes "Safe" is returned for safe temps. Adjust as needed.
}

void test_get_temperature_status_unsafe(void) {
  const char* status = get_temperature_status(150.0); // Example unsafe temp
  TEST_ASSERT_EQUAL_STRING("Unsafe", status); //Assumes "Unsafe" is returned for unsafe temps. Adjust as needed.
}


int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_get_temperature_positive);
  RUN_TEST(test_is_temperature_safe_within_range);
  RUN_TEST(test_is_temperature_safe_below_range);
  RUN_TEST(test_is_temperature_safe_above_range);
  RUN_TEST(test_celsius_to_fahrenheit_positive);
  RUN_TEST(test_celsius_to_fahrenheit_zero);
  RUN_TEST(test_celsius_to_fahrenheit_negative);
  RUN_TEST(test_fahrenheit_to_celsius_positive);
  RUN_TEST(test_fahrenheit_to_celsius_zero);
  RUN_TEST(test_fahrenheit_to_celsius_negative);
  RUN_TEST(test_get_temperature_status_safe);
  RUN_TEST(test_get_temperature_status_unsafe);
  return UNITY_END();
}
