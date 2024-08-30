file(GLOB SOURCE_FILES *.cpp)

set(BINARY_NAME "server")

add_executable(${BINARY_NAME} ${SOURCE_FILES})

target_link_libraries(${BINARY_NAME} PRIVATE core)
