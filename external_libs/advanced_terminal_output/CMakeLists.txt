cmake_minimum_required(VERSION 3.7)

project(advanced_terminal_output)
find_package(Boost 1.63 REQUIRED)

add_library(${PROJECT_NAME} INTERFACE)

target_link_libraries(${PROJECT_NAME}
    INTERFACE Boost::boost
    )

target_include_directories(
    ${PROJECT_NAME}
    INTERFACE ${PROJECT_SOURCE_DIR}/include
    )
