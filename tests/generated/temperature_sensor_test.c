
#include "unity.h"
#include "temperature_sensor.h"

void setUp(void) {}
void tearDown(void) {}

void test_get_temperature(void) {
  float temp = get_temperature();
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 25.5f, temp);
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


void test_celsius_to_fahrenheit(void) {
  float celsius = 0.0f;
  float fahrenheit = celsius_to_fahrenheit(celsius);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 32.0f, fahrenheit);

  celsius = 100.0f;
  fahrenheit = celsius_to_fahrenheit(celsius);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 212.0f, fahrenheit);

  celsius = 25.0f;
  fahrenheit = celsius_to_fahrenheit(celsius);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 77.0f, fahrenheit);
}

void test_fahrenheit_to_celsius(void) {
  float fahrenheit = 32.0f;
  float celsius = fahrenheit_to_celsius(fahrenheit);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, celsius);

  fahrenheit = 212.0f;
  celsius = fahrenheit_to_celsius(fahrenheit);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 100.0f, celsius);

  fahrenheit = 77.0f;
  celsius = fahrenheit_to_celsius(fahrenheit);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 25.0f, celsius);
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

void test_get_temperature_status_boundary(void){
    TEST_ASSERT_EQUAL_STRING("Normal", get_temperature_status(10.0f));
    TEST_ASSERT_EQUAL_STRING("Warm", get_temperature_status(25.0f));
}


int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_get_temperature);
  RUN_TEST(test_is_temperature_safe_within_range);
  RUN_TEST(test_is_temperature_safe_below_range);
  RUN_TEST(test_is_temperature_safe_above_range);
  RUN_TEST(test_is_temperature_safe_boundary_lower);
  RUN_TEST(test_is_temperature_safe_boundary_upper);
  RUN_TEST(test_celsius_to_fahrenheit);
  RUN_TEST(test_fahrenheit_to_celsius);
  RUN_TEST(test_get_temperature_status_cold);
  RUN_TEST(test_get_temperature_status_normal);
  RUN_TEST(test_get_temperature_status_warm);
  RUN_TEST(test_get_temperature_status_hot);
  RUN_TEST(test_get_temperature_status_boundary);
  return UNITY_END();
}
