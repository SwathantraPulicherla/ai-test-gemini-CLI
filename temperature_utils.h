#ifndef TEMPERATURE_UTILS_H
#define TEMPERATURE_UTILS_H

// Function to calculate temperature difference between two readings
float calculate_temperature_difference(float temp1, float temp2);

// Function to check if temperature is within acceptable fluctuation range
int is_temperature_stable(float current_temp, float previous_temp);

// Function to get temperature trend as string
const char* get_temperature_trend(float current_temp, float previous_temp);

#endif // TEMPERATURE_UTILS_H