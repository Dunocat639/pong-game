# Variables de compilador i flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c23 -g
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Nom de l'executable
TARGET = pong

# Fitxers font
SRC = pong.c

# Regla principal (la que s'executa per defecte)
all: $(TARGET)

# Com es construeix l'executable
$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

# Per netejar el desordre (com quan amagues la roba bruta sota el llit)
clean:
	rm -f $(TARGET)

# Per compilar i executar d'una tacada
run: all
	./$(TARGET)