#include <stdio.h>
#include "temperature_sensor.h"

int main() {
    float temp = get_temperature();
    printf("Current temperature: %.2f°C\n", temp);
    printf("Current temperature: %.2f°F\n", celsius_to_fahrenheit(temp));
    if (is_temperature_safe(temp)) {
        printf("Temperature is within safe range.\n");
    } else {
        printf("Temperature is out of safe range!\n");
    }
    return 0;
}