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
#include "Window.h"
#include "Renderer.h"
#include "Texture.h"
#include "Sprite.h"
#include "Util/ColorList.h"
#include "ECS/EntityManager.h"

#include <vector>

namespace AcsGameEngine {
/*
    class Entity {
    public:
        Entity() {}
        Entity(const Entity &orig) = delete;
        Entity(Entity &&orig) = default;

        virtual ~Entity() {}

        virtual void update() = 0;
        virtual void draw() = 0;
    };
*/

    //EC END

    using Util::ColorList;

    class Renderer;

    class MainGame {
    public:
        MainGame();
        MainGame(const MainGame &orig) = delete;
        virtual ~MainGame();
        void run();

        Window &getWindow() noexcept {
            return m_window;
        }



        Texture make_texture(const std::string &);

        static std::shared_ptr<Renderer> m_renderer2;
        
        ECS::EntityManager &getEM() {
            return m_em;
        }
    private:
        ECS::EntityManager m_em;

        void initSystems();

        void gameLoop();
        void processInput();
        void update();
        void drawGame();

        enum class GameState {
            play,
            exit
        };

        const int FPS = 60;
        const int frameDelay = 1000 / FPS;

        uint32_t m_frameStart;
        int m_frameTime;

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

