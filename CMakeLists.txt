cmake_minimum_required(VERSION 3.10)
project(TemperatureSensor)

# Set C standard
set(CMAKE_C_STANDARD 99)

# Include directories
include_directories(unity/src)

# Source files for library
set(LIB_SOURCES temperature_sensor.c)

# Create static library
add_library(temperature_sensor_lib STATIC ${LIB_SOURCES})

# Create executable
add_executable(temperature_sensor main.c)
target_link_libraries(temperature_sensor temperature_sensor_lib)

# Test executable
add_executable(test_temperature_sensor test/test_temperature_sensor.c unity/src/unity.c)
target_link_libraries(test_temperature_sensor temperature_sensor_lib)

# Generated test executables
file(GLOB GENERATED_TESTS "tests/generated/*_test.c")
foreach(TEST_FILE ${GENERATED_TESTS})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_FILE} unity/src/unity.c)
    target_link_libraries(${TEST_NAME} temperature_sensor_lib)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()

# Enable testing
enable_testing()
add_test(NAME TemperatureSensorTests COMMAND test_temperature_sensor)