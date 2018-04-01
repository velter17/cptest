find_package(Boost 1.62 COMPONENTS program_options regex REQUIRED)

add_library ( ${BOOST_PO_EXTENDED} STATIC
    "CustomOptionDescription.cpp"
    "OptionPrinter.cpp"
    )

target_include_directories(${BOOST_PO_EXTENDED}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

target_link_libraries( ${BOOST_PO_EXTENDED}
    Boost::program_options
    Boost::regex
    )
