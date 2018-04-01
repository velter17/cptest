file(GLOB_RECURSE CPTEST_COMMANDS_SRC *.cpp)

find_package(Boost 1.62 COMPONENTS filesystem program_options REQUIRED)

add_library(${CPTEST_COMMANDS} STATIC
    ${CPTEST_COMMANDS_SRC}
    )

target_include_directories(
    ${CPTEST_COMMANDS}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

target_link_libraries(${CPTEST_COMMANDS}
    PRIVATE Boost::filesystem
    PRIVATE Boost::program_options
    PRIVATE ${CPTEST_LIBS}
    PRIVATE ${CPTEST_STATUS}
    PRIVATE ${CPTEST_OUTPUT}
    PRIVATE ${CPTEST_TEST_ARCHIVE}
    PUBLIC ${BOOST_PO_EXTENDED}
    )

install ( FILES
    test/cptest_test_create.sh
    DESTINATION ${BIN_DIR}/bin
    PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
    GROUP_EXECUTE GROUP_READ WORLD_READ WORLD_EXECUTE)
