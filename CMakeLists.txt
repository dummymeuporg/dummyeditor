cmake_minimum_required(VERSION 3.13.0)

project(dummyeditor)

# where to find #include files
include_directories(
    include
    vendor/libdummy/include
)

# Specify C++ version
set(CMAKE_CXX_STANDARD 17)

# enable a sub-cmake
add_subdirectory("vendor/libdummy")

#set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Qt pre-compilation activation
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# depedencies Qt, Boost and Lua
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Boost 1.69.0 REQUIRED)
find_package(Lua 5.3 REQUIRED)

# Silence an annoying Boost/C++17 warning
add_definitions(-D_SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.ui")
file(GLOB_RECURSE HEADERS "include/*.hpp")

macro(GroupSources curdir)
    file(
        GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir}
        ${PROJECT_SOURCE_DIR}/${curdir}/*
    )
    foreach(child ${children})
        if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})
            GroupSources(${curdir}/${child})
        else()
            string(REGEX REPLACE "^(src|include)/?" "" curdirsimple ${curdir})
            string(REPLACE "/" "\\" groupname "${curdirsimple}")
            #string(REPLACE "/" "\\" groupname "${curdir}")
            source_group(
                "${groupname}"
                FILES
                ${PROJECT_SOURCE_DIR}/${curdir}/${child}
            )
        endif()
    endforeach()
endmacro()

link_directories(${Boost_LIBRARY_DIRS} ${LUA_LIBRARIES})

GroupSources(include)
GroupSources(src)
GroupSources(ui)

set(DUMMYEDITOR_LINK_LIBRARIES
    Qt5::Core
    Qt5::Gui
    Qt5::Xml
    Qt5::Widgets
    dummy
    ${Boost_LIBRARIES}
    ${LUA_LIBRARY})

if (UNIX)
    set(DUMMYEDITOR_LINK_LIBRARIES
        ${DUMMYEDITOR_LINK_LIBRARIES}
        stdc++fs
    )
endif (UNIX)

add_executable(dummyeditor ${SOURCES} ${HEADERS} icons.qrc)

IF (WIN32)
    SET_TARGET_PROPERTIES (dummyeditor
        PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:console /NODEFAULTLIB:library"
    )
    SET_TARGET_PROPERTIES (dummyeditor
        PROPERTIES LINK_FLAGS_RELEASE
        "/SUBSYSTEM:windows /ENTRY:mainCRTStartup /NODEFAULTLIB:library"
    )
    SET_TARGET_PROPERTIES (dummyeditor
        PROPERTIES LINK_FLAGS_MINSIZEREL
        "/SUBSYSTEM:windows /ENTRY:mainCRTStartup /NODEFAULTLIB:library"
    )
    SET_TARGET_PROPERTIES (dummyeditor
        PROPERTIES LINK_FLAGS_RELWITHDEBINFO
        "/SUBSYSTEM:windows /ENTRY:mainCRTStartup /NODEFAULTLIB:library"
    )

    # On Windows, need to specify Boost’s lib dir. Sick.
    if (CMAKE_BUILD_TYPE MATCHES Debug)
        target_link_directories(dummyeditor
            PUBLIC
            ${Boost_LIBRARY_DIR_DEBUG}
        )
    endif (CMAKE_BUILD_TYPE MATCHES Debug)

    if (CMAKE_BUILD_TYPE MATCHES Release)
        target_link_directories(dummyeditor
            PUBLIC
            ${Boost_LIBRARY_DIR_RELEASE}
        )
    endif (CMAKE_BUILD_TYPE MATCHES Release)
ENDIF (WIN32)


target_link_libraries(dummyeditor
    ${DUMMYEDITOR_LINK_LIBRARIES}
)

target_include_directories(dummyeditor PUBLIC ${Boost_INCLUDE_DIR} ${LUA_INCLUDE_DIR})
