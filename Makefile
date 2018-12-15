CC=g++
CFLAGS=-Wall -g
EXEC=main
SRC= $(wildcard *.cc)
SFML=-lsfml-graphics -lsfml-window -lsfml-system

all: $(EXEC)

main: $(SRC)
	$(CC) -o $@ $^ $(LDFLAGS) $(SFML)

.PHONY: clean mrproper

clean:
	rm -rf $(EXEC)