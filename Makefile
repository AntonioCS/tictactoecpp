BIN=game_tictactoe
BUILD_DIR=./build
OBJ_DIR=./obj
TARGET=$(BUILD_DIR)/$(BIN)
#-MD Produces path to .h files
#CXXFLAGS=-std=c++1z -Wall -g -Werror -MD
CXXFLAGS=-std=c++1z -Wall -g -Werror
# -fsanitize=address
LDFLAGS=
#No -mwindows so that I can output to console
LDLIBS:=$(shell pkg-config --libs --cflags sdl2 SDL2_ttf SDL2_image glew) -lopengl32
CXX=g++
SRC_DIR=./src
SRC=$(shell find $(SRC_DIR) -name '*.cpp')
HEADERS=$(shell find $(SRC_DIR) -name '*.h')
#https://www.gnu.org/software/make/manual/html_node/Text-Functions.html
#OBJ:=$(addprefix $(OBJ_DIR)/,$(notdir $(patsubst %.cpp, %.o, $(SRC))))
OBJ:=$(addprefix $(OBJ_DIR)/,$(patsubst %.cpp, %.o, $(subst ./,,$(SRC)) ))
#http://stackoverflow.com/a/1951111/8715
dir_guard=@mkdir -p $(@D)

.PHONY: clean

main: LDLIBS:=$(filter-out -mwindows, $(LDLIBS))
main: ./src/main.cpp ./src/AcsGameEngine/Window.cpp ./src/AcsGameEngine/Renderer.cpp ./src/AcsGameEngine/EventManager.cpp ./src/AcsGameEngine/Util/ColorList.cpp
#./src/AcsGameEngine/Renderer.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)


game: LDLIBS:=$(filter-out -mwindows, $(LDLIBS))
game: ./src/game.cpp
# ./src/AcsGameEngine/GameWindow.cpp ./src/AcsGameEngine/Renderer.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

all: $(TARGET)

debug: LDLIBS:=$(filter-out -mwindows, $(LDLIBS))
debug: $(TARGET)

#%.o : %.cpp
#	$(CXX) $(CXXFLAGS) -c $< -o $(OBJ_DIR)/$@

$(TARGET): $(OBJ)
	$(dir_guard)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	cp -r assets/ $(BUILD_DIR);

./obj/src/AcsGameEngine/GameWindow.o: ./src/AcsGameEngine/GameWindow.cpp
		mkdir -p $(dir $@)
		$(CXX) $(CXXFLAGS) -o $@ -c $< $(LDLIBS)

./obj/src/AcsGameEngine/MainGame.o: ./src/AcsGameEngine/MainGame.cpp
		mkdir -p $(dir $@)
		$(CXX) $(CXXFLAGS) -o $@ -c $< $(LDLIBS)

./obj/src/AcsGameEngine/Renderer.o: ./src/AcsGameEngine/Renderer.cpp
		mkdir -p $(dir $@)
		$(CXX) $(CXXFLAGS) -o $@ -c $< $(LDLIBS)

./obj/src/AcsGameEngine/Sprite.o: ./src/AcsGameEngine/Sprite.cpp
		mkdir -p $(dir $@)
		$(CXX) $(CXXFLAGS) -o $@ -c $< $(LDLIBS)

./obj/src/AcsGameEngine/State.o: ./src/AcsGameEngine/State.cpp
		mkdir -p $(dir $@)
		$(CXX) $(CXXFLAGS) -o $@ -c $< $(LDLIBS)

./obj/src/AcsGameEngine/Texture.o: ./src/AcsGameEngine/Texture.cpp
		mkdir -p $(dir $@)
		$(CXX) $(CXXFLAGS) -o $@ -c $< $(LDLIBS)

./obj/src/AcsGameEngine/TextureManager.o: ./src/AcsGameEngine/TextureManager.cpp
		mkdir -p $(dir $@)
		$(CXX) $(CXXFLAGS) -o $@ -c $< $(LDLIBS)

./obj/src/AcsGameEngine/Util/ColorList.o: ./src/AcsGameEngine/Util/ColorList.cpp
		mkdir -p $(dir $@)
		$(CXX) $(CXXFLAGS) -o $@ -c $< $(LDLIBS)

./obj/src/main.o: ./src/main.cpp
		mkdir -p $(dir $@)
		$(CXX) $(CXXFLAGS) -o $@ -c $< $(LDLIBS)

./obj/src/AcsGameEngine/EventManager.o: ./src/AcsGameEngine/EventManager.cpp
		mkdir -p $(dir $@)
		$(CXX) $(CXXFLAGS) -o $@ -c $< $(LDLIBS)

./obj/src/AcsGameEngine/ECS/Component.o: ./src/AcsGameEngine/ECS/Component.cpp
		mkdir -p $(dir $@)
		$(CXX) $(CXXFLAGS) -o $@ -c $< $(LDLIBS)

./obj/src/AcsGameEngine/ECS/Entity.o: ./src/AcsGameEngine/ECS/Entity.cpp
		mkdir -p $(dir $@)
		$(CXX) $(CXXFLAGS) -o $@ -c $< $(LDLIBS)

./obj/src/AcsGameEngine/ECS/EntityManager.o: ./src/AcsGameEngine/ECS/EntityManager.cpp
		mkdir -p $(dir $@)
		$(CXX) $(CXXFLAGS) -o $@ -c $< $(LDLIBS)

./obj/src/DrawRedRectangle.o: ./src/DrawRedRectangle.cpp
		mkdir -p $(dir $@)
		$(CXX) $(CXXFLAGS) -o $@ -c $< $(LDLIBS)

	

#$(OBJ) : $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
#	echo $<
#@mkdir -p
#$(CXX) $(CXXFLAGS) -c $< -o $(OBJ_DIR)/$@

clean:
	rm -rf $(BUILD_DIR)/* $(OBJ_DIR)/*
