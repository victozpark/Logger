cmake_minimum_required(VERSION 3.9)

project(Itc_TEST VERSION 0.0.0 DESCRIPTION "Test program")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmacro-prefix-map=${CMAKE_CURRENT_SOURCE_DIR}/=") # Remove the absolute path from the preprocessor output (for __FILE__ macro)

include_directories(${CMAKE_SOURCE_DIR}/../release/include)
link_directories(${CMAKE_SOURCE_DIR}/../release/lib)
link_libraries (-lpthread -lLogger)

add_executable(main Main.cpp)
