CXX=g++
CXXFLAGS=-std=c++11 -Wall -Wextra -pedantic

SRC=genshin.cpp
OBJ=$(SRC:.cpp=.o)
EXEC=genshin

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ): $(SRC)
	$(CXX) $(CXXFLAGS) -c $^

clean:
	rm -f $(OBJ) $(EXEC)
