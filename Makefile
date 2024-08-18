# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

# Directories
INCLUDE_DIR = include
SRC_DIR = src
BUILD_DIR = build
TEST_DIR = tests

# Target executable
TARGET = $(BUILD_DIR)/hello

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cc)

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.cc, $(BUILD_DIR)/%.o, $(SRCS))

# Rule to build the target executable
$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -o $(TARGET) $(OBJS)

# Rule to build object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Create the build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean up build files
clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(SRC_DIR)/*.o

# Run tests
test: $(TARGET)
	$(TARGET)

# Lint the code
lint:
	python3 cpplint.py --filter=-legal/copyright $(SRC_DIR)/*.cc $(INCLUDE_DIR)/*.h $(TEST_DIR)/*.cpp

# Phony targets
.PHONY: clean test lint

