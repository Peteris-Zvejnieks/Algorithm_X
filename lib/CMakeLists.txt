add_library(range-v3 INTERFACE)
target_include_directories(range-v3 INTERFACE range-v3/include)

add_library(pybind11 INTERFACE)
target_include_directories(pybind11 INTERFACE pybind11/include)

add_library(cppcoro INTERFACE)
target_include_directories(cppcoro INTERFACE cppcoro/include)