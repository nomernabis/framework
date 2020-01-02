#pragma once

#include<SDL2/SDL.h>

class Window;
#include "Color.h"
#include "Rectangle.h"

class Renderer{
    SDL_Renderer* sdlRenderer;
    Color color;
    public:
    Renderer(Window* window);
    void setColor(const Color& color);
    Color& getColor() const;
    void clear();
    void present();
    SDL_Renderer* getSdlRenderer() const;
    void drawRect(Rectangle& rect);
};