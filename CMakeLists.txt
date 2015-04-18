#Set minimum CMake version required to run this file
cmake_minimum_required(VERSION 2.8)
   
#Set name of project 
project("lcdDriver")
   
#Set compiler flags:
#  g3 <-- Include debugging information in build
#  Wall <-- Enable all compiler warnings messages
add_definitions(-Wall -g3)
   
#Add the given directories to those the compiler uses to search for include files
#  CMAKE_CURRENT_SOURCE_DIR <-- This is the directory where the currently processed CMakeLists.txt is located in 
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
   
#Add a subdirectory to the build. The directory specified must contain a CMakeLists.txt file.
add_subdirectory(test)
