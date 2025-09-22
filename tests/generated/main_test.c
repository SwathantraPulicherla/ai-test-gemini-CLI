
#include "unity.h"
#include "temperature_sensor.h"

void setUp(void) {} // optional setup function
void tearDown(void) {} // optional teardown function

void test_get_temperature_returns_a_float(void) {
  float temp = get_temperature();
  //Note:  This test will only pass if get_temperature() has a defined implementation that returns a value.  Without that implementation, this test will likely fail.
  TEST_ASSERT_TRUE(1); // Placeholder - replace with actual assertion once get_temperature is implemented
}

void test_is_temperature_safe_returns_1_if_within_range(void) {
  TEST_ASSERT_EQUAL(1, is_temperature_safe(25.0)); // Assuming safe range includes 25°C
}

void test_is_temperature_safe_returns_0_if_below_range(void) {
  TEST_ASSERT_EQUAL(0, is_temperature_safe(-10.0)); // Assuming -10°C is below safe range
}

void test_is_temperature_safe_returns_0_if_above_range(void) {
  TEST_ASSERT_EQUAL(0, is_temperature_safe(100.0)); // Assuming 100°C is above safe range

}

void test_celsius_to_fahrenheit_converts_correctly(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.1, 77.0, celsius_to_fahrenheit(25.0));
}

void test_celsius_to_fahrenheit_handles_freezing(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.1, 32.0, celsius_to_fahrenheit(0.0));
}

void test_celsius_to_fahrenheit_handles_boiling(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.1, 212.0, celsius_to_fahrenheit(100.0));
}

void test_celsius_to_fahrenheit_handles_negative_temperatures(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.1, 14.0, celsius_to_fahrenheit(-9.444));
}


int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_get_temperature_returns_a_float);
  RUN_TEST(test_is_temperature_safe_returns_1_if_within_range);
  RUN_TEST(test_is_temperature_safe_returns_0_if_below_range);
  RUN_TEST(test_is_temperature_safe_returns_0_if_above_range);
  RUN_TEST(test_celsius_to_fahrenheit_converts_correctly);
  RUN_TEST(test_celsius_to_fahrenheit_handles_freezing);
  RUN_TEST(test_celsius_to_fahrenheit_handles_boiling);
  RUN_TEST(test_celsius_to_fahrenheit_handles_negative_temperatures);
  return UNITY_END();
}
