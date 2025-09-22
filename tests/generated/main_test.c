
#include "unity.h"
#include "temperature_sensor.h"

void setUp(void) {} // optional setup function
void tearDown(void) {} // optional teardown function

void test_get_temperature_normal_range(void) {
  //  Assume get_temperature() returns a value between -10 and 40 for testing purposes.  Adjust as needed for your actual implementation.
  float temp = get_temperature();
  TEST_ASSERT_FLOAT_WITHIN(0.1, -10, temp); //Example, replace with appropriate range
  TEST_ASSERT_FLOAT_WITHIN(0.1, 40, temp); //Example, replace with appropriate range

}

void test_get_temperature_edge_cases(void){
    // Add tests for edge cases if your get_temperature() function has any.
}

void test_is_temperature_safe_within_range(void) {
  TEST_ASSERT_EQUAL(1, is_temperature_safe(25)); // Example safe temperature
}

void test_is_temperature_safe_below_range(void) {
  TEST_ASSERT_EQUAL(0, is_temperature_safe(-50)); // Example unsafe temperature
}

void test_is_temperature_safe_above_range(void) {
  TEST_ASSERT_EQUAL(0, is_temperature_safe(100)); // Example unsafe temperature
}

void test_celsius_to_fahrenheit_freezing(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.1, 32.0, celsius_to_fahrenheit(0));
}

void test_celsius_to_fahrenheit_boiling(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.1, 212.0, celsius_to_fahrenheit(100));
}

void test_celsius_to_fahrenheit_normal(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.1, 68.0, celsius_to_fahrenheit(20));
}


int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_get_temperature_normal_range);
  RUN_TEST(test_get_temperature_edge_cases);
  RUN_TEST(test_is_temperature_safe_within_range);
  RUN_TEST(test_is_temperature_safe_below_range);
  RUN_TEST(test_is_temperature_safe_above_range);
  RUN_TEST(test_celsius_to_fahrenheit_freezing);
  RUN_TEST(test_celsius_to_fahrenheit_boiling);
  RUN_TEST(test_celsius_to_fahrenheit_normal);
  return UNITY_END();
}
