cmake_minimum_required(VERSION 3.26)

# set the project name
project(AlphaZeroPlusPlus)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the -fPIC flag
add_compile_options(-fPIC)

# python bindings using pybind
add_subdirectory(pybind11)
add_subdirectory(game_library)

# Set the install prefix to the site-packages directory of the virtual environment
# Calculate the absolute path to the virtual environment

# Find the Python interpreter and libraries
find_package(Python COMPONENTS Interpreter Development)

# Set the install prefix to the site-packages directory of the Python interpreter
# This assumes that the desired Python is in the system's PATH or specified as a CMake variable.
if(Python_FOUND)
    set(CMAKE_INSTALL_PREFIX ${Python_SITELIB})
else()
    message(FATAL_ERROR "Python not found!")
endif()

install(TARGETS game LIBRARY DESTINATION .)
