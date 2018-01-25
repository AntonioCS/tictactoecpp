#include "GameWindow.h"
namespace AcsGameEngine {

    GameWindow::~GameWindow() {
        if (m_window != nullptr) {
            SDL_DestroyWindow(m_window);
        }
    }

    void GameWindow::open() {
        if (m_window == nullptr) {
            m_window = SDL_CreateWindow(m_title.c_str(), m_x, m_y, m_w, m_h, m_flags);
            if (m_window == nullptr) {
                throw std::runtime_error(std::string{"Could not create window: "}
                +std::string{SDL_GetError()});
            }
        }
    }
}