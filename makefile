# Pre-compiler and Compiler flags
CXX_FLAGS := -Wall -Wextra -g -ggdb
PRE_FLAGS := -MMD -MP

# Project directory structure
BIN := bin
SRC := source
MAINFILE := $(SRC)/cache_sim.cpp

# Build directories and output
TARGET := $(BIN)/cache_sim
BUILD := build

# Include directories
# INC_DIRS := $(INC) $(shell find $(SRC) -type d) 
# INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# Construct build output and dependency filenames
SRCS := $(shell find $(SRC) -name *.cpp)
OBJS := $(subst $(SRC)/,$(BUILD)/,$(addsuffix .o,$(basename $(SRCS))))
DEPS := $(OBJS:.o=.d)

# Run task
run: build
	@echo "🚀 Executing..."
	./$(TARGET) $(ARGS)

# Build task
build: clean all

# Main task
all: $(TARGET)

# Task producing target from built files
$(TARGET): $(OBJS)
	@echo "🚧 Building..."
	mkdir -p $(dir $@)
	$(CXX) $(OBJS) -o $@ 

# Compile all cpp files
$(BUILD)/%.o: $(SRC)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXX_FLAGS) $(PRE_FLAGS) -c -o $@ $< 

# Clean task
.PHONY: clean
clean:
	@echo "🧹 Clearing..."
	rm -rf build
	rm -rf bin

