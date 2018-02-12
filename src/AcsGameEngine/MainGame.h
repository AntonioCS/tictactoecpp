#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <GL/glew.h>
#include <stdexcept>
#include <string>
#include <memory> //shared_ptr
#include <iostream>
#include <fstream>
#include "GameWindow.h"
#include "Renderer.h"
#include "Util/ColorList.h"

namespace AcsGameEngine {
    
    class Renderer;

    class MainGame {
    public:
        MainGame();
        MainGame(const MainGame &orig) = delete;
        virtual ~MainGame();
        void run();

        GameWindow &getWindow() noexcept {
            return m_window;
        }
        
        Util::ColorList m_color;

    private:

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
        std::shared_ptr<Renderer> m_renderer;        
    };
}
#endif /* GAME_H */

