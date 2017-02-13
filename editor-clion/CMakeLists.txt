cmake_minimum_required(VERSION 3.5)
project(editor_clion)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(../noudar-core/include
                    ../editor-core/include
                    ../ncurses-editor
                    )

find_package(Curses REQUIRED)

set(SOURCE_FILES
        ../editor-core/include/CEditor.h
        ../noudar-core/include/CActor.h
        ../noudar-core/include/CMonsterGenerator.h
        ../noudar-core/include/commands/CActorMeleeAttackCommand.h
        ../noudar-core/include/commands/CEndTurnCommand.h
        ../noudar-core/include/commands/CLoadNewLevelCommand.h
        ../noudar-core/include/commands/CMoveActorCommand.h
        ../noudar-core/include/commands/CNullCommand.h
        ../noudar-core/include/commands/CQuitCommand.h
        ../noudar-core/include/commands/CTurnActorCommand.h
        ../noudar-core/include/commands/IGameCommand.h
        ../noudar-core/include/CPlainFileLoader.h
        ../ncurses-version/CConsoleRenderer.h
        ../noudar-core/include/CMonster.h
        ../noudar-core/include/CDoorway.h
        ../noudar-core/include/CElixirFountain.h
        ../noudar-core/include/CGame.h
        ../noudar-core/include/CMap.h
        ../noudar-core/include/IRenderer.h
        ../noudar-core/include/Vec2i.h
        ../editor-core/src/commands/CActorMeleeAttackCommand.cpp
        ../editor-core/src/commands/CEndTurnCommand.cpp
        ../editor-core/src/commands/CLoadNewLevelCommand.cpp
        ../editor-core/src/commands/CMoveActorCommand.cpp
        ../editor-core/src/commands/CNullCommand.cpp
        ../editor-core/src/commands/CQuitCommand.cpp
        ../editor-core/src/commands/CTurnActorCommand.cpp
        ../editor-core/src/commands/IGameCommand.cpp
        ../editor-core/src/CEditor.cpp
        ../noudar-core/src/CActor.cpp
        ../noudar-core/src/CGameDelegate.cpp
        ../noudar-core/src/CKnight.cpp
        ../noudar-core/src/CMonster.cpp
        ../noudar-core/src/CDoorway.cpp
        ../noudar-core/src/CGame.cpp
        ../noudar-core/src/CPlainFileLoader.cpp
        ../noudar-core/src/CMap.cpp
        ../noudar-core/src/IMapElement.cpp
        ../noudar-core/src/CElixirFountain.cpp
        ../ncurses-version/CConsoleRenderer.cpp
        ../ncurses-editor/main.cpp)

include_directories(${CURSES_INCLUDE_DIR})

add_executable(editor_clion ${SOURCE_FILES})

target_link_libraries(editor_clion ${CURSES_LIBRARIES} )