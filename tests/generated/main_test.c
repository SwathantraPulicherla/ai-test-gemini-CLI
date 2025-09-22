
#include "unity.h"
#include "temperature_sensor.h"

void setUp(void) {}
void tearDown(void) {}

void test_get_temperature_positive(void) {
  // Assuming get_temperature() returns a positive value in normal operation.  Adjust expected value as needed.
  float temp = get_temperature();
  TEST_ASSERT_FLOAT_WITHIN(0.1, 25.0, temp); //Example, adjust 25.0 as needed
}


void test_get_temperature_within_range(void) {
    float temp = get_temperature();
    TEST_ASSERT_TRUE(temp >= -100.0 && temp <= 100.0); //Example range, adjust as needed.
}


void test_is_temperature_safe_within_range(void) {
    TEST_ASSERT_EQUAL(1, is_temperature_safe(25.0)); //Example safe temperature. Adjust as needed.
}

void test_is_temperature_safe_below_range(void) {
    TEST_ASSERT_EQUAL(0, is_temperature_safe(-50.0)); //Example unsafe temperature. Adjust as needed.
}

void test_is_temperature_safe_above_range(void) {
    TEST_ASSERT_EQUAL(0, is_temperature_safe(150.0)); //Example unsafe temperature. Adjust as needed.
}


void test_celsius_to_fahrenheit_positive(void) {
    float celsius = 25.0;
    float fahrenheit = celsius_to_fahrenheit(celsius);
    TEST_ASSERT_FLOAT_WITHIN(0.1, 77.0, fahrenheit);
}

void test_celsius_to_fahrenheit_zero(void) {
    float celsius = 0.0;
    float fahrenheit = celsius_to_fahrenheit(celsius);
    TEST_ASSERT_FLOAT_WITHIN(0.1, 32.0, fahrenheit);
}

void test_celsius_to_fahrenheit_negative(void) {
    float celsius = -10.0;
    float fahrenheit = celsius_to_fahrenheit(celsius);
    TEST_ASSERT_FLOAT_WITHIN(0.1, 14.0, fahrenheit);
}


int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_get_temperature_positive);
    RUN_TEST(test_get_temperature_within_range);
    RUN_TEST(test_is_temperature_safe_within_range);
    RUN_TEST(test_is_temperature_safe_below_range);
    RUN_TEST(test_is_temperature_safe_above_range);
    RUN_TEST(test_celsius_to_fahrenheit_positive);
    RUN_TEST(test_celsius_to_fahrenheit_zero);
    RUN_TEST(test_celsius_to_fahrenheit_negative);
    return UNITY_END();
}
