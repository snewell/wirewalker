add_subdirectory(core)
add_subdirectory(oap)

find_library(FOUND_CPPUNIT NAMES cppunit)

if   (FOUND_CPPUNIT)
    message(STATUS "cppunit available, building unit tests")
else ()
    message(WARNING "Missing cppunit -- can't build unit tests")
endif()
