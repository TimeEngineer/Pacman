INC_DIR = ./src/
CC=g++
CFLAGS=-Wall -g -I$(INC_DIR) -std=c++11
EXEC=main
SRC= $(wildcard ./src/*/*.cc) $(wildcard ./src/*.cc)
DEPS= $(wildcard ./src/*/*.hh) $(wildcard ./src/*.hh)
OBJ=$(SRC:.cc=.o)
SFML=-lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system 


$(EXEC) : $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) $(SFML) -o $(EXEC)

%.o : %.cc $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@
%.o : %.hh

all: $(EXEC)

.PHONY: clean mrproper

clean:
	rm -rf $(EXEC) $(OBJ)
del:
	del .\src\Graphics\*.o
	del .\src\Game\*.o
	del .\src\Creature\*.o
	del .\src\Map\*.o
	del .\src\Audio\*.o
	del .\src\Window\*.o
	del .\src\*.o
	del $(EXEC).exe 
	