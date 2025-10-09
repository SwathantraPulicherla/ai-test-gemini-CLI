
#include "unity.h"
#include "temperature_utils.h"

// Note: The source code for temperature_sensor.h functions was not provided.
// As per the instructions to "TEST ACTUAL IMPLEMENTATIONS", only functions
// from temperature_utils.c will be tested.

// Optional: setUp and tearDown functions
void setUp(void) {
    // Set up code, if any, run before each test
}

void tearDown(void) {
    // Clean up code, if any, run after each test
}

//--- Tests for calculate_temperature_difference ---

void test_calculate_temperature_difference_positive_values(void) {
    // Behavior: Returns the absolute difference between two temperature values
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 5.5f, calculate_temperature_difference(25.5f, 20.0f));
}

void test_calculate_temperature_difference_order_independent(void) {
    // The result should be the same regardless of parameter order
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 5.5f, calculate_temperature_difference(20.0f, 25.5f));
}

void test_calculate_temperature_difference_with_negative_values(void) {
    // Test with both temperatures being negative
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 5.0f, calculate_temperature_difference(-10.0f, -15.0f));
}

void test_calculate_temperature_difference_mixed_sign_values(void) {
    // Test with one positive and one negative temperature
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 15.0f, calculate_temperature_difference(10.0f, -5.0f));
}

void test_calculate_temperature_difference_zero_difference(void) {
    // Test with identical temperatures
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, calculate_temperature_difference(22.3f, 22.3f));
}

void test_calculate_temperature_difference_with_zero(void) {
    // Test with one temperature being zero
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 10.0f, calculate_temperature_difference(10.0f, 0.0f));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 10.0f, calculate_temperature_difference(0.0f, -10.0f));
}


//--- Tests for is_temperature_stable ---

void test_is_temperature_stable_well_within_range(void) {
    // Behavior: Returns 1 if diff <= 5.0
    // 25.0 - 22.0 = 3.0, which is <= 5.0
    TEST_ASSERT_EQUAL(1, is_temperature_stable(25.0f, 22.0f));
}

void test_is_temperature_stable_at_boundary(void) {
    // Difference is exactly 5.0, which is stable
    TEST_ASSERT_EQUAL(1, is_temperature_stable(30.0f, 25.0f));
}

void test_is_temperature_stable_just_outside_boundary(void) {
    // Behavior: Returns 0 if diff > 5.0
    // 30.1 - 25.0 = 5.1, which is > 5.0
    TEST_ASSERT_EQUAL(0, is_temperature_stable(30.1f, 25.0f));
}

void test_is_temperature_stable_large_difference(void) {
    // Difference is large, should not be stable
    TEST_ASSERT_EQUAL(0, is_temperature_stable(50.0f, 20.0f));
}

void test_is_temperature_stable_zero_difference(void) {
    // Zero difference is the most stable case
    TEST_ASSERT_EQUAL(1, is_temperature_stable(25.0f, 25.0f));
}

void test_is_temperature_stable_negative_values_stable(void) {
    // Test with negative values within the stable range
    // -10 - (-12) = 2.0, which is <= 5.0
    TEST_ASSERT_EQUAL(1, is_temperature_stable(-10.0f, -12.0f));
}

void test_is_temperature_stable_negative_values_unstable(void) {
    // Test with negative values outside the stable range
    // -10 - (-20) = 10.0, which is > 5.0
    TEST_ASSERT_EQUAL(0, is_temperature_stable(-10.0f, -20.0f));
}

//--- Tests for get_temperature_trend ---

void test_get_temperature_trend_rising(void) {
    // Behavior: Returns "Rising" if current > previous
    const char* trend = get_temperature_trend(25.5f, 25.4f);
    TEST_ASSERT_EQUAL_STRING("Rising", trend);
}

void test_get_temperature_trend_falling(void) {
    // Behavior: Returns "Falling" if current < previous
    const char* trend = get_temperature_trend(20.1f, 20.2f);
    TEST_ASSERT_EQUAL_STRING("Falling", trend);
}

void test_get_temperature_trend_stable(void) {
    // Behavior: Returns "Stable" if equal
    const char* trend = get_temperature_trend(15.0f, 15.0f);
    TEST_ASSERT_EQUAL_STRING("Stable", trend);
}

void test_get_temperature_trend_rising_from_negative(void) {
    // Test rising trend with negative numbers
    const char* trend = get_temperature_trend(-5.0f, -10.0f);
    TEST_ASSERT_EQUAL_STRING("Rising", trend);
}

void test_get_temperature_trend_falling_to_negative(void) {
    // Test falling trend with negative numbers
    const char* trend = get_temperature_trend(-15.0f, -10.0f);
    TEST_ASSERT_EQUAL_STRING("Falling", trend);
}

// Main function to run all tests
int main(void) {
    UNITY_BEGIN();

    // Tests for calculate_temperature_difference
    RUN_TEST(test_calculate_temperature_difference_positive_values);
    RUN_TEST(test_calculate_temperature_difference_order_independent);
    RUN_TEST(test_calculate_temperature_difference_with_negative_values);
    RUN_TEST(test_calculate_temperature_difference_mixed_sign_values);
    RUN_TEST(test_calculate_temperature_difference_zero_difference);
    RUN_TEST(test_calculate_temperature_difference_with_zero);

    // Tests for is_temperature_stable
    RUN_TEST(test_is_temperature_stable_well_within_range);
    RUN_TEST(test_is_temperature_stable_at_boundary);
    RUN_TEST(test_is_temperature_stable_just_outside_boundary);
    RUN_TEST(test_is_temperature_stable_large_difference);
    RUN_TEST(test_is_temperature_stable_zero_difference);
    RUN_TEST(test_is_temperature_stable_negative_values_stable);
    RUN_TEST(test_is_temperature_stable_negative_values_unstable);

    // Tests for get_temperature_trend
    RUN_TEST(test_get_temperature_trend_rising);
    RUN_TEST(test_get_temperature_trend_falling);
    RUN_TEST(test_get_temperature_trend_stable);
    RUN_TEST(test_get_temperature_trend_rising_from_negative);
    RUN_TEST(test_get_temperature_trend_falling_to_negative);

    return UNITY_END();
}
