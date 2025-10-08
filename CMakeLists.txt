cmake_minimum_required(VERSION 3.31)
project(TaskManager)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(TaskManager
        main.cpp
        src/ProgramInterface/AuthorizationМenu/AuthorizationМenu.cpp
)

target_link_libraries(TaskManager Qt5::Widgets)
