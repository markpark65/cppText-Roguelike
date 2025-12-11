cmake_minimum_required(VERSION 3.10)
project(Roguelike)

set(CMAKE_CXX_STANDARD 14)

if(MSVC)
    add_compile_options(/utf-8)
endif()

# Set output directory to project root or build/Release depending on preference
# For simplicity, we just look in build dir
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include directory
include_directories(include)

# Source files
# Explicitly listing files is better practice than GLOB for CMake, but GLOB is easier for now.
# However, I know the files: main.cpp, Entity.cpp, GameManager.cpp.
# Let's see if main.cpp is in src. Assuming yes based on "move *.cpp src/".
set(SOURCES
    src/main.cpp
    src/Entity.cpp
    src/GameManager.cpp
)

add_executable(roguelike ${SOURCES})
