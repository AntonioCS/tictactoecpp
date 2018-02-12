#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "Util/ColorList.h"

namespace AcsGameEngine {


    class GameWindow;

    class Renderer {
    public:
        Renderer(const GameWindow &window, int index = -1, Uint32 flags = SDL_RENDERER_ACCELERATED);
        Renderer(const Renderer& orig) = delete;
        virtual ~Renderer();

        Renderer &DrawColor(Util::ColorList::Color &color, uint8_t alpha = 255);
        Renderer &DrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha = 255);
        Renderer &Clear();
        Renderer &Present();
    private:
        SDL_Renderer *m_renderer = nullptr;
        const GameWindow &m_window;
    };
}

#endif /* RENDERER_H */

