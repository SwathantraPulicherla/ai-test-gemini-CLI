
#include "unity.h"
#include "temperature_sensor.h"

void setUp(void) {}

void tearDown(void) {}

void test_get_temperature_returns_value(void) {
    float temp = get_temperature();
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 25.5f, temp);
}

void test_is_temperature_safe_within_range(void) {
    TEST_ASSERT_TRUE(is_temperature_safe(50.0f));
}

void test_is_temperature_safe_lower_bound(void) {
    TEST_ASSERT_TRUE(is_temperature_safe(0.0f));
}

void test_is_temperature_safe_upper_bound(void) {
    TEST_ASSERT_TRUE(is_temperature_safe(100.0f));
}

void test_is_temperature_safe_below_lower_bound(void) {
    TEST_ASSERT_FALSE(is_temperature_safe(-1.0f));
}

void test_is_temperature_safe_above_upper_bound(void) {
    TEST_ASSERT_FALSE(is_temperature_safe(101.0f));
}

void test_is_temperature_safe_near_lower_bound(void) {
    TEST_ASSERT_TRUE(is_temperature_safe(0.1f));
}

void test_is_temperature_safe_near_upper_bound(void) {
    TEST_ASSERT_TRUE(is_temperature_safe(99.9f));
}


int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_get_temperature_returns_value);
    RUN_TEST(test_is_temperature_safe_within_range);
    RUN_TEST(test_is_temperature_safe_lower_bound);
    RUN_TEST(test_is_temperature_safe_upper_bound);
    RUN_TEST(test_is_temperature_safe_below_lower_bound);
    RUN_TEST(test_is_temperature_safe_above_upper_bound);
    RUN_TEST(test_is_temperature_safe_near_lower_bound);
    RUN_TEST(test_is_temperature_safe_near_upper_bound);
    return UNITY_END();
}
