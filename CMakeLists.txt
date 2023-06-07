cmake_minimum_required(VERSION 3.18)
project(Domotica)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenSSL REQUIRED)

target_include_directories(
        src/common/include
        src/libs/easyloggingpp/src/
        src/libs/mosquitto-2.0.15/include
)

set(HEADER_FILES)

set(COMMON_FILES)

add_executable(cpp-iot-car src/target/main.cpp ${HEADER_FILES} ${COMMON_FILES})

add_executable(Domotica src/target/main.cpp)

add_subdirectory(libs/mosquitto-2.0.15)
add_subdirectory(libs/easyloggingpp)

target_include_directories(${PROJECT_NAME} PRIVATE libs/mosquitto-2.0.15/lib/cpp)
target_include_directories(${PROJECT_NAME} PRIVATE libs/easyloggingpp)

target_link_directories(${PROJECT_NAME} PRIVATE libs/mosquitto-2.0.15)
target_link_directories(${PROJECT_NAME} PRIVATE libs/easyloggingpp)

target_link_libraries(${PROJECT_NAME} mosquittopp)
target_link_libraries(${PROJECT_NAME} easyloggingpp)
