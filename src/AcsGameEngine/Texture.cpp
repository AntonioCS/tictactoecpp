
#include "Texture.h"
#include "Renderer.h"
#include <SDL2/SDL_image.h>

namespace AcsGameEngine {

    Texture::Texture(const Renderer &renderer) : m_renderer(renderer) {
    }

    Texture::Texture(const Renderer &renderer, const std::string &p) : Texture(renderer) {
        load(p.c_str());
    }

    Texture::~Texture() {
        if (m_texture != nullptr) {
            SDL_DestroyTexture(m_texture);
        }
    }

    void Texture::load(const std::string &path, uint16_t w, uint16_t h) const {
        load(path.c_str());
    }

    void Texture::load(const char *path, uint16_t w, uint16_t h) {
        SDL_Surface *tmp = IMG_Load(path);
        m_texture = SDL_CreateTextureFromSurface(m_renderer.getRenderer(), tmp);
        SDL_FreeSurface(tmp);

        if (m_texture == nullptr) {
            //error
        }

    }

}
