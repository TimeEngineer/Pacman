INC_DIR = ./src/
CC=g++
CFLAGS=-Wall -g -I$(INC_DIR) -std=c++11
EXEC=main
SRC= $(wildcard ./src/*/*.cc) $(wildcard ./src/*.cc)
DEPS= $(wildcard ./src/*/*.hh) $(wildcard ./src/*.hh)
OBJ=$(SRC:.cc=.o)
SFML=-lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system 
INC_DIR = -I./src -I./src/Audio -I./src/Creature -I./src/Game -I./src/Graphics -I./src/Map -I./src/Window


$(EXEC) : $(OBJ) 
	$(CC) $(OBJ) $(SFML) $(CFLAGS) -o $(EXEC)

%.o : %.cc
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@
	
.depend: $(SRC)
	g++ -std=c++11 -MM $(SRC)  > .depend
-include .depend

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
	