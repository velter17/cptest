add_executable(cptest_start
    cptest.cpp
    private/CommandFactory.cpp)

target_link_libraries(cptest_start
    ${CPTEST_LIBS}
    ${CPTEST_COMMANDS}
    )

install(TARGETS
    cptest_start
    RUNTIME DESTINATION ${BIN_DIR}/bin
    )
