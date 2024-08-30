file(GLOB SOURCE_FILES *.cpp)

set(BINARY_NAME "core")

add_library(${BINARY_NAME} STATIC ${SOURCE_FILES})

target_include_directories(${BINARY_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/${SOURCE_DIR}/core)
target_link_libraries(${BINARY_NAME} PUBLIC netcpp::netcpp fmt::fmt)
