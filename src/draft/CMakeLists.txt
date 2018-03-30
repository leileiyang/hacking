cmake_minimum_required(VERSION 3.5)
project(testArm)

set(CMAKE_SYSTEM_NAME linux)
set(CMAKE_CXX_COMPILER /usr/local/bin/gcc-linaro-arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER /usr/local/bin/gcc-linaro-arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++)

add_executable(testArm test.cpp)


