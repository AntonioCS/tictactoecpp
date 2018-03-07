#include "EventManager.h"

namespace AcsGameEngine {

    void EventManager::onMouseClick(eventFunc func) {
        m_m.attach(SDL_MOUSEBUTTONUP, func);
    }

    void EventManager::onKeyDown(eventFunc func) {
        m_m.attach(SDL_KEYDOWN, func);
    }

    void EventManager::onQuit(eventFunc func) {
        m_m.attach(SDL_QUIT, func);
    }

    void EventManager::onEvent(Uint32 eventName, eventFunc func) {
        m_m.attach(eventName, func);
    }

    void EventManager::processEvents() {
        while (SDL_PollEvent(&m_event)) {
            m_m.trigger(m_event.type, m_event);
        }
    }

    bool EventManager::isKeyPressed(Uint8 key) {
        const Uint8 *keyState = SDL_GetKeyboardState(nullptr);
        return keyState[key];
    }
}