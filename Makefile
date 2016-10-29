CXXFLAGS = -Inoudar-core/include -Incurses-version -O2 -g -c -std=c++0x  -ferror-limit=1
CXX = clang++
OBJS = ncurses-version/main.o ncurses-version/CConsoleRenderer.o \
    noudar-core/src/CActor.o \
    noudar-core/src/CBullKnight.o \
    noudar-core/src/CCuco.o \
    noudar-core/src/CMap.o \
    noudar-core/src/CDoorway.o \
    noudar-core/src/IMapElement.o \
    noudar-core/src/CGame.o \
    noudar-core/src/CGameDelegate.o \
LDFLAGS = -lncurses
TARGET = knights2

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
	rm src/*~
	rm include/*~
	rm *~
