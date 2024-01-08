cmake_minimum_required(VERSION 3.0)
project(main)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-std=c++11)

find_package(Eigen3 REQUIRED)
# include_directories("/usr/local/include/eigen3")
include_directories(${EIGEN3_INCLUDE_DIRS} ${osqp_INCLUDE_DIRS})

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -W -Wall -Wextra -Wfatal-errors -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_BUILD_TYPE "Debug")
# set(CMAKE_BUILD_TYPE "Release")
add_executable(main main.cpp)
#target_link_libraries (${PROJECT_NAME} ${Boost_SYSTEM_LIBRARY} pthread) 
target_link_libraries (${PROJECT_NAME} ${Boost_SYSTEM_LIBRARY} boost_system pthread armadillo OsqpEigen osqp) 
#target_link_libraries (main ${CMAKE_THREAD_LIBS_INIT})

