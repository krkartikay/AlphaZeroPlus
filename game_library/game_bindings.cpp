#include <pybind11/pybind11.h>
#include "game.h"

namespace py = pybind11;

PYBIND11_MODULE(pygamebindings, m) {
    py::class_<GameState>(m, "GameState")
        .def(py::init<>())
        .def("get_state", &GameState::get_state);
}