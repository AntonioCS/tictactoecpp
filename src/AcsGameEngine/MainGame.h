#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <GL/glew.h>
#include <stdexcept>
#include <string>
#include <memory>
#include <iostream>
#include <fstream>
#include "GameWindow.h"
#include "Sprite.h"
#include "GLSLProgram.h"

namespace AcsGameEngine {

    class MainGame {
    public:
        MainGame();
        MainGame(const MainGame &orig) = delete;
        virtual ~MainGame();
        void run();

        GameWindow &getWindow() noexcept {
            return m_window;
        }

    private:
        Sprite m_sprite;

        void initSystems();
        void initShaders();
        void gameLoop();
        void processInput();
        void drawGame();

        enum class GameState {
            play,
            exit
        };

        std::ofstream m_logger;

        void writeToLog(std::string data) {
            if (m_logger.is_open() == false) {
                m_logger.open(std::string{SDL_GetBasePath()}
                +"debug.log");
            }

            m_logger << data << '\n';
            m_logger.flush();
        }
        
        GameState m_gameState = GameState::play;
        GameWindow m_window;

        GLSLProgram m_colourProgram;
    };
}
#endif /* GAME_H */

