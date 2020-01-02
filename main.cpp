#include <iostream>
#include "Window.h"
#include "Rectangle.h"
#include "Colors.h"
#include <SDL2/SDL.h>

int main(){
    SDL_Event event;
    Window window("Window", 640, 480);
    Rectangle player(280, 100, 40, 40);
    Rectangle wall(100, 200, 80, 240);
    player.setColor(Colors::RED);
    wall.setColor(Colors::BLUE);
    const int SPEED = 5;
    while(window.isRunning()){
        while(SDL_PollEvent(&event) != 0){
            if (event.type == SDL_QUIT){
                window.close();
            } else 
            if (event.type == SDL_KEYDOWN){
                Pair position = player.getPosition();
                switch (event.key.keysym.sym){
                    case SDLK_LEFT:
                        position.x -= SPEED;
                        break;
                    case SDLK_RIGHT:
                        position.x += SPEED;
                        break;
                    case SDLK_DOWN:
                        position.y += SPEED;
                        break;
                    case SDLK_UP:
                        position.y -= SPEED;
                        break;
                    default:
                        break;
                }
                Rectangle newPosition = {position.x, position.y, player.getWidth(), player.getHeight()};
                if (!newPosition.isIntersects(wall)){
                    player.setPosition(position);
                }
            }
        }
        window.clear();
        window.drawRect(player);
        window.drawRect(wall);
        window.present();
    }
    return 0;
}