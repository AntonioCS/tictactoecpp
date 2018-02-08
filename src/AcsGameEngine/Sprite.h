/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sprite.h
 * Author: António Simões <antoniocs@gmail.com>
 *
 * Created on 29 January 2018, 18:44
 */

#ifndef SPRITE_H
#define SPRITE_H

#include <GL/glew.h>
#include <array>

namespace AcsGameEngine {

    class Sprite {
    public:
        Sprite();
        Sprite(const Sprite& orig);
        virtual ~Sprite();

        void init(float x, float y, float width, float height);
        void draw();
    private:
        float m_x;
        float m_y;
        float m_width;
        float m_height;

        //32bit
        GLuint m_vboID;

    };
}

#endif /* SPRITE_H */

