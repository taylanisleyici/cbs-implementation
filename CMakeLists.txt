cmake_minimum_required(VERSION 3.10)

# Set the project name
project(cbs-implementation)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directories
include_directories(include)

# Add the executable
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(cbs-implementation main.cpp ${SOURCES})

# Link libraries if any (example)
# target_link_libraries(cbs-implementation some_library)