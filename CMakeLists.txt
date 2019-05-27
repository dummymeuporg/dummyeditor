cmake_minimum_required(VERSION 3.10.0)
project(dummyeditor)
include_directories(
    dummy
    graphicmap
    misc
    vendor/libdummy/include
)

set (CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall")

add_subdirectory("vendor/libdummy")

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(Qt5Widgets REQUIRED)

file(GLOB_RECURSE SOURCES "dummy/*.cpp")
file(GLOB_RECURSE HEADERS "graphicmap/*.cpp")
file(GLOB_RECURSE HEADERS "misc/*.cpp")

add_executable(dummyeditor ${SOURCES} ${HEADERS})

target_link_libraries(dummyeditor
    Qt5::Core
    Qt5::Gui
    Qt5::Xml
    Qt5::Widgets
    dummy
)