cmake_minimum_required(VERSION 2.8.4)
project(poyline-cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/Polyline.cpp
        src/Polyline.h)

set(TEST_FILES
        tests/PolylineTest.cpp
        tests/PolylineTest.h)

set(TEST_FILES ${TEST_FILES} ${SOURCE_FILES})

add_executable(polyline_test ${TEST_FILES})

##################
# TEST FRAMEWORK #
##################

# Add google test framework
add_subdirectory(dependencies/googletest gtest)
include_directories(gtest STATIC devtools/googletest/include )

set(TEST_FRAMEWORK_LIBS gtest)

target_link_libraries(polyline_test ${TEST_FRAMEWORK_LIBS})

