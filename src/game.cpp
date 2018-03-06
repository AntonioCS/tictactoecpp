
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <vector>
#include <tuple>
#include <array>
#include <memory>
#include <functional>
#include <unordered_map>
#include <optional>

//#include "AcsGameEngine/GameWindow.h"
//#include "AcsGameEngine/Renderer.h"

bool running = true;
bool playable = true;
SDL_Window *window;
SDL_Renderer *renderer;
constexpr int win_w = 800;
constexpr int win_h = 600;
constexpr int board_w = 653;
constexpr int board_h = 480;
constexpr int board_x = win_w / 2 - board_w / 2;
constexpr int board_y = win_h / 2 - board_h / 2 + 50;
SDL_Rect cross{654, 0, 95, 117};
SDL_Rect circle{ 654, 120, 95, 120};
SDL_Rect turnText{ 654, 240, 36, 99};
SDL_Rect winText{ 701, 240, 36, 160};
SDL_Rect drawText{ 654, 342, 36, 114};
constexpr const char *assets = "assets/board_items.png";

enum class Type {
    cross,
    circle
};

Type turn{Type::circle};

class Spot {
    bool m_clicked{false};
    Type m_type;
    SDL_Rect m_area;
    int m_draw_x{0};
    int m_draw_y{0};
public:
    Spot() = default;

    void setArea(int x, int y, int w, int h) noexcept {
        m_area.x = x;
        m_area.y = y;
        m_area.w = w;
        m_area.h = h;
    }

    void reset() {
        m_clicked = false;
    }

    const SDL_Rect &getRect() const noexcept {
        return m_area;
    }

    std::pair<int, int> getDrawXY() const noexcept {
        return {m_draw_x, m_draw_y};
    }

    bool isClicked() const noexcept {
        return m_clicked;
    }

    void setClicked(Type type, int x, int y) noexcept {
        m_type = type;
        m_clicked = true;
        m_draw_x = x;
        m_draw_y = y;
    }

    Type getType() const noexcept {
        return m_type;
    }

    bool isInsideArea(int x, int y) const noexcept {
        //std::cout << x << " - " << m_area.x << " - " << m_area.w + m_area.x << '\n';
        return x >= m_area.x && x <= m_area.w + m_area.x &&
                y >= m_area.y && y <= m_area.h + m_area.y;
    }
};

constexpr uint8_t total_spots{9};
std::array<Spot, total_spots> spots;

bool isInsideBoard(int x, int y) {
    return x >= board_x && x <= board_w + board_x && y >= board_y && y <= board_h + board_y;
}

struct EventData {
};

template <typename keyType, typename funcType>
class Mediator {
    using eventFunc = funcType; //std::function<void(void)>;
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
public:

};

class EventManager {
    SDL_Event m_event;
    using eventFunc = std::function<void(SDL_Event &event)>;
    Mediator<Uint32, eventFunc> m_m;
public:

    void onMouseClick(eventFunc func) {
        m_m.attach(SDL_MOUSEBUTTONUP, func);
    }

    void onKeyDown(eventFunc func) {
        m_m.attach(SDL_KEYDOWN, func);
    }

    void onQuit(eventFunc func) {
        m_m.attach(SDL_QUIT, func);
    }

    void onEvent(Uint32 eventName, eventFunc func) {
        m_m.attach(eventName, func);
    }

    void processEvents() {
        while (SDL_PollEvent(&m_event)) {
            m_m.trigger(m_event.type, m_event);
        }
    }

    bool isKeyPressed(Uint8 key) {
        const Uint8 *keyState = SDL_GetKeyboardState(nullptr);
        return keyState[key];
    }
};

void drawBoard(SDL_Texture *all) {
    SDL_Rect a{0, 0, board_w, board_h};
    SDL_Rect b{board_x, board_y, board_w, board_h};

    SDL_RenderCopy(renderer, all, &a, &b);
}

void drawCross(SDL_Texture *all, int x, int y, SDL_Rect *dest = nullptr) {
    SDL_Rect a{654, 0, 95, 117};
    SDL_Rect b{x, y, a.w, a.h};

    if (dest == nullptr) {
        dest = &b;
    }

    SDL_RenderCopy(renderer, all, &a, dest);
}

void drawCircle(SDL_Texture *all, int x, int y, SDL_Rect *dest = nullptr) {
    SDL_Rect a{ 654, 120, 95, 120};
    SDL_Rect b{x, y, a.w, a.h};

    if (dest == nullptr) {
        dest = &b;
    }

    SDL_RenderCopy(renderer, all, &a, dest);
}

void displayItem(SDL_Texture *all, SDL_Rect *source, int y = 0) {
    int x = win_w / 2 - source->w / 2;
    //y = y - source->h/2;
    SDL_Rect b{x, y, source->w, source->h};

    SDL_RenderCopyEx(renderer, all, source, &b, -90, nullptr, SDL_FLIP_NONE);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);    
    SDL_RenderDrawRect(renderer, &b);
}

void displayTurn(SDL_Texture *all) {
    displayItem(all, &turnText, 10);
    int y = 10;
    SDL_Rect turnItem{win_w / 2 - turnText.w / 2 , y+ turnText.h, y + turnText.h / 2 - 15, 30};
    turn == Type::circle ? drawCircle(all, 1, 1, &turnItem) : drawCross(all, 1, 1, &turnItem);
}

