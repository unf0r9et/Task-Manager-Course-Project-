cmake_minimum_required(VERSION 3.16)
project(TaskManager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(
        ${CMAKE_SOURCE_DIR}/include
)

set(RESOURCES
        resources/resources.qrc
)

add_executable(TaskManager
        src/main.cpp
        src/gui/authorization/Authorization.h
        src/gui/authorization/Authorization.cpp
        ${RESOURCES}
)

target_link_libraries(TaskManager Qt5::Widgets)