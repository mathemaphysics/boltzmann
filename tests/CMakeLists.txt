include(CTest)
enable_testing()

find_package(Boost REQUIRED)

add_executable(test_create_node test_create_node.cpp)
target_include_directories(test_create_node PUBLIC ${PROJECT_SOURCE_DIR}/include ${Boost_INCLUDE_DIRS})
target_link_libraries(test_create_node boltzmann ${Boost_LIBRARIES})

add_test(NAME CreateNodeTest COMMAND test_create_node)
set_property(TEST CreateNodeTest APPEND PROPERTY DEPENDS test_create_node)