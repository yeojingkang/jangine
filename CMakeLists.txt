cmake_minimum_required(VERSION 3.10)

# Set the project name
project(jangine)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add Jangine library
add_subdirectory(src/engine)

find_package(GTest)

if(NOT(GTest_FOUND))
    configure_file(GTest_CMakeLists.txt.in googletest-download/CMakeLists.txt)
    execute_process(
        COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE  result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download
    )
    if(result)
        message(FATAL_ERROR "CMake step for googletest failed: ${result}")
    endif()

    execute_process(
        COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE  result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download
    )
    if(result)
        message(FATAL_ERROR "Build step for googletest failed: ${result}")
    endif()

    # Prevent overriding the parent project's compiler/linker settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    # Add googletest directly to the build. This defines the gtest and gtest_main targets
    add_subdirectory(
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL
    )
endif()

# Add unit tests
enable_testing()
add_executable(UnitTest
    src/test/vector_test.cpp 
    src/test/matrix_test.cpp 
)
target_link_libraries(UnitTest PUBLIC gtest_main jangine)
add_test(NAME Unit_Test COMMAND UnitTest)
