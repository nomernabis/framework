#pragma once

#include<SDL2/SDL.h>
class Color{
    public:
    Uint8 red;
    Uint8 green;
    Uint8 blue;
    Uint8 alpha;
    Color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 0xFF);
    Color();
};