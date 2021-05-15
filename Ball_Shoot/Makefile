CC := g++
FLAGS := -std=c++17 -Wall -Wextra -Wpedantic -pedantic -Werror -Weffc++ -Wold-style-cast -Woverloaded-virtual -fmax-errors=5 -g
LIB := -lsfml-window -lsfml-graphics -lsfml-system

all: start

start: main.cc
	$(CC) $(FLAGS) main.cc -o start $(LIB)
