# Compiler to be used
CXX = g++

# Flags to be passed to the compiler
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Werror

# Directory for object files
OBJ_DIR = obj

# Name of the executable
TARGET = mud.bin

# List of source files
SOURCES = json11.cpp utils.cpp Commands.cpp Doors.cpp Game.cpp main.cpp Object.cpp Mob.cpp Player.cpp Room.cpp World.cpp

# List of object files generated from source files
OBJECTS = $(addprefix $(OBJ_DIR)/, $(SOURCES:.cpp=.o))

# Rule to build everything (default rule)
all: directories $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Rule to build object files from source files
$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS)  -o $@ -c $<

# Rule to create the necessary directories
directories:
	mkdir -p $(OBJ_DIR)

# Rule to clean the build
clean:
	rm -rf $(TARGET) $(OBJ_DIR)

# Rule to re-build everything
rebuild: clean all
