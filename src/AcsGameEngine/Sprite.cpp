#include "Sprite.h"
#include "Texture.h"
#include "Renderer.h"

namespace AcsGameEngine {

    Sprite::Sprite(const Texture &texture) : m_texture(texture) {

    }

    Sprite::Sprite(const Texture &texture, int x, int y, int w, int h) : Sprite(texture) {
        setSourceXYWH(x, y, w, h);
    }

    Sprite::Sprite(const Texture &texture, int sx, int sy, int sw, int sh, int dx, int dy, int dw, int dh) : Sprite(texture, sx, sy, sw, sh) {
        setDestinationXYWH(dx, dy, dw, dh);
    }

    Sprite::Sprite(const Texture &texture, SDL_Rect source) : Sprite(texture, source.x, source.y, source.w, source.h) {

    }

    Sprite::Sprite(const Texture &texture, SDL_Rect source, SDL_Rect destination) : Sprite(texture, source.x, source.y, source.w, source.h, destination.x, destination.y, destination.w, destination.h) {

    }

    Sprite::~Sprite() {
    }

    void Sprite::setSourceXYWH(int x, int y, int w, int h) {
        m_source.x = x;
        m_source.y = y;
        m_source.w = w;
        m_source.h = h;
    }

    void Sprite::setDestinationXYWH(int x, int y, int w, int h) {
        m_destination.x = x;
        m_destination.y = y;
        m_destination.w = w;
        m_destination.h = h;
    }

    void Sprite::setSourceXY(int x, int y) {
        m_source.x = x;
        m_source.y = y;
    }

    void Sprite::setSourceWH(int w, int h) {
        m_source.w = w;
        m_source.h = h;
    }

    void Sprite::setDestinationXY(int x, int y) {
        m_destination.x = x;
        m_destination.y = y;
    }

    void Sprite::setDestinationWH(int w, int h) {
        m_destination.w = w;
        m_destination.h = h;
    }

    void Sprite::draw() {
        SDL_Renderer *r = m_texture.getRenderer().getRenderer();
        SDL_Texture *t = m_texture.getTexture();

        SDL_RenderCopy(r, t, &m_source, &m_destination);
    }
}
