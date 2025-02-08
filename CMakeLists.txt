cmake_minimum_required(VERSION 3.10)
project(Socket)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add subdirectories
add_subdirectory(server)
add_subdirectory(client)