# add the game library
add_library(game_lib game.cpp)

# add the executable
add_executable(game_main main.cpp)

pybind11_add_module(game game_bindings.cpp)

target_link_libraries(game_main PUBLIC game_lib)
target_link_libraries(game PUBLIC game_lib)
