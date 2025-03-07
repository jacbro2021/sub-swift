cmake_minimum_required(VERSION 3.17)
project(lexer)
set(CMAKE_CXX_STANDARD 20)

# For later use...
# add_library(lexer_internals 
# )
# target_include_directories(lexer_internals PUBLIC include)

add_executable(lexer main.cpp)
# target_link_libraries(lexer lexer_internals)