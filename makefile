#-----------------------------------------------------------------------------
# Author: Adam Strutt
# Creation date: 06/01/2018
# File: makefile
#-----------------------------------------------------------------------------

TARGET = main

# Files
SRC = src
INC = include
BIN = bin

SOURCE = $(wildcard $(SRC)/*.cpp)
OBJECT = $(patsubst %,$(BIN)/%, $(notdir $(SOURCE:.cpp=.o)))

CC = g++

# Colors
RED = \033[1;31m
GREEN = \033[1;32m
BLUE = \033[1;34m
YELLOW = \033[1;33m
NC = \033[1;0m

# Linking
$(BIN)/$(TARGET): $(OBJECT)
	@echo "$(YELLOW)Linking...$(NC)"
	$(CC) -o $@ $^
	@echo "$(GREEN)Finished linking!$(NC)"

# Compiling
$(BIN)/%.o: $(SRC)/%.cpp
	@echo "$(YELLOW)Compiling...$(NC)"
	$(CC) -c $< -o $@

.PHONY: run clean help

# Build and Run
run: $(BIN)/$(TARGET)
	@echo "$(GREEN)Running...$(NC)"
	./$(BIN)/$(TARGET)

# Remove build files
clean:
	@echo "$(RED)Deleting...$(NC)"
	rm -f $(BIN)/$(TARGET) $(OBJECT)
	@echo "$(GREEN)Complete!$(NC)"

help:
	@echo "target: $(TARGET)"
	@echo "source: $(SOURCE)"
	@echo "object: $(OBJECT)"
	@echo "$(BLUE)Commands:$(NC)"
	@echo "run clean"
