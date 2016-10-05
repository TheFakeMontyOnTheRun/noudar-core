CXXFLAGS = -Iinclude -O2 -g -c -std=c++0x  -ferror-limit=1
CXX = clang++
OBJS = src/main.o src/CActor.o src/CBaphomet.o src/CBullKnight.o src/CCuco.o src/CDemon.o src/CFalconKnight.o src/CMap.o src/CMoura.o src/CTurtleKnight.o src/CDoorway.o src/IMapElement.o src/CConsoleRenderer.o src/CGame.o
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
