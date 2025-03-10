cmake_minimum_required(VERSION 3.17)
project(lexer)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

add_library(lexer_internals 
    src/tokenizer.cpp  
    include/tokenizer.hpp 
)
target_include_directories(lexer_internals PUBLIC include)

add_executable(lexer main.cpp)
target_link_libraries(lexer lexer_internals)