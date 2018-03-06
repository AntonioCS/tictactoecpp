#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <memory>
#include "Util/ColorList.h"

namespace AcsGameEngine {


    class Window;

    class Renderer {
    public:
        Renderer(const Window &window, int index = -1, Uint32 flags = SDL_RENDERER_ACCELERATED);
        Renderer(const Renderer& orig) = delete;

        Renderer &DrawColor(const Util::ColorList::Color &, uint8_t alpha = 255);
        Renderer &DrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha = 255);
        Renderer &Clear();
        Renderer &Clear(const Util::ColorList::Color &);
        Renderer &Present();

        SDL_Renderer *getRawPointer() const;
        const Window &getWindow() const;
    private:
        std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer) > m_renderer;
        const Window &m_window;
        SDL_Renderer *createRendererPointer(SDL_Window *w, int index, Uint32 flags);
    };
}

#endif /* RENDERER_H */

