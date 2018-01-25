#include "Renderer.h"
/*
namespace AcsGameEngine {

    Renderer::Renderer(std::unique_ptr<GameWindow> window) : m_window(window) {
        m_renderer = SDL_CreateRenderer(m_window->getWindow(), -1, SDL_RENDERER_ACCELERATED);
        if (m_renderer == nullptr) {
            throw std::runtime_error(std::string{"Unable to initialize renderer: "}
            +std::string{SDL_GetError()});
        }
    }

    Renderer::Renderer(const Renderer& orig) {
    }

    Renderer::~Renderer() {
    }
}
*/