#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

namespace AcsGameEngine {

    class Texture;

    class Sprite {
    public:
        Sprite(const Texture &texture);
        Sprite(const Texture &texture, int, int, int, int);
        Sprite(const Texture &texture, int, int, int, int, int, int, int, int);
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

        void setCenter();

        void draw();

        void border();
    private:
        const Texture &m_texture;
        SDL_Rect m_destination;
        SDL_Rect m_source;

        bool showBorder;
    };
}
#endif /* SPRITE_H */

