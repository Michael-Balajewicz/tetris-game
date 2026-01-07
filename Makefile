CXX = g++-14
CXXFLAGS = -std=c++20 -fmodules-ts -Wall -Wextra -g

TARGET = biquadris

OBJS = \
        types.o types-impl.o \
        abstract.o abstract-impl.o \
        block.o block-impl.o \
        board.o board-impl.o \
        level.o level-impl.o \
        score.o score-impl.o \
        player.o player-impl.o \
        textdisplay.o textdisplay-impl.o \
        commandInterpreter.o commandInterpreter-impl.o \
        game.o game-impl.o \
        main.o

all: sysheaders $(TARGET)

sysheaders:
	$(CXX) $(CXXFLAGS) -c -x c++-system-header fstream
	$(CXX) $(CXXFLAGS) -c -x c++-system-header sstream
	$(CXX) $(CXXFLAGS) -c -x c++-system-header iostream
	$(CXX) $(CXXFLAGS) -c -x c++-system-header ostream
	$(CXX) $(CXXFLAGS) -c -x c++-system-header cstdlib
	$(CXX) $(CXXFLAGS) -c -x c++-system-header vector
	$(CXX) $(CXXFLAGS) -c -x c++-system-header algorithm
	$(CXX) $(CXXFLAGS) -c -x c++-system-header memory
	$(CXX) $(CXXFLAGS) -c -x c++-system-header utility
	$(CXX) $(CXXFLAGS) -c -x c++-system-header string

# ------------- MODULES -------------

types.o: types.cc
	$(CXX) $(CXXFLAGS) -c types.cc

types-impl.o: types-impl.cc types.o
	$(CXX) $(CXXFLAGS) -c types-impl.cc


abstract.o: abstract.cc
	$(CXX) $(CXXFLAGS) -c abstract.cc

abstract-impl.o: abstract-impl.cc abstract.o
	$(CXX) $(CXXFLAGS) -c abstract-impl.cc


block.o: block.cc types.o
	$(CXX) $(CXXFLAGS) -c block.cc

block-impl.o: block-impl.cc block.o types.o
	$(CXX) $(CXXFLAGS) -c block-impl.cc


board.o: board.cc block.o abstract.o
	$(CXX) $(CXXFLAGS) -c board.cc

board-impl.o: board-impl.cc board.o
	$(CXX) $(CXXFLAGS) -c board-impl.cc


level.o: level.cc block.o types.o
	$(CXX) $(CXXFLAGS) -c level.cc

level-impl.o: level-impl.cc level.o block.o types.o
	$(CXX) $(CXXFLAGS) -c level-impl.cc


score.o: score.cc
	$(CXX) $(CXXFLAGS) -c score.cc

score-impl.o: score-impl.cc score.o
	$(CXX) $(CXXFLAGS) -c score-impl.cc


player.o: player.cc board.o level.o score.o block.o types.o
	$(CXX) $(CXXFLAGS) -c player.cc

player-impl.o: player-impl.cc player.o board.o level.o score.o block.o types.o
	$(CXX) $(CXXFLAGS) -c player-impl.cc


textdisplay.o: textdisplay.cc player.o board.o abstract.o
	$(CXX) $(CXXFLAGS) -c textdisplay.cc

textdisplay-impl.o: textdisplay-impl.cc textdisplay.o player.o board.o abstract.o
	$(CXX) $(CXXFLAGS) -c textdisplay-impl.cc


commandInterpreter.o: commandInterpreter.cc types.o
	$(CXX) $(CXXFLAGS) -c commandInterpreter.cc

commandInterpreter-impl.o: commandInterpreter-impl.cc commandInterpreter.o
	$(CXX) $(CXXFLAGS) -c commandInterpreter-impl.cc


game.o: game.cc player.o textdisplay.o commandInterpreter.o
	$(CXX) $(CXXFLAGS) -c game.cc

game-impl.o: game-impl.cc game.o types.o
	$(CXX) $(CXXFLAGS) -c game-impl.cc


main.o: main.cc game.o
	$(CXX) $(CXXFLAGS) -c main.cc


$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

clean:
	rm -f *.o $(TARGET)
	rm -rf gcm.cache
