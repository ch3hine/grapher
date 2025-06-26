TARGET = app

SRC_DIR = src
INC_DIR = include
OBJ_DIR = build
BIN_DIR = bin

CXX = g++
CXXFLAGS = -Wall -g -std=c++20 -I$(INC_DIR) -I/usr/include/freetype2
LDFLAGS = -lglfw -lGL -ldl -lfreetype

SRCS = $(wildcard $(SRC_DIR)/*.cpp) src/glad.c

OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(wildcard $(SRC_DIR)/*.cpp)) $(OBJ_DIR)/glad.o

all: $(BIN_DIR)/$(TARGET)

$(OBJ_DIR)/glad.o: src/gl.c | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@


$(BIN_DIR)/$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/glad.o: src/glad.c | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)/$(TARGET)
