find_package(Boost REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)
add_library(boltzmann SHARED neuron.cpp layer.cpp)
