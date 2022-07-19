cmake_minimum_required(VERSION 3.1)
project(DancingLinks)
enable_language(C)
enable_language(CXX)

include(FetchContent)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native")

#range_v3
FetchContent_Declare(
    range_v3
    GIT_REPOSITORY https://github.com/ericniebler/range-v3/
    GIT_TAG        0.12.0
)
FetchContent_GetProperties(range_v3)
if(NOT range_v3_POPULATED)
    FetchContent_Populate(range_v3)
    add_subdirectory(${range_v3_SOURCE_DIR} ${range_v3_BINARY_DIR})
    include_directories(${range_v3_SOURCE_DIR}/include)
endif()

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
#pybind
FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11
    GIT_TAG        v2.9.2
)
FetchContent_GetProperties(pybind11)
if(NOT pybind11_POPULATED)
    FetchContent_Populate(pybind11)
    add_subdirectory(${pybind11_SOURCE_DIR} ${pybind11_BINARY_DIR})
    include_directories(${pybind11_SOURCE_DIR})
endif()

#cppcoro
FetchContent_Declare(
    cppcoro
    GIT_REPOSITORY https://github.com/andreasbuhr/cppcoro
    GIT_TAG        main
)
FetchContent_GetProperties(boost)
if(NOT cppcoro_POPULATED)
    FetchContent_Populate(cppcoro)
    add_subdirectory(${cppcoro_SOURCE_DIR} ${cppcoro_BINARY_DIR})
    include_directories(${cppcoro_SOURCE_DIR}/include)
endif()

add_subdirectory(src)
include_directories(src)


set(SOURCE_FILES src/DancingLinks.cpp)

pybind11_add_module(DancingLinks ${SOURCE_FILES})
