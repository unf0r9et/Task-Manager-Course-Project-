cmake_minimum_required(VERSION 3.16)
project(TaskManager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CURL REQUIRED)

find_package(nlohmann_json QUIET)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/src/utils/styleloader
)

set(RESOURCES
        resources/resources.qrc
)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
)


add_executable(TaskManager
        ${PROJECT_SOURCES}
        ${RESOURCES}
)

target_link_libraries(TaskManager
        Qt5::Widgets
        CURL::libcurl
)

target_link_libraries(TaskManager Qt5::Widgets)