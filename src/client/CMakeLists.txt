file(GLOB SOURCE_FILES *.cpp)

set(BINARY_NAME "client")

add_executable(${BINARY_NAME} ${SOURCE_FILES})

target_link_libraries(${BINARY_NAME} PRIVATE core)
