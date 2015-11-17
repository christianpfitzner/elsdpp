find_package(Boost REQUIRED COMPONENTS unit_test_framework)

add_definitions (-DBOOST_TEST_DYN_LINK)

configure_file(stars.pgm stars.pgm COPYONLY)

set(TEST_LIBS
    elsd
    ${Boost_LIBRARIES}
    ${ELSD_LIBS}
    )

set(TEST_SOURCES
    elsdetector_test.cpp
    )

foreach(testfilename ${TEST_SOURCES})
    string(REPLACE ".cpp" "" testname ${testfilename})
    add_executable(${testname} ${testfilename})
    target_link_libraries(${testname} ${TEST_LIBS})
endforeach(testfilename ${TEST_SOURCES})
