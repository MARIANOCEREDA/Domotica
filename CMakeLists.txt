cmake_minimum_required(VERSION 3.18)
project(Domotica)

set(CMAKE_CXX_STANDARD 17)

set(PAHO_MQTT_LIBRARY_PATH /home/user/libs/paho.mqtt.cpp)
set(PAHO_MQTT_C_LIBRARY_PATH /home/user/libs/paho.mqtt.c)

find_package(OpenSSL REQUIRED)
find_library(MQTT_LIB libpaho-mqttpp3.so PATHS ${PAHO_MQTT_LIBRARY_PATH}/build/src REQUIRED)
find_library(MQTT_LIB_C libpaho-mqtt3c.so PATHS ${PAHO_MQTT_C_LIBRARY_PATH}/build/src REQUIRED)

if (MQTT_LIB)
    message("Found Paho-mqtt client library")
else ()
    message("Not found Paho-mqtt client library")
endif (MQTT_LIB)

include_directories(
        src/common/include
        src/target/include
        src/util
        src/libs/easyloggingpp/src
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
target_include_directories(${PROJECT_NAME} PRIVATE ${PAHO_MQTT_LIBRARY_PATH}/src/mqtt)
target_include_directories(${PROJECT_NAME} PRIVATE ${PAHO_MQTT_LIBRARY_PATH}/src/mqtt)

target_link_directories(${PROJECT_NAME} PRIVATE src/libs/easyloggingpp)

target_link_libraries(${PROJECT_NAME} easyloggingpp)
target_link_libraries(${PROJECT_NAME} ${MQTT_LIB_C})
target_link_libraries(${PROJECT_NAME} ${MQTT_LIB})

