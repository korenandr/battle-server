cmake_minimum_required(VERSION 3.27)
project(battle_server VERSION 1.0)
include(cmake/PreventInSourceBuilds.cmake)

option(ENABLE_TESTING "Enable Test Builds" ON)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.hpp)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC src/)

if(ENABLE_TESTING)
    include(cmake/GoogleTests.cmake)
    add_subdirectory(tests)
endif()
