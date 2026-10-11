cmake_minimum_required(VERSION 3.10)

project(ice-sliding-puzzle)

# Build both parts of the project from a single top-level configure:
#   player/  - the interactive game (assignment 13)
#   solver/  - the BFS/DFS solver   (assignment 14)
# Each subdirectory has its own CMakeLists.txt and its own test suite.
add_subdirectory(player)
add_subdirectory(solver)
