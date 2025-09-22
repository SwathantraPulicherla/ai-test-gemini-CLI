
#include "unity.h"
#include "temperature_sensor.h"

void setUp(void) {}
void tearDown(void) {}

void test_get_temperature_returns_25_5(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.001, 25.5f, get_temperature());
}

void test_is_temperature_safe_within_range(void) {
  TEST_ASSERT_EQUAL(1, is_temperature_safe(25.0f));
}

void test_is_temperature_safe_below_range(void) {
  TEST_ASSERT_EQUAL(0, is_temperature_safe(-5.0f));
}

void test_is_temperature_safe_above_range(void) {
  TEST_ASSERT_EQUAL(0, is_temperature_safe(105.0f));
}

void test_is_temperature_safe_boundary_lower(void) {
  TEST_ASSERT_EQUAL(1, is_temperature_safe(0.0f));
}

void test_is_temperature_safe_boundary_upper(void) {
  TEST_ASSERT_EQUAL(1, is_temperature_safe(100.0f));
}


void test_celsius_to_fahrenheit_zero(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.001, 32.0f, celsius_to_fahrenheit(0.0f));
}

void test_celsius_to_fahrenheit_positive(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.001, 77.0f, celsius_to_fahrenheit(25.0f));
}

void test_celsius_to_fahrenheit_negative(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.001, 14.0f, celsius_to_fahrenheit(-10.0f));
}

void test_fahrenheit_to_celsius_zero(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.001, -17.778f, fahrenheit_to_celsius(0.0f));
}

void test_fahrenheit_to_celsius_positive(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.001, 25.0f, fahrenheit_to_celsius(77.0f));
}

void test_fahrenheit_to_celsius_negative(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001, -10.0f, fahrenheit_to_celsius(14.0f));
}

void test_get_temperature_status_cold(void) {
  TEST_ASSERT_EQUAL_STRING("Cold", get_temperature_status(5.0f));
}

void test_get_temperature_status_normal(void) {
  TEST_ASSERT_EQUAL_STRING("Normal", get_temperature_status(15.0f));
}

void test_get_temperature_status_warm(void) {
  TEST_ASSERT_EQUAL_STRING("Warm", get_temperature_status(30.0f));
}

void test_get_temperature_status_hot(void) {
  TEST_ASSERT_EQUAL_STRING("Hot", get_temperature_status(40.0f));
}

void test_get_temperature_status_boundary_normal_warm(void){
    TEST_ASSERT_EQUAL_STRING("Warm", get_temperature_status(25.0f));
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_get_temperature_returns_25_5);
  RUN_TEST(test_is_temperature_safe_within_range);
  RUN_TEST(test_is_temperature_safe_below_range);
  RUN_TEST(test_is_temperature_safe_above_range);
  RUN_TEST(test_is_temperature_safe_boundary_lower);
  RUN_TEST(test_is_temperature_safe_boundary_upper);
  RUN_TEST(test_celsius_to_fahrenheit_zero);
  RUN_TEST(test_celsius_to_fahrenheit_positive);
  RUN_TEST(test_celsius_to_fahrenheit_negative);
  RUN_TEST(test_fahrenheit_to_celsius_zero);
  RUN_TEST(test_fahrenheit_to_celsius_positive);
  RUN_TEST(test_fahrenheit_to_celsius_negative);
  RUN_TEST(test_get_temperature_status_cold);
  RUN_TEST(test_get_temperature_status_normal);
  RUN_TEST(test_get_temperature_status_warm);
  RUN_TEST(test_get_temperature_status_hot);
  RUN_TEST(test_get_temperature_status_boundary_normal_warm);
  return UNITY_END();
}
