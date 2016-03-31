add_subdirectory(common_types)
add_subdirectory(object)
add_subdirectory(packet)

include_directories(include)

add_library(wwcore SHARED ${common_srcs} ${object_srcs} ${packet_srcs})
set_target_properties(wwcore PROPERTIES
                      VERSION ${CMAKE_PROJECT_VERSION}
                      SOVERSION ${CMAKE_PROJECT_MAJOR_VERSION})

add_executable(wwcore_units test_runner.cpp ${common_units} ${object_units}
                                            ${packet_units})
target_link_libraries(wwcore_units cppunit wwcore)
add_test(wwcore_units wwcore_units)
