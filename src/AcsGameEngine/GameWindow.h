#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <stdexcept>
#include <string>

namespace AcsGameEngine {
    //https://wiki.libsdl.org/SDL_CreateWindow

    class GameWindow {
    public:

        GameWindow(std::string title = "SDL2 Window", int w = 800, int h = 600, int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, uint32_t flags = SDL_WINDOW_OPENGL)
        //uint32_t flags = SDL_WINDOW_SHOWN)
        : m_title(title), m_w(w), m_h(h), m_x(x), m_y(y), m_flags(flags) {
        }

        GameWindow(const GameWindow &orig) = delete;
        virtual ~GameWindow();

        void open();

        inline int getX() const noexcept {
            return m_x;
        }

        inline int getY() const noexcept {
            return m_y;
        }

        inline int getWidth() const noexcept {
            return m_w;
        }

        inline int getHeight() const noexcept {
            return m_h;
        }

        inline std::string getTitle() const noexcept {
            return m_title;
        }

        void setTitle(std::string title) {
            m_title = title;
            if (m_window != nullptr) {
                SDL_SetWindowTitle(m_window, m_title.c_str());
            }
        }

        void setX(int x) {
            m_x = x;
            applyNewPosition();
        }

        void setY(int y) {
            m_y = y;
            applyNewPosition();
        }

        void setWidth(int w) {
            m_w = w;
            applyNewSize();
        }

        void setHeight(int h) {
            m_h = h;
            applyNewSize();
        }

        SDL_Window *getWindow() const {
            return m_window;
        }

    private:
        std::string m_title;
        int m_w;
        int m_h;
        int m_x;
        int m_y;

        uint32_t m_flags;
        SDL_Window *m_window = nullptr;

        void applyNewPosition() const noexcept {
            if (m_window != nullptr) {
                SDL_SetWindowPosition(m_window, m_x, m_y);
            }
        }

        void applyNewSize() const noexcept {
            if (m_window != nullptr) {
                SDL_SetWindowSize(m_window, m_w, m_h);
            }
        }
    };
}
#endif /* WINDOW_H */

