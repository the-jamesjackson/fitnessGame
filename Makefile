CXX := g++
CXXFLAGS := -g -Wall --std=c++11

all: fitness_game

# Compile object files
main.o: main.cpp user.h exercise.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

user.o: user.cpp user.h cardio.h strength-training.h exercise.h
	$(CXX) $(CXXFLAGS) -c user.cpp -o user.o

cardio.o: cardio.cpp cardio.h exercise.h
	$(CXX) $(CXXFLAGS) -c cardio.cpp -o cardio.o

strength-training.o: strength-training.cpp strength-training.h exercise.h
	$(CXX) $(CXXFLAGS) -c strength-training.cpp -o strength-training.o

exercise.o: exercise.cpp cardio.h strength-training.h exercise.h
	$(CXX) $(CXXFLAGS) -c exercise.cpp -o exercise.o

# Link executable
fitness_game: main.o user.o cardio.o strength-training.o exercise.o
	$(CXX) $(CXXFLAGS) main.o user.o cardio.o strength-training.o exercise.o -o fitness_game

clean:
	rm -f *.o fitness_game *~

.PHONY: clean all