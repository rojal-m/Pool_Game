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
CCFLAGS +=  -Wno-deprecated-declarations -Wall -Wextra -pedantic -std=c++17 -Weffc++ -I$(SFML_ROOT)/include

LDFLAGS += -L$(SFML_ROOT)/lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

# file which contains the main function
MAINFILE := main.cpp

# Object modules
OBJECTS =  $(OBJDIR)/main.o  $(OBJDIR)/Game.o  $(OBJDIR)/Game_State.o  $(OBJDIR)/Menu_State.o  $(OBJDIR)/Ball.o  $(OBJDIR)/Hole.o  $(OBJDIR)/Item.o  $(OBJDIR)/Stick.o  $(OBJDIR)/Wall.o 

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

$(OBJDIR)/Menu_State.o: $(SRC)/Menu_State.cc dir 
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Menu_State.cc -o $(OBJDIR)/Menu_State.o

$(OBJDIR)/Ball.o: $(SRC)/Ball.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Ball.cc -o $(OBJDIR)/Ball.o

$(OBJDIR)/Hole.o: $(SRC)/Hole.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Hole.cc -o $(OBJDIR)/Hole.o

$(OBJDIR)/Item.o: $(SRC)/Item.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Item.cc -o $(OBJDIR)/Item.o

$(OBJDIR)/Stick.o: $(SRC)/Stick.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Stick.cc -o $(OBJDIR)/Stick.o

$(OBJDIR)/Wall.o: $(SRC)/Wall.cc dir
	$(CCC) -I$(IDIR) $(CCFLAGS) -c $(SRC)/Wall.cc -o $(OBJDIR)/Wall.o

dir:
	@mkdir -p $(OBJDIR)

# 'make clean' removes object files and memory dumps.
clean:
	@ \rm -rf $(OBJDIR)/*.o *.gch core

# 'make zap' also removes the executable and backup files.
zap: clean
	@ \rm -rf main *~
