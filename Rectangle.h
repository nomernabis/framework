#pragma once

#include <SDL2/SDL.h>
#include "Color.h"

struct Pair{
    int x, y;
};

class Rectangle{
    SDL_Rect sdlRect;
    Color color;
    Color borderColor;
    int border;
    public:
    Rectangle(const int& x, const int& y, const int& width, const int& height);
    void setX(const int& x);
    int getX();
    void setY(const int& y);
    int getY();
    void setWidth(const int& width);
    int getWidth();
    void setHeight(const int& height);
    int getHeight();
    int getBorder();
    void setBorder(const int& border);
    Color getColor();
    void setColor(const Color& color);
    void setBorderColor(const Color& color);
    Color getBorderColor();
    SDL_Rect getSdlRect();
    void setPosition(int x, int y);
    void setPosition(Pair position);
    Pair getPosition();
    bool isIntersects(Rectangle otherRect);
};