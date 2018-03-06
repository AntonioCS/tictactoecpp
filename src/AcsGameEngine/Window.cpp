#include "Window.h"
#include <utility> //std::pair
#include <iostream>

namespace AcsGameEngine {

    Window::Window(std::string title, int x, int y, int w, int h, uint32_t flags)
    : m_window(createWindowPointer(title, x, y, w, h, flags), SDL_DestroyWindow) {
    }

    int Window::getX() const noexcept {
        auto pos = getPosition();
        return pos.first;
    }

    int Window::getY() const noexcept {
        auto pos = getPosition();
        return pos.second;
    }

    int Window::getWidth() const noexcept {
        auto size = getSize();
        return size.first;
    }

    int Window::getHeight() const noexcept {
        auto size = getSize();
        return size.second;
    }

    std::string Window::getTitle() const noexcept {
        return std::string{SDL_GetWindowTitle(getRawPointer())};
    }

    void Window::setTitle(std::string title) {
        SDL_SetWindowTitle(getRawPointer(), title.c_str());
    }

    SDL_Window *Window::getRawPointer() const {
        return m_window.get();
    }

    std::pair<int, int> Window::getPosition() const noexcept {
        int x;
        int y;

        SDL_GetWindowPosition(getRawPointer(), &x, &y);
        return {x, y};
    }

    std::pair<int, int> Window::getSize() const noexcept {
        int w;
        int h;

        SDL_GetWindowSize(getRawPointer(), &w, &h);
        return {w, h};
    }

    SDL_Window *Window::createWindowPointer(std::string title, int x, int y, int w, int h, uint32_t flags) {        
        return SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
    }

}