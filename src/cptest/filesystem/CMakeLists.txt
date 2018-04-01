file(GLOB_RECURSE CPTEST_FILESYSTEM_SRC *.cpp)

find_package(Boost 1.62 COMPONENTS filesystem REQUIRED)

add_library(${CPTEST_FILESYSTEM} STATIC
    ${CPTEST_FILESYSTEM_SRC}
    )

target_link_libraries(${CPTEST_FILESYSTEM}
    PUBLIC  ${CPTEST_LIBS}
    Boost::filesystem
    )
