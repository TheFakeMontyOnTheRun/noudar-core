cmake_minimum_required(VERSION 3.5)
project(noudar_core)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(noudar-core/include)



find_package(Curses REQUIRED)

set(SOURCE_FILES
        noudar-core/include/CActor.h
        noudar-core/include/CBaphomet.h
        noudar-core/include/CBullKnight.h
        noudar-core/include/CConsoleRenderer.h
        noudar-core/include/CCuco.h
        noudar-core/include/CDemon.h
        noudar-core/include/CDoorway.h
        noudar-core/include/CFalconKnight.h
        noudar-core/include/CGame.h
        noudar-core/include/CMap.h
        noudar-core/include/CMoura.h
        noudar-core/include/CTurtleKnight.h
        noudar-core/include/IRenderer.h
        noudar-core/include/Vec2i.h
        noudar-core/src/CActor.cpp
        noudar-core/src/CBaphomet.cpp
        noudar-core/src/CGameDelegate.cpp
        noudar-core/src/CBullKnight.cpp
        noudar-core/src/CConsoleRenderer.cpp
        noudar-core/src/CCuco.cpp
        noudar-core/src/CDemon.cpp
        noudar-core/src/CDoorway.cpp
        noudar-core/src/CFalconKnight.cpp
        noudar-core/src/CGame.cpp
        noudar-core/src/CMap.cpp
        noudar-core/src/CMoura.cpp
        noudar-core/src/CTurtleKnight.cpp
        noudar-core/src/IMapElement.cpp
        ncurses-version/main.cpp)

include_directories(${CURSES_INCLUDE_DIR})

add_executable(noudar_core ${SOURCE_FILES})

target_link_libraries(noudar_core ${CURSES_LIBRARIES} )