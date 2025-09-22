
#include "unity.h"
#include "temperature_sensor.h"

void setUp(void) {}
void tearDown(void) {}

void test_get_temperature(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.001, 25.5f, get_temperature());
}

void test_is_temperature_safe_within_range(void) {
  TEST_ASSERT_EQUAL(1, is_temperature_safe(25.0f));
}

void test_is_temperature_safe_below_range(void) {
  TEST_ASSERT_EQUAL(0, is_temperature_safe(-10.0f));
}

void test_is_temperature_safe_above_range(void) {
  TEST_ASSERT_EQUAL(0, is_temperature_safe(110.0f));
}

void test_is_temperature_safe_at_lower_bound(void) {
    TEST_ASSERT_EQUAL(1, is_temperature_safe(0.0f));
}

void test_is_temperature_safe_at_upper_bound(void) {
    TEST_ASSERT_EQUAL(1, is_temperature_safe(100.0f));
}


void test_celsius_to_fahrenheit(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.001, 77.0f, celsius_to_fahrenheit(25.0f));
}

void test_celsius_to_fahrenheit_freezing(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001, 32.0f, celsius_to_fahrenheit(0.0f));
}

void test_celsius_to_fahrenheit_boiling(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001, 212.0f, celsius_to_fahrenheit(100.0f));
}


void test_fahrenheit_to_celsius(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.001, 25.0f, fahrenheit_to_celsius(77.0f));
}

void test_fahrenheit_to_celsius_freezing(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001, 0.0f, fahrenheit_to_celsius(32.0f));
}

void test_fahrenheit_to_celsius_boiling(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.001, 100.0f, fahrenheit_to_celsius(212.0f));
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

void test_get_temperature_status_boundary_normal_warm(void) {
    TEST_ASSERT_EQUAL_STRING("Warm", get_temperature_status(25.0f));
}


int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_get_temperature);
  RUN_TEST(test_is_temperature_safe_within_range);
  RUN_TEST(test_is_temperature_safe_below_range);
  RUN_TEST(test_is_temperature_safe_above_range);
  RUN_TEST(test_is_temperature_safe_at_lower_bound);
  RUN_TEST(test_is_temperature_safe_at_upper_bound);
  RUN_TEST(test_celsius_to_fahrenheit);
  RUN_TEST(test_celsius_to_fahrenheit_freezing);
  RUN_TEST(test_celsius_to_fahrenheit_boiling);
  RUN_TEST(test_fahrenheit_to_celsius);
  RUN_TEST(test_fahrenheit_to_celsius_freezing);
  RUN_TEST(test_fahrenheit_to_celsius_boiling);
  RUN_TEST(test_get_temperature_status_cold);
  RUN_TEST(test_get_temperature_status_normal);
  RUN_TEST(test_get_temperature_status_warm);
  RUN_TEST(test_get_temperature_status_hot);
  RUN_TEST(test_get_temperature_status_boundary_normal_warm);
  return UNITY_END();
}
