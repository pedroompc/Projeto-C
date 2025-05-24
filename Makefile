EXEC = jogo
SRC = jogo_tigrinho.c
CFLAGS = -Wall -I/opt/homebrew/include
LIBS = -L/opt/homebrew/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo

all:
	gcc $(SRC) -o $(EXEC) $(CFLAGS) $(LIBS)

run: all
	./$(EXEC)

clean:
	rm -f $(EXEC)
