#include "Renderer.h"
#include "Window.h"

namespace AcsGameEngine {

    Renderer::Renderer(const Window &window, int index, Uint32 flags) : m_renderer(createRendererPointer(window.getRawPointer(), index, flags), SDL_DestroyRenderer), m_window(window) {

        if (m_renderer == nullptr) {
            throw std::runtime_error(std::string{"Unable to initialize renderer: "}
            +std::string{SDL_GetError()});
        }
    }

    SDL_Renderer *Renderer::createRendererPointer(SDL_Window *w, int index, Uint32 flags) {
        return SDL_CreateRenderer(w, index, flags);
    }

    Renderer &Renderer::DrawColor(const Util::ColorList::Color &color, uint8_t alpha) {
        DrawColor(color.r, color.g, color.b, alpha);
        return *this;
    }

    Renderer &Renderer::DrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha) {
        SDL_SetRenderDrawColor(getRawPointer(), r, g, b, alpha);
        return *this;
    }

    Renderer &Renderer::Clear(const Util::ColorList::Color &color) {
        DrawColor(color);
        return Clear();
    }

    Renderer &Renderer::Clear() {
        SDL_RenderClear(getRawPointer());
        return *this;
    }

    Renderer &Renderer::Present() {
        SDL_RenderPresent(getRawPointer());
        return *this;
    }

    SDL_Renderer *Renderer::getRawPointer() const {
        return m_renderer.get();
    }

    const Window &Renderer::getWindow() const {
        return m_window;
    }
}
