#include "MainGame.h"
#include "Renderer.h"

namespace AcsGameEngine {

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
        //m_renderer->DrawColor(m_color.red);
        m_renderer->DrawColor(0, 0, 0);
    }


    void MainGame::gameLoop() {
        while (m_gameState != GameState::exit) {
            processInput();
            drawGame();
        }
    }

    void MainGame::processInput() {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    m_gameState = GameState::exit;
                    break;
                case SDL_MOUSEMOTION:
                    //std::cout << e.motion.x << " " << e.motion.y << '\n';
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

    void MainGame::drawGame() {
        m_renderer
                ->Clear().
                Present()
                ;
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
