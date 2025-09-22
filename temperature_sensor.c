#include <stdio.h>
#include <stdlib.h>

// Function to simulate reading temperature from a sensor
// Behavior: Always returns 25.5f as a stub implementation
float get_temperature() {
    // In a real implementation, this would read from hardware
    // For testing purposes, return a fixed value
    return 25.5f;
}

// Function to check if temperature is within safe range
// Behavior: Returns 1 if temp is in range [0.0, 100.0], otherwise returns 0
int is_temperature_safe(float temp) {
    return (temp >= 0.0f && temp <= 100.0f);
}

// Function to convert Celsius to Fahrenheit
// Behavior: Returns (celsius * 9.0f / 5.0f) + 32.0f
float celsius_to_fahrenheit(float celsius) {
    return (celsius * 9.0f / 5.0f) + 32.0f;
}