cmake_minimum_required(VERSION 3.5)
project(noudar_core)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(noudar-core/include)

find_package(Curses REQUIRED)

set(SOURCE_FILES
        noudar-core/include/commands/CMoveActorCommand.h
        noudar-core/include/commands/CActorMeleeAttackCommand.h
        noudar-core/include/commands/CHitscanAttackCommand.h
        noudar-core/include/commands/CEndTurnCommand.h
        noudar-core/include/commands/CLoadNewLevelCommand.h
        noudar-core/include/commands/CNullCommand.h
        noudar-core/include/commands/CQuitCommand.h
        noudar-core/include/commands/CTurnActorCommand.h
        noudar-core/include/commands/IGameCommand.h
        noudar-core/include/CPlainFileLoader.h
        noudar-core/include/CActor.h
        noudar-core/include/CElixirFountain.h
        noudar-core/include/CMonsterGenerator.h
        ncurses-version/CConsoleRenderer.h
        noudar-core/include/CMonster.h
        noudar-core/include/CDoorway.h
        noudar-core/include/CGame.h
        noudar-core/include/CMap.h
        noudar-core/include/IRenderer.h
        noudar-core/include/Vec2i.h
        noudar-core/include/CTeam.h
        noudar-core/include/CCharacterArchetype.h
        noudar-core/include/CHuntApproach.h
        noudar-core/include/CCharacter.h
        noudar-core/src/commands/CMoveActorCommand.cpp
        noudar-core/src/commands/CActorMeleeAttackCommand.cpp
        noudar-core/src/commands/CHitscanAttackCommand.cpp
        noudar-core/src/commands/CEndTurnCommand.cpp
        noudar-core/src/commands/CLoadNewLevelCommand.cpp
        noudar-core/src/commands/CNullCommand.cpp
        noudar-core/src/commands/CQuitCommand.cpp
        noudar-core/src/commands/CTurnActorCommand.cpp
        noudar-core/src/commands/IGameCommand.cpp
        noudar-core/src/CPlainFileLoader.cpp
        noudar-core/src/Vec2i.cpp
        noudar-core/src/CActor.cpp
        noudar-core/src/CCharacter.cpp
        noudar-core/src/CCharacterArchetype.cpp
        noudar-core/src/CHuntApproach.cpp
        noudar-core/src/CElixirFountain.cpp
        noudar-core/src/CGameDelegate.cpp
        ncurses-version/CConsoleRenderer.cpp
        noudar-core/src/CMonster.cpp
        noudar-core/src/IFileLoaderDelegate.cpp
        noudar-core/src/CTeam.cpp
        noudar-core/src/CDoorway.cpp
        noudar-core/src/CGame.cpp
        noudar-core/src/CMap.cpp
        noudar-core/src/IMapElement.cpp
        ncurses-version/main.cpp)

include_directories(${CURSES_INCLUDE_DIR})

add_executable(noudar_core ${SOURCE_FILES})

target_link_libraries(noudar_core ${CURSES_LIBRARIES} )