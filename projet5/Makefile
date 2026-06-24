CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = gestion_personnes

SOURCES = main.c person.c file_handler.c console.c
OBJECTS = $(SOURCES:.c=.o)

# Cible par défaut
all: $(TARGET)

# Compilation de l'exécutable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "✓ Compilation réussie: $(TARGET)"

# Compilation des fichiers objets
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "✓ Compilation: $<"

# Nettoyage
clean:
	rm -f $(OBJECTS) $(TARGET) *.bin *.txt
	@echo "✓ Nettoyage effectué"

# Exécution
run: $(TARGET)
	./$(TARGET)

# Récompilation complète
rebuild: clean all

.PHONY: all clean run rebuild
