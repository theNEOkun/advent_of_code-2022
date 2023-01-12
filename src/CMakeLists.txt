cmake_minimum_required(VERSION 3.25.1)

set(SOURCES main.cpp
  day1/day1.cpp
  day2/day2.cpp
  day3/day3.cpp
  day4/day4.cpp
  day5/day5.cpp
  day6/day6.cpp
  day7/day7.cpp
  day7/info.cpp
  day8/day8.cpp
  day9/day9.cpp
  day10/day10.cpp
  day11/day11.cpp
  day12/day12.cpp
  day13/day13.cpp)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O -Wall -ggdb -lstdc++")
project(cmake-project)

add_library(utils STATIC ${PROJECT_SOURCE_DIR}/utils/utils.cpp)

# Add executable

add_executable(cmake-project ${PROJECT_SOURCE_DIR}/${SOURCES})
target_link_libraries(cmake-project utils)
