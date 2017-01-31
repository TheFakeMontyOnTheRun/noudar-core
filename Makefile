CXXFLAGS = -Inoudar-core/include -Incurses-version -O2 -g -c -std=c++0x  -ferror-limit=1 -Werror -Wall
CXX = clang++

OBJS = ncurses-version/main.o \
    ncurses-version/CConsoleRenderer.o \
    noudar-core/src/CActor.o \
    noudar-core/src/CMonster.o \
    noudar-core/src/CTeam.o \
    noudar-core/src/CMap.o \
    noudar-core/src/CHuntApproach.o \
    noudar-core/src/CCharacter.o \
    noudar-core/src/CCharacterArchetype.o \
    noudar-core/src/CElixirFountain.o \
    noudar-core/src/CDoorway.o \
    noudar-core/src/Common.o \
    noudar-core/src/IFileLoaderDelegate.o \
    noudar-core/src/IMapElement.o \
    noudar-core/src/CGame.o \
    noudar-core/src/CPlainFileLoader.o \
    noudar-core/src/CGameDelegate.o \
    noudar-core/src/commands/CActorMeleeAttackCommand.o \
    noudar-core/src/commands/IGameCommand.o \
    noudar-core/src/commands/CHitscanAttackCommand.o \
    noudar-core/src/commands/CMoveActorCommand.o \
    noudar-core/src/commands/CLoadNewLevelCommand.o \
    noudar-core/src/commands/CTurnActorCommand.o \
    noudar-core/src/commands/CQuitCommand.o \
    noudar-core/src/commands/CNullCommand.o \
    noudar-core/src/commands/CEndTurnCommand.o

LDFLAGS = -lncurses

TARGET = noudar

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
	rm src/*~
	rm include/*~
	rm *~
