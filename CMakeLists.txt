cmake_minimum_required(VERSION 3.10.0)
project(dummyeditor)
include_directories(
    include
    vendor/libdummy/include
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory("vendor/libdummy")

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(Qt5Widgets REQUIRED)

macro(GroupSources curdir)
    file(
        GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir}
        ${PROJECT_SOURCE_DIR}/${curdir}/*
    )
    foreach(child ${children})
        if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})
            GroupSources(${curdir}/${child})
        else()
            string(REPLACE "/" "\\" groupname ${curdir})
            source_group(
                ${groupname}
                FILES
                ${PROJECT_SOURCE_DIR}/${curdir}/${child}
            )
        endif()
    endforeach()
endmacro()

file(GLOB_RECURSE SOURCES "src/*.cpp" "ui/*.ui")
file(GLOB_RECURSE HEADERS "include/*.cpp")

GroupSources(include)
GroupSources(src)
GroupSources(ui)

add_executable(dummyeditor ${SOURCES} ${HEADERS})

target_link_libraries(dummyeditor
    Qt5::Core
    Qt5::Gui
    Qt5::Xml
    Qt5::Widgets
    dummy
)