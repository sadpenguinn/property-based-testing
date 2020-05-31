cmake_minimum_required(VERSION 3.16)
project(property_based_testing)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory("external/rapidcheck")

add_executable(property_based_testing Main.cpp Types.hpp name_traits.hpp Realization.cpp Realization.hpp)
target_link_libraries(property_based_testing rapidcheck)