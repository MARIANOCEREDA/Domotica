cmake_minimum_required(VERSION 3.18)
project(Domotica)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenSSL REQUIRED)

include_directories(
        src/common/include
        src/libs/easyloggingpp/src
        src/libs/mosquitto-2.0.15/include
        ${OPENSSL_INCLUDE_DIRS}
)

add_executable(Domotica src/target/main.cpp src/target/include/main.h)

add_subdirectory(src/libs/mosquitto-2.0.15)
add_subdirectory(src/libs/easyloggingpp)

target_include_directories(${PROJECT_NAME} PRIVATE src/libs/mosquitto-2.0.15/lib/cpp)
target_include_directories(${PROJECT_NAME} PRIVATE src/libs/easyloggingpp)

target_link_directories(${PROJECT_NAME} PRIVATE src/libs/mosquitto-2.0.15)
target_link_directories(${PROJECT_NAME} PRIVATE src/libs/easyloggingpp)

target_link_libraries(${PROJECT_NAME} mosquittopp)
target_link_libraries(${PROJECT_NAME} easyloggingpp)
