cmake_minimum_required(VERSION 3.10)
project(CodeOptimizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(code_optimizer
    src/backend/src/main.cpp
    src/backend/src/optimizer.cpp
    src/backend/src/parser.cpp
)

target_include_directories(code_optimizer PRIVATE src/backend/include)
target_compile_options(code_optimizer PRIVATE -O2 -Wall -Wextra)