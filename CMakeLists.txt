cmake_minimum_required(VERSION 3.18)

project(Domotica)

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

#set(PAHO_MQTT_LIBRARY_PATH /home/mariano/workspace/projects/domotica/libs/paho.mqtt.cpp)
#set(PAHO_MQTT_C_LIBRARY_PATH /home/mariano/workspace/projects/domotica/libs/paho.mqtt.c)

find_package(OpenSSL REQUIRED)

# Find mqtt libraries
find_library(MQTT_LIB libpaho-mqttpp3.so REQUIRED)
find_library(MQTT_LIB_C libpaho-mqtt3c.so REQUIRED)

if (MQTT_LIB)
    message("Found Paho-mqtt-cpp client library")
else ()
    message("Not found Paho-mqtt-cpp client library")
endif (MQTT_LIB)

if (MQTT_LIB_C)
    message("Found Paho-mqtt-c client library")
else ()
    message("Not found Paho-mqtt-c client library")
endif (MQTT_LIB_C)

# Pigpiod library
find_library(pigpio_LIBRARY
        NAMES libpigpio.so
        HINTS /usr/local/lib)

find_library(pigpiod_if_LIBRARY
        NAMES libpigpiod_if.so
        HINTS /usr/local/lib)

find_library(pigpiod_if2_LIBRARY
        NAMES libpigpiod_if2.so
        HINTS /usr/local/lib)

# Set the pigpio variables to plural form to make them accessible for
# the paramount cmake modules.
set(pigpio_INCLUDE_DIRS ${pigpio_INCLUDE_DIR})
set(pigpio_INCLUDES     ${pigpio_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)

include_directories(
        src/common/include
        src/target/include
        src/util
        src/libs/easyloggingpp/src
        pigpio_INCLUDE_DIRS
        pigpio_INCUDES
)

set(HEADER_FILES
        src/target/include/main.h
        src/common/include/MqttClient.h
        src/util/MqttData.h)

set(SOURCE_FILES
        src/common/MqttClient.cpp)

add_executable(Domotica src/target/main.cpp ${HEADER_FILES} ${SOURCE_FILES})

add_subdirectory(src/libs/easyloggingpp)

target_include_directories(${PROJECT_NAME} PRIVATE src/libs/easyloggingpp)
#target_include_directories(${PROJECT_NAME} PRIVATE ${PAHO_MQTT_C_LIBRARY_PATH}/src/mqtt)
#target_include_directories(${PROJECT_NAME} PRIVATE ${PAHO_MQTT_LIBRARY_PATH}/src/mqtt)

target_link_directories(${PROJECT_NAME} PRIVATE src/libs/easyloggingpp)

target_link_libraries(${PROJECT_NAME} easyloggingpp)
target_link_libraries(${PROJECT_NAME} ${MQTT_LIB_C})
target_link_libraries(${PROJECT_NAME} ${MQTT_LIB})

