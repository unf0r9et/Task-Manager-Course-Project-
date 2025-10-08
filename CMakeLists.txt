cmake_minimum_required(VERSION 3.31)
project(TaskManager)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(TaskManager main.cpp)

target_link_libraries(TaskManager Qt5::Widgets)
