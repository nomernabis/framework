#include "Window.h"


Window::Window(){
    SDL_Init(SDL_INIT_VIDEO);
    this->running = true;
}

Window::Window(const std::string& title, const int& width, const int& height): Window(){
    this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    this->renderer = new Renderer(this);
}

SDL_Window* Window::getSdlWindow() const{
    return this->window;
}

void Window::close(){
    this->running = false;
}

bool Window::isRunning(){
    return this->running;
}

void Window::setColor(const Color& color){
    this->renderer->setColor(color);
}

void Window::clear(){
    this->renderer->setColor(Colors::WHITE);
    this->renderer->clear();
}

void Window::present(){
    this->renderer->present();
}

void Window::drawRect(Rectangle& rect){
    this->renderer->drawRect(rect);
}

Window::~Window(){
    SDL_DestroyWindow(this->window);
    this->window = NULL;
    delete renderer;
    this->renderer = NULL;
    SDL_Quit();
}