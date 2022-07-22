cmake_minimum_required(VERSION 3.12)
project(DancingLinks VERSION 0.1.0)
enable_language(CXX)

include(FetchContent)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native")

add_subdirectory(lib/pybind11)
add_subdirectory(lib/cppcoro)
add_subdirectory(lib/range-v3)

include_directories(SYSTEM lib/pybind11/include)
include_directories(SYSTEM lib/cppcoro/include)
include_directories(SYSTEM lib/range-v3/include)

add_subdirectory(src)
include_directories(SYSTEM src)

pybind11_add_module(DancingLinks_cpp src/DancingLinks.cpp)

#target_compile_definitions(cmake_example PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})