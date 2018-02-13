#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

namespace AcsGameEngine {

    class Texture;

    class Sprite {
    public:
        Sprite(const Texture &texture);
        Sprite(const Texture &texture, int x = 0, int y = 0, int w = 0, int h = 0);        
        Sprite(const Texture &texture, int sx = 0, int sy = 0, int sw = 0, int sh = 0, int dx = 0, int dy = 0, int dw = 0, int dh = 0);
        Sprite(const Texture &texture, SDL_Rect source);
        Sprite(const Texture &texture, SDL_Rect source, SDL_Rect destination);
        Sprite(const Sprite& orig) = delete;
        virtual ~Sprite();

        void setSourceXYWH(int, int, int, int);
        void setDestinationXYWH(int, int, int, int);

        void setSourceXY(int, int);
        void setDestinationXY(int, int);

        void setSourceWH(int, int);
        void setDestinationWH(int, int);

        void draw();
    private:
        const Texture &m_texture;
        SDL_Rect m_destination;
        SDL_Rect m_source;
    };
}
#endif /* SPRITE_H */

