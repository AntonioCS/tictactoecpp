BIN=game_tictactoe
BUILD_DIR=./build
OBJ_DIR=./obj
TARGET=$(BUILD_DIR)/$(BIN)
CXXFLAGS=-std=c++1z -Wall -g -Werror
LDFLAGS=
#No -mwindows so that I can output to console
#LDLIBS=-Dmain=SDL_main -IC:/msys64/mingw64/include/SDL2 -IC:/msys64/mingw64/include -LC:/msys64/mingw64/lib -lSDL2_ttf -lSDL2_image -lmingw32 -lSDL2main -lSDL2 -lglew32
LDLIBS=`pkg-config --libs --cflags sdl2 SDL2_ttf SDL2_image glew` -lopengl32
CXX=g++
SRC_DIR=./src
SRC=$(shell find $(SRC_DIR) -name '*.cpp')
HEADERS=$(shell find $(SRC_DIR) -name '*.h')
#https://www.gnu.org/software/make/manual/html_node/Text-Functions.html
OBJ=$(addprefix $(OBJ_DIR)/,$(notdir $(patsubst %.cpp, %.o, $(SRC))))
#http://stackoverflow.com/a/1951111/8715
dir_guard=@mkdir -p $(@D)

.PHONY: clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(dir_guard)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	cp -R $(SRC_DIR)/Shaders $(BUILD_DIR)

#To cause recompile when .h files are change
$(OBJ):	$(SRC)
#$(HEADERS)
	$(dir_guard)
	$(CXX) $(CXXFLAGS) -c $? $(LDLIBS)
#Put all the object files in the correct directory
	@mv *.o $(OBJ_DIR)
clean:
	rm -rf $(BUILD_DIR)/* $(OBJ_DIR)/*
