# Makefile

# Kompilator i flagi
CXX = g++
CXXFLAGS = -std=c++17

# Biblioteki SFML
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Ścieżki do plików źródłowych
SRC = main.cpp features/kolo.cpp
OBJ = $(SRC:.cpp=.o)

# Nazwa końcowego pliku wykonywalnego
TARGET = game

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
