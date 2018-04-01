file(GLOB_RECURSE CPTEST_OUTPUT_SRC *.cpp)

add_library(${CPTEST_OUTPUT} STATIC
    ${CPTEST_OUTPUT_SRC}
    )

target_link_libraries(${CPTEST_OUTPUT}
    PUBLIC ${CPTEST_LIBS}
    )
