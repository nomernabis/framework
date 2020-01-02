#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "Renderer.h"
#include "Color.h"
#include "Rectangle.h"
#include "Colors.h"


class Window{
    SDL_Window* window;
    Renderer* renderer;
    bool running;
    public:
    Window();
    Window(const std::string& title, const int& width, const int& height);
    SDL_Window* getSdlWindow() const;
    bool isRunning();
    void close();
    void setColor(const Color& color);
    void clear();
    void present();
    void drawRect(Rectangle& rect);
    ~Window();
};
