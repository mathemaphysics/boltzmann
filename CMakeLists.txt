cmake_minimum_required(VERSION 3.0.0)
project(Boltzmann VERSION 0.1.0)

include(CTest)
enable_testing()

option(USE_BOOST_GRAPH "Use boost graph library for structure" OFF)

configure_file(include/boltzmann/boltzmann_config.hpp.in include/boltzmann/boltzmann_config.hpp)

add_subdirectory(src)
add_subdirectory(tests)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
