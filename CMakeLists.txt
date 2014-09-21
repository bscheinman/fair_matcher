cmake_minimum_required(VERSION 2.8.12)
project(fair_matcher)

find_package(
    Boost
    1.54
    COMPONENTS system REQUIRED
)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

set(CMAKE_CXX_FLAGS "-std=c++11 -g")
set(CMAKE_EXE_LINKER_FLAGS "-lboost_system -lpthread -lprotobuf")

add_subdirectory(shared)
add_subdirectory(matcher)
add_subdirectory(client)
