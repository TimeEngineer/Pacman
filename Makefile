CC=g++
CFLAGS=-Wall -g
EXEC=main
SRC= $(wildcard ./src/*.cc)
SFML=-lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

all: $(EXEC)

main: $(SRC)
	$(CC) -o $@ $^ $(LDFLAGS) $(SFML)

.PHONY: clean mrproper

clean:
	rm -rf $(EXEC)