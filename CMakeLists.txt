cmake_minimum_required(VERSION 3.9)

project(BigNumber VERSION 0.9.0 DESCRIPTION "Logger library")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmacro-prefix-map=${CMAKE_CURRENT_SOURCE_DIR}/=") # Remove the absolute path from the preprocessor output (for __FILE__ macro)

add_library(Logger 
SHARED ALogger.cpp
       DefaultLogFormatter.cpp
       SimpleLogger.cpp
       ThreadedLogger.cpp
)

set_target_properties(Logger PROPERTIES VERSION ${PROJECT_VERSION})

target_include_directories(Logger PUBLIC ${CMAKE_SOURCE_DIR})

target_compile_options(Logger PRIVATE -Wall -Werror)

install(TARGETS Logger DESTINATION ${CMAKE_SOURCE_DIR}/release/lib)
install(
FILES ALogger.hpp
      DefaultLogFormatter.hpp
      ILogFormatter.hpp
      Logger.h
      SimpleLogger.hpp
      ThreadedLogger.hpp
DESTINATION ${CMAKE_SOURCE_DIR}/release/include
)
