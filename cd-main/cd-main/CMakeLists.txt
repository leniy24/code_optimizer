cmake_minimum_required(VERSION 3.10)
project(CodeOptimizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
add_executable(code_optimizer
    src/main.cpp
    src/optimizer.cpp
    src/parser.cpp
)

# Include directories
target_include_directories(code_optimizer PRIVATE include)

# Add compiler flags for optimization
target_compile_options(code_optimizer PRIVATE -O2 -Wall -Wextra) 