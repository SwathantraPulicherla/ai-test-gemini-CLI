#include <stdio.h>
#include <stdlib.h>
#include "temperature_utils.h"

// Function to calculate temperature difference between two readings
// Behavior: Returns the absolute difference between two temperature values
float calculate_temperature_difference(float temp1, float temp2) {
    float diff = temp1 - temp2;
    return (diff < 0.0f) ? -diff : diff;
}

// Function to check if temperature is within acceptable fluctuation range
// Behavior: Returns 1 if the temperature difference is within 5.0 degrees, otherwise returns 0
int is_temperature_stable(float current_temp, float previous_temp) {
    float diff = calculate_temperature_difference(current_temp, previous_temp);
    return (diff <= 5.0f);
}

// Function to get temperature trend as string
// Behavior: Returns "Rising" if current > previous, "Falling" if current < previous, "Stable" if equal
const char* get_temperature_trend(float current_temp, float previous_temp) {
    if (current_temp > previous_temp) {
        return "Rising";
    } else if (current_temp < previous_temp) {
        return "Falling";
    } else {
        return "Stable";
    }
}