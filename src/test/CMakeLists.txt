cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Test)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(Test test.cpp)

target_include_directories(Test PUBLIC ../engine/)