void displayWinner(SDL_Texture *all) {
    displayItem(all, &winText);

    //int x = win_w / 2 - winText.w / 2;
    //int y = 5;
    //SDL_Rect b{x, y, winText.w, winText.h};

    //SDL_RenderCopyEx(renderer, all, &winText, &b, -90, nullptr, SDL_FLIP_NONE);    

    //turn == Type::circle ? drawCircle(all, 1, 1, &turnItem) : drawCross(all, 1, 1, &turnItem);
}

void displayDraw(SDL_Texture *all) {
    displayItem(all, &drawText);
}

std::optional<Type> checkForWin() {
    constexpr uint8_t total_combinations{8};
    constexpr uint8_t winN{3};

    constexpr std::array<std::array<int, winN>, total_combinations> winningCombinations{
        {
            {
                0, 1, 2
            },
            {
                3, 4, 5
            },
            {
                6, 7, 8
            },
            {
                0, 3, 6
            },
            {
                1, 4, 7
            },
            {
                2, 5, 8
            },
            {
                0, 4, 8
            },
            {
                2, 4, 6
            }
        }};

    for (const auto &comb : winningCombinations) {
        if (spots[comb[0]].isClicked() && spots[comb[1]].isClicked() && spots[comb[2]].isClicked() &&
                spots[comb[0]].getType() == spots[comb[1]].getType() && spots[comb[1]].getType() == spots[comb[2]].getType()) {

            return spots[comb[0]].getType();
        }
    }

    return {};
}

void drawStuff(SDL_Texture *all) {
    int spots_taken = 0;
    drawBoard(all);
    for (const auto &spot : spots) {
        if (spot.isClicked()) {
            spots_taken++;
            auto coords = spot.getDrawXY();

            if (spot.getType() == Type::circle) {
                drawCircle(all, coords.first, coords.second);
            } else {
                drawCross(all, coords.first, coords.second);
            }
        }

        //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        //SDL_RenderDrawRect(renderer, &(spot.getRect()));

    }

    auto res = checkForWin();

    if (res.has_value()) {
        displayWinner(all);
        playable = false;
        /*   
            std::cout << "VITORIA!! ";
            if (res.value() == Type::cross) {
                std::cout << "das cruzes\n";
            } else {
                std::cout << "dos circulos\n";
            }*/
    } else {
        if (spots_taken == total_spots) {
            displayDraw(all);
            playable = false;
        } else {
            displayTurn(all);
        }
    }
}

void createSpots() {
    constexpr int r_w = 208;
    constexpr int r_h = 150;
    constexpr int space = 16;

    int i{0};
    for (int iY = 0; iY < 3; iY++) {
        for (int iX = 0; iX < 3; iX++) {
            int x = board_x + (r_w * iX) + (space * iX) - (1 * iX);
            int y = board_y + (r_h * iY) + (space * iY) - (1 * iY);

            spots[i++].setArea(x, y, r_w, r_h);
        }
    }
}

void resetGame() {
    for (auto &spot : spots) {
        if (spot.isClicked()) {
            spot.reset();
        }
    }
    turn = Type::circle;
    playable = true;
}

int main(int argc, char** argv) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "Unable to start SDL2\n";
        exit(-1);
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cout << "Unable to start SDL_image\n";
        exit(-1);
    }

    window = SDL_CreateWindow("test",
            SDL_WINDOWPOS_UNDEFINED, // initial x position
            SDL_WINDOWPOS_UNDEFINED, // initial y position
            win_w, // width, in pixels
            win_h, // height, in pixels
            SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    constexpr int FPS = 60;
    constexpr int frameDelay = 1000 / FPS;

    uint32_t frameStart;
    int frameTime;

    SDL_Surface *tmp = IMG_Load(assets);
    SDL_Texture *all = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);

    createSpots();

    EventManager em;


    em.onEvent(SDL_QUIT, [](SDL_Event & e) {
        running = false;
    });

    em.onKeyDown([](SDL_Event & e) {
        if (e.key.keysym.sym == SDLK_ESCAPE)
            running = false;
        if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_RETURN2)
            resetGame();
        if (e.key.keysym.sym == SDLK_1) {
            //spots[0].
        }
    });

    em.onMouseClick([](SDL_Event & event) {
        if (!playable)
            return;

        if (event.button.button == SDL_BUTTON_LEFT) {
            int x = event.button.x;
            int y = event.button.y;

            if (isInsideBoard(x, y)) {
                for (auto &spot : spots) {
                    if (spot.isInsideArea(x, y)) {                        
                        if (spot.isClicked() == false) {
                            const SDL_Rect &r = spot.getRect();
                            if (turn == Type::circle) {
                                x = r.x + (circle.w / 2);
                                y = r.y + 15;
                            } else {
                                x = r.x + cross.w / 2;
                                y = r.y + 15;
                            }

                            spot.setClicked(turn, x, y);
                            turn = turn == Type::cross ? Type::circle : Type::cross;
                        }
                        break;
                    }
                }
            }
        }
    });


    while (running) {
        frameStart = SDL_GetTicks();
        em.processEvents();

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        if (em.isKeyPressed(SDL_SCANCODE_KP_ENTER)) {
            //            text_x++;
           // std::cout << "MERDa\n";
        }

        if (em.isKeyPressed(SDL_SCANCODE_LEFT)) {
            //          text_x--;
        }

        if (em.isKeyPressed(SDL_SCANCODE_UP)) {
            //        text_y--;
        }

        if (em.isKeyPressed(SDL_SCANCODE_DOWN)) {
            //      text_y++;
        }

        drawStuff(all);

        SDL_RenderPresent(renderer);

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    IMG_Quit();
    SDL_Quit();


    return 0;
}