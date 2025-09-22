#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

// Function to simulate reading temperature from a sensor
float get_temperature();

// Function to check if temperature is within safe range
int is_temperature_safe(float temp);

// Function to convert Celsius to Fahrenheit
float celsius_to_fahrenheit(float celsius);

#endif // TEMPERATURE_SENSOR_H