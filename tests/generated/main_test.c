
#include "unity.h"
#include "temperature_sensor.h"

void setUp(void) {} // optional setup function
void tearDown(void) {} // optional teardown function

void test_get_temperature_normal(void) {
  // Expect a reasonable temperature reading.  Replace with a realistic expectation.
  float temp = get_temperature();
  TEST_ASSERT_FLOAT_WITHIN(0.1, 25.0, temp); // Adjust expected value as needed
}

void test_get_temperature_edge_case_high(void) {
    // Simulate a high temperature reading.  Adjust as needed for your sensor's range.
    // This test might need adjustment depending on your get_temperature() implementation.
  float temp = get_temperature();
  TEST_ASSERT_FLOAT_WITHIN(0.1, 100.0, temp); //Adjust as needed for edge case
}

void test_get_temperature_edge_case_low(void) {
    //Simulate a low temperature reading. Adjust as needed for your sensor's range.
    // This test might need adjustment depending on your get_temperature() implementation.
  float temp = get_temperature();
  TEST_ASSERT_FLOAT_WITHIN(0.1, -10.0, temp); // Adjust as needed for edge case

}



void test_is_temperature_safe_within_range(void) {
  TEST_ASSERT_EQUAL(1, is_temperature_safe(20.0));
}

void test_is_temperature_safe_below_range(void) {
  TEST_ASSERT_EQUAL(0, is_temperature_safe(0.0)); // Assuming 0 is below the safe range
}

void test_is_temperature_safe_above_range(void) {
  TEST_ASSERT_EQUAL(0, is_temperature_safe(100.0)); // Assuming 100 is above the safe range
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

void test_get_temperature_status_normal(void) {
  // Adjust expected string based on your implementation
  const char* status = get_temperature_status(20.0);
  TEST_ASSERT_EQUAL_STRING("Normal", status); //Example, adjust as needed
}

void test_get_temperature_status_high(void) {
    // Adjust expected string based on your implementation
  const char* status = get_temperature_status(100.0);
  TEST_ASSERT_EQUAL_STRING("High", status); //Example, adjust as needed
}

void test_get_temperature_status_low(void) {
    // Adjust expected string based on your implementation
  const char* status = get_temperature_status(0.0);
  TEST_ASSERT_EQUAL_STRING("Low", status); //Example, adjust as needed
}


int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_get_temperature_normal);
  RUN_TEST(test_get_temperature_edge_case_high);
  RUN_TEST(test_get_temperature_edge_case_low);
  RUN_TEST(test_is_temperature_safe_within_range);
  RUN_TEST(test_is_temperature_safe_below_range);
  RUN_TEST(test_is_temperature_safe_above_range);
  RUN_TEST(test_celsius_to_fahrenheit_normal);
  RUN_TEST(test_celsius_to_fahrenheit_freezing);
  RUN_TEST(test_celsius_to_fahrenheit_boiling);
  RUN_TEST(test_fahrenheit_to_celsius_normal);
  RUN_TEST(test_fahrenheit_to_celsius_freezing);
  RUN_TEST(test_fahrenheit_to_celsius_boiling);
  RUN_TEST(test_get_temperature_status_normal);
  RUN_TEST(test_get_temperature_status_high);
  RUN_TEST(test_get_temperature_status_low);
  return UNITY_END();
}
