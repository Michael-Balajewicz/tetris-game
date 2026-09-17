CXX = g++-14
CXXFLAGS = -std=c++20 -fmodules-ts -Wall -Wextra -g

TARGET = biquadris

# Source tree layout
CORE = src/core
GAME = src/game
UI   = src/ui
BLD  = build

# Object files live in build/ so the source tree stays clean.
$(shell mkdir -p $(BLD))

OBJS = \
        $(BLD)/types.o $(BLD)/types-impl.o \
        $(BLD)/abstract.o $(BLD)/abstract-impl.o \
        $(BLD)/block.o $(BLD)/block-impl.o \
        $(BLD)/board.o $(BLD)/board-impl.o \
        $(BLD)/level.o $(BLD)/level-impl.o \
        $(BLD)/score.o $(BLD)/score-impl.o \
        $(BLD)/player.o $(BLD)/player-impl.o \
        $(BLD)/textdisplay.o $(BLD)/textdisplay-impl.o \
        $(BLD)/commandInterpreter.o $(BLD)/commandInterpreter-impl.o \
        $(BLD)/game.o $(BLD)/game-impl.o \
        $(BLD)/main.o

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
# Order matters: a module interface must be compiled before anything
# that imports it, so each rule lists the .o files it imports from.

# --- core ---
$(BLD)/types.o: $(CORE)/types.cc
	$(CXX) $(CXXFLAGS) -c $(CORE)/types.cc -o $@

$(BLD)/types-impl.o: $(CORE)/types-impl.cc $(BLD)/types.o
	$(CXX) $(CXXFLAGS) -c $(CORE)/types-impl.cc -o $@


$(BLD)/abstract.o: $(CORE)/abstract.cc
	$(CXX) $(CXXFLAGS) -c $(CORE)/abstract.cc -o $@

$(BLD)/abstract-impl.o: $(CORE)/abstract-impl.cc $(BLD)/abstract.o
	$(CXX) $(CXXFLAGS) -c $(CORE)/abstract-impl.cc -o $@


# --- game ---
$(BLD)/block.o: $(GAME)/block.cc $(BLD)/types.o
	$(CXX) $(CXXFLAGS) -c $(GAME)/block.cc -o $@

$(BLD)/block-impl.o: $(GAME)/block-impl.cc $(BLD)/block.o $(BLD)/types.o
	$(CXX) $(CXXFLAGS) -c $(GAME)/block-impl.cc -o $@


$(BLD)/board.o: $(GAME)/board.cc $(BLD)/block.o $(BLD)/abstract.o
	$(CXX) $(CXXFLAGS) -c $(GAME)/board.cc -o $@

$(BLD)/board-impl.o: $(GAME)/board-impl.cc $(BLD)/board.o
	$(CXX) $(CXXFLAGS) -c $(GAME)/board-impl.cc -o $@


$(BLD)/level.o: $(GAME)/level.cc $(BLD)/block.o $(BLD)/types.o
	$(CXX) $(CXXFLAGS) -c $(GAME)/level.cc -o $@

$(BLD)/level-impl.o: $(GAME)/level-impl.cc $(BLD)/level.o $(BLD)/block.o $(BLD)/types.o
	$(CXX) $(CXXFLAGS) -c $(GAME)/level-impl.cc -o $@


$(BLD)/score.o: $(GAME)/score.cc
	$(CXX) $(CXXFLAGS) -c $(GAME)/score.cc -o $@

$(BLD)/score-impl.o: $(GAME)/score-impl.cc $(BLD)/score.o
	$(CXX) $(CXXFLAGS) -c $(GAME)/score-impl.cc -o $@


$(BLD)/player.o: $(GAME)/player.cc $(BLD)/board.o $(BLD)/level.o $(BLD)/score.o $(BLD)/block.o $(BLD)/types.o
	$(CXX) $(CXXFLAGS) -c $(GAME)/player.cc -o $@

$(BLD)/player-impl.o: $(GAME)/player-impl.cc $(BLD)/player.o $(BLD)/board.o $(BLD)/level.o $(BLD)/score.o $(BLD)/block.o $(BLD)/types.o
	$(CXX) $(CXXFLAGS) -c $(GAME)/player-impl.cc -o $@


# --- ui ---
$(BLD)/textdisplay.o: $(UI)/textdisplay.cc $(BLD)/player.o $(BLD)/board.o $(BLD)/abstract.o
	$(CXX) $(CXXFLAGS) -c $(UI)/textdisplay.cc -o $@

$(BLD)/textdisplay-impl.o: $(UI)/textdisplay-impl.cc $(BLD)/textdisplay.o $(BLD)/player.o $(BLD)/board.o $(BLD)/abstract.o
	$(CXX) $(CXXFLAGS) -c $(UI)/textdisplay-impl.cc -o $@


$(BLD)/commandInterpreter.o: $(UI)/commandInterpreter.cc $(BLD)/types.o
	$(CXX) $(CXXFLAGS) -c $(UI)/commandInterpreter.cc -o $@

$(BLD)/commandInterpreter-impl.o: $(UI)/commandInterpreter-impl.cc $(BLD)/commandInterpreter.o
	$(CXX) $(CXXFLAGS) -c $(UI)/commandInterpreter-impl.cc -o $@


# --- top level ---
$(BLD)/game.o: $(GAME)/game.cc $(BLD)/player.o $(BLD)/textdisplay.o $(BLD)/commandInterpreter.o
	$(CXX) $(CXXFLAGS) -c $(GAME)/game.cc -o $@

$(BLD)/game-impl.o: $(GAME)/game-impl.cc $(BLD)/game.o $(BLD)/types.o
	$(CXX) $(CXXFLAGS) -c $(GAME)/game-impl.cc -o $@


$(BLD)/main.o: src/main.cc $(BLD)/game.o
	$(CXX) $(CXXFLAGS) -c src/main.cc -o $@


$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

clean:
	rm -rf $(BLD) $(TARGET) gcm.cache

.PHONY: all sysheaders clean
