#include <cstdint>
#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pat/pat.hpp>
#include <cppcoro/generator.hpp>

using namespace pat;
using namespace std;
namespace py = pybind11;


PYBIND11_MODULE(DancingLinks, m) {
    m.doc()  = "I'm a docstring hehe";
    py::class_<default_solver>(m, "DLX")
            .def(py::init<uint32_t, uint32_t>(), py::arg("primary_items"), py::arg("secondary_items") = 0u)
            .def("add_subset", &default_solver::add_option<std::vector<uint32_t>>, py::arg("subset"))
            .def("solve", [&default_solver](){std::vector<uint32_t> solution = ++default_solver::solve(); return solution;});
            };

