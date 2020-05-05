SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%.cpp,bin\\%.o,$(SRC))

CXXFLAGS = -I ./include -g -std=c++17

CXX = g++

2048.exe: $(OBJ) $(LIB)
	$(CXX) -o $@ $^ $(LDFLAGS)

bin\\%.o: src/%.cpp
	$(CXX) -o $@ -c $^ $(CXXFLAGS)

all: 2048.exe
	2048.exe

clean:
	del $(OBJ)
	del 2048.exe
