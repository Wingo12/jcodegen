CC = gcc
CFLAGS = -Wall -Wextra -O2 -D_GNU_SOURCE
TARGET = jcodegen
SRC_DIR = src
SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/generator.c $(SRC_DIR)/langs.c \
          $(SRC_DIR)/names.c $(SRC_DIR)/validator.c $(SRC_DIR)/cli.c \
          $(SRC_DIR)/utils.c
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.c src/jcodegen.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

install: $(TARGET)
	sudo cp $(TARGET) /usr/local/bin/
	sudo chmod 755 /usr/local/bin/$(TARGET)

uninstall:
	sudo rm -f /usr/local/bin/$(TARGET)

run: $(TARGET)
	./$(TARGET) -l c -n 50 -o junk.c

run-py: $(TARGET)
	./$(TARGET) -l py -n 20

run-js: $(TARGET)
	./$(TARGET) -l js -n 30 -o junk.js

help:
	@echo "Commands:"
	@echo "  make          - build"
	@echo "  make clean    - remove objects"
	@echo "  make install  - install"
	@echo "  make run      - test C"
	@echo "  make run-py   - test Python"
	@echo "  make run-js   - test JavaScript"

.PHONY: all clean install uninstall run run-py run-js help
