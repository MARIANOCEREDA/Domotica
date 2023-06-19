cmake_minimum_required(VERSION 3.22)
project(Domotica)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenSSL REQUIRED)
find_library(MQTT_LIB libpaho-mqttpp3.so REQUIRED)

set(PAHO_MQTT_LIBRARY_PATH /home/user/libs/paho.mqtt.cpp)

if (MQTT_LIB)
    message("Found Paho-mqtt client library")
else ()
    message("Not found Paho-mqtt client library")
endif (MQTT_LIB)

include_directories(
        src/common/include
        src/libs/easyloggingpp/src
)

add_executable(Domotica src/target/main.cpp src/target/include/main.h)

add_subdirectory(src/libs/easyloggingpp)

target_include_directories(${PROJECT_NAME} PRIVATE src/libs/easyloggingpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${PAHO_MQTT_LIBRARY_PATH}/src/mqtt)

target_link_directories(${PROJECT_NAME} PRIVATE src/libs/easyloggingpp)
target_link_directories(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} easyloggingpp)
target_link_libraries(${PROJECT_NAME} ${MQTT_LIB})
