
#include "Renderer.h"
#include "Window.h"

Renderer::Renderer(Window* window){
   this->sdlRenderer = SDL_CreateRenderer(window->getSdlWindow(), -1, SDL_RENDERER_ACCELERATED);
}

void Renderer::clear(){
    SDL_RenderClear(this->sdlRenderer);
}

void Renderer::present(){
    SDL_RenderPresent(this->sdlRenderer);
}

void Renderer::setColor(const Color& color){
    this->color = color;
    SDL_SetRenderDrawColor(this->sdlRenderer, this->color.red, this->color.green, this->color.blue, this->color.alpha);
}

SDL_Renderer* Renderer::getSdlRenderer() const{
    return this->sdlRenderer;
}

void Renderer::drawRect(Rectangle& rect){
    this->setColor(rect.getColor());
    SDL_Rect sdlRect = rect.getSdlRect();
    SDL_RenderFillRect(this->sdlRenderer, &sdlRect);
}