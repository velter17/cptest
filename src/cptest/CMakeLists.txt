#add_subdirectory (include)

add_library(${CPTEST_LIBS} INTERFACE)

target_include_directories(
    ${CPTEST_LIBS}
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${CPTEST_LIBS}
    INTERFACE advanced_terminal_output
    )

add_subdirectory(compiler)
add_subdirectory(contest)
add_subdirectory(executor)
add_subdirectory(status)
add_subdirectory(test_archive)
add_subdirectory(tester)
add_subdirectory(filesystem)
add_subdirectory(output)
