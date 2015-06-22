include(CMakeForceCompiler)

cmake_minimum_required(VERSION 2.8)

SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_PROCESSOR arm)
SET(CMAKE_CROSSCOMPILING 1)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)

CMAKE_FORCE_C_COMPILER("arm-none-eabi-gcc" GNU)

project("lcdDriver" C)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(/home/jacob/git/stm32/src)

add_subdirectory(src)
add_subdirectory(test/endtoend)
add_subdirectory(/home/jacob/git/stm32 stm32)
