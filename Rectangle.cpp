#include "Rectangle.h"

Rectangle::Rectangle(const int& x, const int& y, const int& width, const int& height){
    this->sdlRect = {x, y, width, height};
}

void Rectangle::setColor(const Color& color){
    this->color = color;
}

Color Rectangle::getColor(){
    return this->color;
}

void Rectangle::setX(const int& x){
    this->sdlRect.x = x;
}

int Rectangle::getX(){
    return this->sdlRect.x;
}

int Rectangle::getY(){
    return this->sdlRect.y;
}

void Rectangle::setY(const int& y){
    this->sdlRect.y = y;
}

void Rectangle::setWidth(const int& width){
    this->sdlRect.w = width;
}

int Rectangle::getWidth(){
    return this->sdlRect.w;
}

void Rectangle::setHeight(const int& height){
    this->sdlRect.h = height;
}

int Rectangle::getHeight(){
    return this->sdlRect.h;
}

int Rectangle::getBorder(){
    return this->border;
}

void Rectangle::setBorder(const int& border){
    this->border = border;
}

void Rectangle::setBorderColor(const Color& color){
    this->borderColor = color;
}

Color Rectangle::getBorderColor(){
    return this->borderColor;
}

SDL_Rect Rectangle::getSdlRect(){
    return this->sdlRect;
}

void Rectangle::setPosition(int x, int y){
    this->setX(x);
    this->setY(y);
}

void Rectangle::setPosition(Pair position){
    this->setPosition(position.x, position.y);
}

Pair Rectangle::getPosition(){
    return {this->getX(), this->getY()}; 
}

bool Rectangle::isIntersects(Rectangle otherRect){
    Rectangle* left = this;
    Rectangle* right = &otherRect;

    if(this->getX() < otherRect.getX()){
        left = this;
        right = &otherRect;
    } else
    if(this->getX() > otherRect.getX()){
        left = &otherRect;
        right = this;
    } 

    const int rect1Left = left->getX();
    const int rect1Top = left->getY();
    const int rect1Right = rect1Left + left->getWidth();
    const int rect1Bottom = rect1Top + left->getHeight();

    const int rect2Left = right->getX();
    const int rect2Top = right->getY();
    const int rect2Right = rect2Left + right->getWidth();
    const int rect2Bottom = rect2Top + right->getHeight();

    if(rect1Right > rect2Left && (rect2Top > rect1Top && rect2Top < rect1Bottom || rect2Bottom > rect1Top && rect2Bottom < rect1Bottom
        || rect1Top > rect2Top && rect1Top < rect2Bottom || rect1Bottom > rect2Top && rect1Bottom < rect2Bottom)){
        return true;
    }
    return false;
}