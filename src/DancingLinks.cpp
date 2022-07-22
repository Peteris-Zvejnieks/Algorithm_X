#include <cstdint>
#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pat/pat.hpp>

using namespace pat;
using namespace std;
namespace py = pybind11;


PYBIND11_MODULE(DancingLinks_cpp, m) {
    m.doc()  = "Python module of C++20 based implementations of dancing link algorithms (as described by Donald E. Knuth in *The Art of Computer Programming*) for various kinds of cover problem";
    py::class_<default_solver>(m, "DLX")
            .def(py::init<uint32_t, uint32_t>(),
                    py::arg("primary_items"),
                    py::arg("secondary_items") = 0u)
            .def("add_subset",
                 &default_solver::add_option, py::arg("subset"))
            .def("make_generator",
                 &default_solver::make_generator)
            .def("__next__",
                 &default_solver::get_next)
            .def("_next_batch",
                 &default_solver::get_next_batch,
                 py::arg("batch_size") = 8u)
            .def("__len__",  &default_solver::get_number_of_solutions);

    #ifdef VERSION_INFO
        m.attr("__version__") = VERSION_INFO;
    #else
        m.attr("__version__") = "dev";
    #endif
};

