include(CTest)
enable_testing()

find_package(Boost REQUIRED COMPONENTS filesystem)

if (WITH_OPENCV)
find_package(OpenCV REQUIRED)
endif (WITH_OPENCV)

add_executable(test_create_node test_create_node.cpp)
target_include_directories(test_create_node PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_BINARY_DIR}/include ${Boost_INCLUDE_DIRS})
target_link_libraries(test_create_node boltzmann ${Boost_LIBRARIES})

add_executable(test_create_network test_create_network.cpp)
target_include_directories(test_create_network PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_BINARY_DIR}/include ${Boost_INCLUDE_DIRS})
target_link_libraries(test_create_network boltzmann ${Boost_LIBRARIES})

add_executable(test_activate_node test_activate_node.cpp)
target_include_directories(test_activate_node PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_BINARY_DIR}/include ${Boost_INCLUDE_DIRS})
target_link_libraries(test_activate_node boltzmann ${Boost_LIBRARIES})

add_executable(test_activate_layer test_activate_layer.cpp)
target_include_directories(test_activate_layer PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_BINARY_DIR}/include ${Boost_INCLUDE_DIRS})
target_link_libraries(test_activate_layer boltzmann ${Boost_LIBRARIES})

add_executable(test_activate_layer_back test_activate_layer_back.cpp)
target_include_directories(test_activate_layer_back PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_BINARY_DIR}/include ${Boost_INCLUDE_DIRS})
target_link_libraries(test_activate_layer_back boltzmann ${Boost_LIBRARIES})

add_executable(test_boost_graph test_boost_graph.cpp)
target_include_directories(test_boost_graph PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_BINARY_DIR}/include ${Boost_INCLUDE_DIRS})
target_link_libraries(test_boost_graph ${Boost_LIBRARIES})

if (WITH_OPENCV)
add_executable(test_opencv_display_state test_opencv_display_state.cpp)
target_include_directories(test_opencv_display_state PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_BINARY_DIR}/include ${Boost_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})
target_link_libraries(test_opencv_display_state ${Boost_LIBRARIES} ${OpenCV_LIBRARIES})
endif (WITH_OPENCV)

if (WITH_OPENCV)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/output)
add_test(NAME OpenCVDisplayState COMMAND test_opencv_display_state WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/output)
endif (WITH_OPENCV)

add_test(NAME CreateNodeTest COMMAND test_create_node)
add_test(NAME CreateNetworkTest COMMAND test_create_network)
add_test(NAME ActivateNodeTest COMMAND test_activate_node)
add_test(NAME ActivateLayerTest COMMAND test_activate_layer)
add_test(NAME ActivateLayerBackTest COMMAND test_activate_layer_back)
add_test(NAME BoostGraphSample COMMAND test_boost_graph)
