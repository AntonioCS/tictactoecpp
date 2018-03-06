#include "MainGame.h"
#include "Renderer.h"

namespace AcsGameEngine {

    std::shared_ptr<Renderer> MainGame::m_renderer2;

    MainGame::MainGame() {
        initSystems();
    }

    MainGame::~MainGame() {
        if (m_logger.is_open()) {
            m_logger.close();
        }
        IMG_Quit();
        SDL_Quit();
    }

    void MainGame::run() {
        gameLoop();
    }

    void MainGame::initSystems() {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            throw std::runtime_error(std::string{"Unable to initialize SDL: "}
            +std::string{SDL_GetError()});
        }

        int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
            throw std::runtime_error(std::string{"SDL_image could not initialize! SDL_image Error: "}
            +std::string{IMG_GetError()});
        }

        m_window.open();
        m_renderer = std::make_shared<Renderer>(m_window);
        m_renderer2 = m_renderer;
        //m_renderer->DrawColor(ColorList::blue);

    }

    void MainGame::gameLoop() {



        /*
        auto t = make_texture("assets/TicTacToe.jpg");
        Sprite board{t, 0, 0, 424, 364};
        Sprite circle{t, 448, 4, 118, 114};
        Sprite cross{t, 448, 131, 121, 114};
         */
        auto t = make_texture("assets/board_items.png");
        Sprite board{t, 0, 0, 650, 480};
        Sprite circle{t, 650, 120, 95, 120};
        Sprite cross{t, 650, 0, 95, 117};

        board.setCenter();
        cross.setDestinationXY(0, 400);
        circle.setDestinationXY(200, 400);

        while (m_gameState != GameState::exit) {
            m_frameStart = SDL_GetTicks();

            processInput();
            update();

            m_renderer->Clear(ColorList::blue);

            m_em.draw();
            board.draw();
            //cross.draw();
            //circle.draw();


            m_renderer->Present();



            //drawGame();

            m_frameTime = SDL_GetTicks() - m_frameStart;

            if (frameDelay > m_frameTime) {
                SDL_Delay(frameDelay - m_frameTime);
            }
        }
    }

    //Another name handleEvents

    void MainGame::processInput() {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            //https://wiki.libsdl.org/SDL_Event
            switch (event.type) {
                    //https://wiki.libsdl.org/SDL_EventType
                case SDL_QUIT:
                    m_gameState = GameState::exit;
                    break;
                case SDL_MOUSEMOTION:
                    //std::cout << e.motion.x << " " << e.motion.y << '\n';
                    break;
                case SDL_MOUSEBUTTONUP:
                    std::cout << "MouseUp\n";
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        std::cout << "Left was release\n";
                    }

                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            m_gameState = GameState::exit;
                            break;
                    }
                    break;
            }
        }
    }

    void MainGame::update() {

    }

    void MainGame::drawGame() {
        m_renderer
                ->Clear()
                .Present()
                ;
    }

    Texture MainGame::make_texture(const std::string &path) {
        Texture t(*m_renderer, path);
        return t;
    }
}

/*
                SDL_Renderer *r;
                SDL_Window *w = getWindow()->getWindow();
                r = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);
                //Initialize renderer color
                SDL_SetRenderDrawColor(r, 0xFF, 0xFF, 0xFF, 0xFF);
                std::string path{SDL_GetBasePath()};
                path += "../assets/TicTacToe.jpg";

                //The final texture
                SDL_Texture *newTexture = NULL;
                //Load image at specified path
                SDL_Surface *loadedSurface = IMG_Load(path.c_str());
                if (loadedSurface == NULL) {
                    printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
                } else {
                    //Create texture from surface pixels
                    newTexture = SDL_CreateTextureFromSurface(r, loadedSurface);
                    if (newTexture == NULL) {
                        printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
                    }

                    //Get rid of old loaded surface
                    SDL_FreeSurface(loadedSurface);
                }

                //Render texture to screen
                SDL_RenderCopy(r, newTexture, NULL, NULL);

                //Update screen
                SDL_RenderPresent(r);

                //return newTexture;
 */
