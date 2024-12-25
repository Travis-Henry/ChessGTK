CC = gcc
CFLAGS = $(shell pkg-config --cflags gtk4) -MMD -MP
LDFLAGS = $(shell pkg-config --libs gtk4)

# Directories
SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build
BIN_DIR := bin

# File names
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.d,$(SRCS))

TARGET = $(BIN_DIR)/ChessGTK

# Default rule
all: $(TARGET)

# Link the target
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

# Compile object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Include dependencies
-include $(DEPS)

# Clean up build artifacts
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

run: $(TARGET)
	$(TARGET)

# Phony targets
.PHONY: all clean run

