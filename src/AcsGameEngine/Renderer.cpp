#include "Renderer.h"
#include "GameWindow.h"
#include <iostream>

namespace AcsGameEngine {

    Renderer::Renderer(const GameWindow &window, int index, Uint32 flags) : m_window(window) {
        SDL_Window *w = m_window.getWindow();
        m_renderer = SDL_CreateRenderer(w, index, flags);
        if (m_renderer == nullptr) {
            throw std::runtime_error(std::string{"Unable to initialize renderer: "}
            +std::string{SDL_GetError()});
        }
    }


    Renderer::~Renderer() {
    }

    Renderer &Renderer::DrawColor(Util::ColorList::Color &color, uint8_t alpha) {
        DrawColor(color.r, color.g, color.b, alpha);
        return *this;
    }

    Renderer &Renderer::DrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha) {
        SDL_SetRenderDrawColor(m_renderer, r, g, b, alpha);
        return *this;
    }

    Renderer &Renderer::Clear() {
        SDL_RenderClear(m_renderer);
        return *this;
    }

    Renderer &Renderer::Present() {
        SDL_RenderPresent(m_renderer);
        return *this;
    }
}
