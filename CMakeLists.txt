cmake_minimum_required(VERSION 3.27)

# set the project name
project(AlphaZeroPlusPlus)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the game library
add_library(game_lib game_library/game.cpp)

# add the executable
add_executable(game_main game_library/main.cpp)

target_link_libraries(game_main PUBLIC game_lib)

# python bindings using pybind
set(SYSTEM ON)
add_subdirectory(pybind11)
pybind11_add_module(pygamebindings game_library/game_bindings.cpp)
target_link_libraries(pygamebindings PUBLIC game_lib)