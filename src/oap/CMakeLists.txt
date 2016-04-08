add_subdirectory(common)
add_subdirectory(request)
add_subdirectory(wire)

include_directories("${wwcore_dir}/include")
include_directories(include)
include_directories(internal_include)

add_library(wwoap SHARED ${common_srcs} ${request_srcs} ${wire_srcs})
set_target_properties(wwoap PROPERTIES
                      VERSION ${PROJECT_VERSION}
                      SOVERSION ${PROJECT_VERSION_MAJOR})
target_link_libraries(wwoap wwcore)

if   (FOUND_CPPUNIT)
    add_executable(wwoap_units test_runner.cpp ${common_units} ${request_units} ${wire_units})
    target_link_libraries(wwoap_units cppunit wwoap)
    add_test(wwoap_units wwoap_units)
endif()
