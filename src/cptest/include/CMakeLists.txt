add_library(${CPTEST_LIBS} INTERFACE)

target_include_directories(
    ${CPTEST_LIBS}
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
