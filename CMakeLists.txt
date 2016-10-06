cmake_minimum_required(VERSION 3.5)
project(noudar_core)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(include)



find_package(Curses REQUIRED)

set(SOURCE_FILES
    include/CActor.h
    include/CBaphomet.h
    include/CBullKnight.h
    include/CConsoleRenderer.h
    include/CCuco.h
    include/CDemon.h
    include/CDoorway.h
    include/CFalconKnight.h
    include/CGame.h
    include/CMap.h
    include/CMoura.h
    include/CTurtleKnight.h
    include/IRenderer.h
    include/Vec2i.h
    src/CActor.cpp
    src/CBaphomet.cpp
    src/CBullKnight.cpp
    src/CConsoleRenderer.cpp
    src/CCuco.cpp
    src/CDemon.cpp
    src/CDoorway.cpp
    src/CFalconKnight.cpp
    src/CGame.cpp
    src/CMap.cpp
    src/CMoura.cpp
    src/CTurtleKnight.cpp
    src/IMapElement.cpp
    src/main.cpp)

include_directories(${CURSES_INCLUDE_DIR})

add_executable(noudar_core ${SOURCE_FILES})

target_link_libraries(noudar_core ${CURSES_LIBRARIES} )