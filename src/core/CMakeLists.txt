set(wwcore_dir "${CMAKE_CURRENT_SOURCE_DIR}" PARENT_SCOPE)

add_subdirectory(common_types)
add_subdirectory(interface)
add_subdirectory(object)
add_subdirectory(packet)

include_directories(include)

add_library(wwcore SHARED ${common_srcs} ${interface_srcs} ${object_srcs}
                          ${packet_srcs})
set_target_properties(wwcore PROPERTIES
                      VERSION ${PROJECT_VERSION}
                      SOVERSION ${PROJECT_VERSION_MAJOR})

if    (FOUND_CPPUNIT)
    add_executable(wwcore_units test_runner.cpp ${common_units} ${interface_units}
                                                ${object_units} ${packet_units})
    target_link_libraries(wwcore_units cppunit wwcore)
    add_test(wwcore_units wwcore_units)
endif()
