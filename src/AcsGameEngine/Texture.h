
#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL.h>
#include <string>
#include <memory>


namespace AcsGameEngine {

    class Renderer;    
    
    class Texture {
    public:
        Texture(const Renderer &renderer);
        Texture(const Renderer &renderer, const std::string &);
        Texture(const Renderer &renderer, const std::string &, uint16_t, uint16_t);
        Texture(const Texture &orig) = default;
        virtual ~Texture();
        
        void load(const std::string &, uint16_t w = 0, uint16_t h = 0) const;
        void load(const char *, uint16_t w = 0, uint16_t h = 0);
        
        const Renderer &getRenderer() const {
            return m_renderer;
        }

        SDL_Texture *getTexture() const {
            return m_texture;            
        }

    private:
        std::unique_ptr<SDL_Texture> m_texture;
        const Renderer &m_renderer;
        
        uint16_t m_width;
        uint16_t m_height;
    };
}

#endif /* IMAGE_H */

