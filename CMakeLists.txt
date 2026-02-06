cmake_minimum_required(VERSION 3.15)
project(UnitConverter)
set(CMAKE_CXX_STANDARD 17)
add_executable(converter
src/main.cpp
src/CsvHandler.cpp
src/TOMLHandler.cpp
src/Length.cpp
src/Time.cpp
src/Temperature.cpp
)
target_include_directories(converter PRIVATE include)