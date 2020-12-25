cmake_minimum_required(VERSION 3.0.0)
project(Boltzmann VERSION 0.1.0)

include(CTest)
enable_testing()

option(USE_DOUBLE "Use double precision weights and biases" OFF)
option(USE_BOOST_GRAPH "Use boost graph library for structure" OFF)
option(USE_BOOST_UBLAS "Use boost numeric's uBLAS library for structure" ON)
option(USE_BOOST_MULTIARRAY "Build network weights to use Boost's multi_array" OFF)
option(WITH_OPENCV "Build project using OpenCV libraries for display" OFF)
option(WITH_OPENACC "Build project using OpenACC directives" OFF)
option(WITH_OPENMP "Build project using OpenMP directives" OFF)
option(WITH_CUDA "Build project using CUDA libraries" OFF)

configure_file(include/boltzmann/boltzmann_config.hpp.in include/boltzmann/boltzmann_config.hpp)

add_subdirectory(src)
add_subdirectory(tests)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
