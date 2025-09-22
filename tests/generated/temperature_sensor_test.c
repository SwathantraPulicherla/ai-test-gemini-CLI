
#include "unity.h"
#include "temperature_sensor.h"

void setUp(void) {}
void tearDown(void) {}

void test_get_temperature_returns_25_5(void) {
  float temp = get_temperature();
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 25.5f, temp);
}

void test_is_temperature_safe_within_range(void) {
  TEST_ASSERT_EQUAL(1, is_temperature_safe(50.0f));
}

void test_is_temperature_safe_below_range(void) {
  TEST_ASSERT_EQUAL(0, is_temperature_safe(-10.0f));
}

void test_is_temperature_safe_above_range(void) {
  TEST_ASSERT_EQUAL(0, is_temperature_safe(110.0f));
}

void test_is_temperature_safe_lower_bound(void) {
  TEST_ASSERT_EQUAL(1, is_temperature_safe(0.0f));
}

void test_is_temperature_safe_upper_bound(void) {
  TEST_ASSERT_EQUAL(1, is_temperature_safe(100.0f));
}



int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_get_temperature_returns_25_5);
    RUN_TEST(test_is_temperature_safe_within_range);
    RUN_TEST(test_is_temperature_safe_below_range);
    RUN_TEST(test_is_temperature_safe_above_range);
    RUN_TEST(test_is_temperature_safe_lower_bound);
    RUN_TEST(test_is_temperature_safe_upper_bound);
    return UNITY_END();
}