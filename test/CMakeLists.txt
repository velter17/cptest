include_directories ( ../src/cptest/include/ )

set (TEST_TEST_ARCHIVE_SRC
    test_archive.cpp
    )

add_executable (test_test_archive ${TEST_TEST_ARCHIVE_SRC} )

target_link_libraries ( test_test_archive
    ${CPTEST_TEST_ARCHIVE}
    aixlog
    )
