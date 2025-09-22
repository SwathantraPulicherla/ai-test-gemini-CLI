
#include "unity.h"
#include "temperature_sensor.h"

// Implement get_temperature() and is_temperature_safe() in temperature_sensor.c for testing

void setUp(void) {}

void tearDown(void) {}

void test_get_temperature_normal(void) {
    float temp = get_temperature();
    //  Replace with appropriate expected value and tolerance based on sensor simulation
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 25.0f, temp); 
}

void test_get_temperature_edge_case(void) {
    // Simulate edge cases as needed in get_temperature() for testing
    float temp = get_temperature();
    // Replace with appropriate expected value and tolerance
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, temp);
}


void test_is_temperature_safe_within_range(void) {
    TEST_ASSERT_TRUE(is_temperature_safe(25.0f));
}

void test_is_temperature_safe_lower_boundary(void) {
    // Adjust 10.0f based on your safe temperature range definition
    TEST_ASSERT_TRUE(is_temperature_safe(10.0f)); 
}

void test_is_temperature_safe_upper_boundary(void) {
    // Adjust 30.0f based on your safe temperature range definition
    TEST_ASSERT_TRUE(is_temperature_safe(30.0f));
}

void test_is_temperature_safe_below_range(void) {
    // Adjust 5.0f based on your safe temperature range definition
    TEST_ASSERT_FALSE(is_temperature_safe(5.0f));
}

void test_is_temperature_safe_above_range(void) {
    // Adjust 35.0f based on your safe temperature range definition
    TEST_ASSERT_FALSE(is_temperature_safe(35.0f));
}


int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_get_temperature_normal);
    RUN_TEST(test_get_temperature_edge_case);
    RUN_TEST(test_is_temperature_safe_within_range);
    RUN_TEST(test_is_temperature_safe_lower_boundary);
    RUN_TEST(test_is_temperature_safe_upper_boundary);
    RUN_TEST(test_is_temperature_safe_below_range);
    RUN_TEST(test_is_temperature_safe_above_range);
    return UNITY_END();
}
