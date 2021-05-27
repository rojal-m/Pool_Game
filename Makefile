#
# Makefile
#

# Folders
SRC = source

# this is the directory I will compile from (i.e. the argument to -I)
IDIR := include

# all object files will be put here
OBJDIR := objdir

# Compiler (g++)
CCC = g++

# Compiling flags
CCFLAGS += -std=c++17 -Wno-deprecated-declarations -Wall -Wextra -Wpedantic -pedantic -Werror -Weffc++ -Wold-style-cast -Woverloaded-virtual -fmax-errors=5 -g -I$(SFML_ROOT)/include

LDFLAGS += -L$(SFML_ROOT)/lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

# file which contains the main function
MAINFILE := main.cpp

# Object modules
OBJECTS =  $(OBJDIR)/main.o  $(OBJDIR)/Game.o  $(OBJDIR)/Game_State.o  $(OBJDIR)/Game_State_2.o $(OBJDIR)/Menu_State.o  $(OBJDIR)/Ball.o  $(OBJDIR)/Hole.o  $(OBJDIR)/Stick.o  $(OBJDIR)/Wall.o $(OBJDIR)/Player.o

# Main objetice - created with 'make' or 'make main'.
main: $(OBJECTS) Makefile
	$(CCC) -I$(IDIR) $(CCFLAGS) -o main $(OBJECTS) $(LDFLAGS)

# Part objectives
$(OBJDIR)/main.o:  $(SRC)/main.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/main.cc -o $(OBJDIR)/main.o

$(OBJDIR)/Game.o: $(SRC)/Game.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Game.cc -o $(OBJDIR)/Game.o

$(OBJDIR)/Game_State.o: $(SRC)/Game_State.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Game_State.cc -o $(OBJDIR)/Game_State.o

$(OBJDIR)/Game_State_2.o: $(SRC)/Game_State_2.cc dir
	 $(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Game_State_2.cc -o $(OBJDIR)/Game_State_2.o


$(OBJDIR)/Menu_State.o: $(SRC)/Menu_State.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Menu_State.cc -o $(OBJDIR)/Menu_State.o

$(OBJDIR)/Ball.o: $(SRC)/Ball.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Ball.cc -o $(OBJDIR)/Ball.o

$(OBJDIR)/Hole.o: $(SRC)/Hole.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Hole.cc -o $(OBJDIR)/Hole.o

$(OBJDIR)/Stick.o: $(SRC)/Stick.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Stick.cc -o $(OBJDIR)/Stick.o

$(OBJDIR)/Wall.o: $(SRC)/Wall.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Wall.cc -o $(OBJDIR)/Wall.o

$(OBJDIR)/Player.o: $(SRC)/Player.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Player.cc -o $(OBJDIR)/Player.o

dir:
	@mkdir -p $(OBJDIR)

# 'make clean' removes object files and memory dumps.
clean:
	@ \rm -rf $(OBJDIR)/*.o *.gch core

# 'make zap' also removes the executable and backup files.
zap: clean
	@ \rm -rf main *~

run:
	./main
