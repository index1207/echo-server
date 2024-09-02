cmake_minimum_required(VERSION 3.11)
project(echo)

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_DIR "src")

option(ENABLE_TEST "Enable dummy client stress test" ON)

find_package(fmt CONFIG REQUIRED)
find_package(netcpp CONFIG REQUIRED)

add_subdirectory(${SOURCE_DIR}/client)
add_subdirectory(${SOURCE_DIR}/core)
add_subdirectory(${SOURCE_DIR}/server)
if (${ENABLE_TEST})
    add_subdirectory(${SOURCE_DIR}/dummy)
endif ()