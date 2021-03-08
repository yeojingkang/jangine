cmake_minimum_required(VERSION 3.7)

# Set the project name
project(Test)

# Add the executable
add_executable(Test test.cpp)

target_include_directories(Test PUBLIC ../engine/)
