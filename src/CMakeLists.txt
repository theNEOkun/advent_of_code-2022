cmake_minimum_required(VERSION 3.25.1)

set(SOURCES main.cpp day1/day1.cpp day2/day2.cpp day3/day3.cpp)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O -Wall")
project(cmake-project)

add_library(utils STATIC ${PROJECT_SOURCE_DIR}/utils/utils.cpp)

# Add executable

add_executable(cmake-project ${PROJECT_SOURCE_DIR}/${SOURCES})
target_link_libraries(cmake-project utils)
