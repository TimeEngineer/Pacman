CC=g++
CFLAGS=-Wall -g -std=c++11
EXEC=main
SRC= $(wildcard ./src/*.cc)
OBJ=$(SRC:.cc=.o)
SFML=-lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system


$(EXEC) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) $(SFML) -o $(EXEC)

%.o : %.cc
	$(CC) $(CFLAGS) -c $< -o $@

all: $(EXEC)

.PHONY: clean mrproper

clean:
	rm -rf $(EXEC) $(OBJ)
del:
	del src\*.o	
	del $(EXEC).exe 
	