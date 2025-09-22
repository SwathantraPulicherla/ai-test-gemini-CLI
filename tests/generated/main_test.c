
#include "unity.h"
#include "temperature_sensor.h"

void setUp(void) {} // optional setup function
void tearDown(void) {} // optional teardown function

void test_get_temperature_normal(void) {
  // This test relies on the implementation of get_temperature().  
  //  Replace with a more robust test if possible, given constraints.
  float temp = get_temperature();
  // Test assumes get_temperature() returns a reasonable value. Adjust as needed.
  TEST_ASSERT_FLOAT_WITHIN(0.1, 20.0, temp); //Example, adjust based on expected range
}


void test_is_temperature_safe_within_range(void) {
  TEST_ASSERT_TRUE(is_temperature_safe(20.0)); //Example, adjust based on safe range definition
}

void test_is_temperature_safe_below_range(void) {
  TEST_ASSERT_FALSE(is_temperature_safe(0.0)); //Example, adjust based on safe range definition
}

void test_is_temperature_safe_above_range(void) {
  TEST_ASSERT_FALSE(is_temperature_safe(100.0)); //Example, adjust based on safe range definition
}

void test_celsius_to_fahrenheit_normal(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.1, 68.0, celsius_to_fahrenheit(20.0));
}

void test_celsius_to_fahrenheit_freezing(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.1, 32.0, celsius_to_fahrenheit(0.0));
}

void test_celsius_to_fahrenheit_boiling(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.1, 212.0, celsius_to_fahrenheit(100.0));
}

void test_fahrenheit_to_celsius_normal(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.1, 20.0, fahrenheit_to_celsius(68.0));
}

void test_fahrenheit_to_celsius_freezing(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.1, 0.0, fahrenheit_to_celsius(32.0));
}

void test_fahrenheit_to_celsius_boiling(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.1, 100.0, fahrenheit_to_celsius(212.0));
}


void test_get_temperature_status_safe(void) {
  const char* status = get_temperature_status(20.0); //Example, adjust based on safe range definition
  TEST_ASSERT_NOT_NULL(status);
  TEST_ASSERT_EQUAL_STRING("Safe", status); //Example, adjust based on string returned
}

void test_get_temperature_status_unsafe(void) {
  const char* status = get_temperature_status(100.0); //Example, adjust based on safe range definition
  TEST_ASSERT_NOT_NULL(status);
  TEST_ASSERT_EQUAL_STRING("Unsafe", status); //Example, adjust based on string returned

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
  RUN_TEST(test_get_temperature_status_safe);
  RUN_TEST(test_get_temperature_status_unsafe);
  return UNITY_END();
}
