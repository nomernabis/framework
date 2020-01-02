#include "Color.h"

Color::Color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha){
    this->red = red;
    this->green = green;
    this->blue = blue;
    this->alpha = alpha;
}
Color::Color():alpha(0xFF){}



