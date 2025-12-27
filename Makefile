# Makefile for Orange Updater

CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall -Wextra -I./include
LDFLAGS = `pkg-config --libs gtk+-3.0`

TARGET = orange-updater
SRC_DIR = src
BUILD_DIR = build
SCRIPT_DIR = scripts

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Installation paths
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin
DATADIR = $(PREFIX)/share/orange-updater
DESKTOPDIR = $(PREFIX)/share/applications

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo "Build complete! Run with: ./$(TARGET)"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
	@echo "Clean complete"

install: $(TARGET)
	install -d $(BINDIR)
	install -d $(DATADIR)/scripts
	install -m 755 $(TARGET) $(BINDIR)/
	install -m 755 $(SCRIPT_DIR)/*.sh $(DATADIR)/scripts/
	@echo "Installation complete!"
	@echo "Run with: orange-updater"

uninstall:
	rm -f $(BINDIR)/$(TARGET)
	rm -rf $(DATADIR)
	@echo "Uninstall complete"

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean install uninstall run
