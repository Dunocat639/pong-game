# Variables de compilador i flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c23 -g
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Nom de l'executable
TARGET = pong

# Troba automàticament tots els .c dins src/
SRC = $(wildcard src/*.c)

# Genera els .o corresponents (src/foo.c -> build/foo.o)
OBJ = $(patsubst src/%.c, build/%.o, $(SRC))

# Regla principal
all: $(TARGET)

# Enllaça tots els .o per crear l'executable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

# Compila cada .c a .o (inclou headers de src/)
build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -I src -c $< -o $@

# Neteja
clean:
	rm -f $(TARGET)
	rm -rf build/

# Compila i executa
run: all
	./$(TARGET)