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

namespace AcsGameEngine {

    class MainGame {
    public:
        MainGame();
        MainGame(const MainGame &orig) = delete;
        virtual ~MainGame();
        void run();
        
        std::shared_ptr<GameWindow> getWindow() const noexcept {
            return m_window;
        }

    private:
        void initSystems();
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
        std::shared_ptr<GameWindow> m_window;
    };
}
#endif /* GAME_H */

