#pragma once

#include <SDL2/SDL.h>
#include <functional>

namespace AcsGameEngine {

    class EventManager {
        SDL_Event m_event;
        using eventFunc = std::function<void(SDL_Event &event)>;


        template <typename keyType, typename funcType>
        class Mediator {
            using eventFunc = funcType;
            std::unordered_map<keyType, std::vector<eventFunc>> m_events;

        public:

            void attach(keyType eventName, eventFunc func) {
                m_events[eventName].push_back(func);
            }

            template <typename... Args>
            void trigger(keyType eventName, Args... args) {
                if (m_events.find(eventName) != m_events.end()) {
                    for (const auto &f : m_events[eventName]) {
                        f(args...);
                    }
                }
            }
        };
        Mediator<Uint32, eventFunc> m_m;

    public:

        void onMouseClick(eventFunc func);

        void onKeyDown(eventFunc func);

        void onQuit(eventFunc func);

        void onEvent(Uint32 eventName, eventFunc func);

        void processEvents();

        bool isKeyPressed(Uint8 key);
    };
}