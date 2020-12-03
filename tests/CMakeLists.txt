include(CTest)
enable_testing()

find_package(Boost REQUIRED)

add_executable(test_create_node test_create_node.cpp)
target_include_directories(test_create_node PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_BINARY_DIR}/include ${Boost_INCLUDE_DIRS})
target_link_libraries(test_create_node boltzmann ${Boost_LIBRARIES})

add_executable(test_activate_node test_activate_node.cpp)
target_include_directories(test_activate_node PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_BINARY_DIR}/include ${Boost_INCLUDE_DIRS})
target_link_libraries(test_activate_node boltzmann ${Boost_LIBRARIES})

add_executable(test_create_network test_create_network.cpp)
target_include_directories(test_create_network PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_BINARY_DIR}/include ${Boost_INCLUDE_DIRS})
target_link_libraries(test_create_network boltzmann ${Boost_LIBRARIES})

add_executable(test_boost_graph test_boost_graph.cpp)
target_include_directories(test_boost_graph PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_BINARY_DIR}/include ${Boost_INCLUDE_DIRS})
target_link_libraries(test_boost_graph ${Boost_LIBRARIES})

add_test(NAME CreateNodeTest COMMAND test_create_node)
add_test(NAME ActivateNodeTest COMMAND test_activate_node)
add_test(NAME CreateNetworkTest COMMAND test_create_network)
add_test(NAME BoostGraphSample COMMAND test_boost_graph)
