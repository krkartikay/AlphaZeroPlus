#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "game.h"

namespace py = pybind11;

PYBIND11_MODULE(game, m) {
  py::enum_<Player>(m, "Player")
      .value("NONE", Player::NONE)
      .value("WHITE", Player::WHITE)
      .value("BLACK", Player::BLACK)
      .export_values();

  py::class_<GameState>(m, "GameState")
      .def(py::init<>())
      .def("player", &GameState::player)
      .def("winner", &GameState::winner)
      .def("terminated", &GameState::terminated)
      .def("legalActions", &GameState::legalActions)
      .def("makeMove", &GameState::makeMove)
      .def("printBoard", &GameState::printBoard);
}