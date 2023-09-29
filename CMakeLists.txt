cmake_minimum_required(VERSION 3.27)

# set the project name
project(AlphaZeroPlusPlus)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# python bindings using pybind
add_subdirectory(pybind11)
add_subdirectory(game_library)

# Set the install prefix to the site-packages directory of the virtual environment
# Calculate the absolute path to the virtual environment
get_filename_component(VENV_PATH "${CMAKE_SOURCE_DIR}/venv" ABSOLUTE)
set(CMAKE_INSTALL_PREFIX "${VENV_PATH}/lib/python3.11/site-packages")

install(TARGETS game LIBRARY DESTINATION .)
