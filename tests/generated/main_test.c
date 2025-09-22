
#include "unity.h"
#include "temperature_sensor.h"

void setUp(void) {} // optional setup function
void tearDown(void) {} // optional teardown function

void test_get_temperature_normal(void) {
  // Expecting a reasonable temperature reading.  Adjust expectation as needed based on your sensor's expected output.
  float temp = get_temperature();
  TEST_ASSERT_FLOAT_WITHIN(0.1, 25.0, temp); //Example, adjust 25.0 as needed
}

void test_get_temperature_edge_case_low(void) {
    //Simulate a low temperature reading. Adjust expectation as needed
    float temp = get_temperature();
    TEST_ASSERT_FLOAT_WITHIN(0.1, 0.0, temp); //Example, adjust 0.0 as needed

}

void test_get_temperature_edge_case_high(void) {
    //Simulate a high temperature reading. Adjust expectation as needed
    float temp = get_temperature();
    TEST_ASSERT_FLOAT_WITHIN(0.1, 100.0, temp); //Example, adjust 100.0 as needed
}


void test_is_temperature_safe_within_range(void) {
  TEST_ASSERT_EQUAL(1, is_temperature_safe(25.0)); //Example, adjust range as needed
}

void test_is_temperature_safe_below_range(void) {
  TEST_ASSERT_EQUAL(0, is_temperature_safe(-10.0)); //Example, adjust range as needed
}

void test_is_temperature_safe_above_range(void) {
  TEST_ASSERT_EQUAL(0, is_temperature_safe(100.0)); //Example, adjust range as needed
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


int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_get_temperature_normal);
  RUN_TEST(test_get_temperature_edge_case_low);
  RUN_TEST(test_get_temperature_edge_case_high);
  RUN_TEST(test_is_temperature_safe_within_range);
  RUN_TEST(test_is_temperature_safe_below_range);
  RUN_TEST(test_is_temperature_safe_above_range);
  RUN_TEST(test_celsius_to_fahrenheit_normal);
  RUN_TEST(test_celsius_to_fahrenheit_freezing);
  RUN_TEST(test_celsius_to_fahrenheit_boiling);
  return UNITY_END();
}
