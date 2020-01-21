#include <iostream>
#include <cstdlib>
#include "Window.h"
#include "Rectangle.h"
#include "Colors.h"
#include <SDL2/SDL.h>
#include "game/Map.h"

const int SIZE = 64;


void drawMap(Matrix map, Window& window, int mapOffsetX, int mapOffsetY){
    Rectangle rect = {0, 0, SIZE, SIZE};
    rect.setColor(Colors::BLUE);
    for(int i=0; i < map.size(); ++i){
        for(int j=0; j < map[i].size(); ++j){
            if(map[i][j] == 0){
                rect.setX(j * SIZE + mapOffsetX);
                rect.setY(i * SIZE + mapOffsetY);
                window.drawRect(rect);
            }
        }
    }
}


class ViewPort{
    static const int BUFFER_SIZE = 2;
    Matrix map;
    Matrix originalMap;
    public:
    SDL_Rect buffer;
    SDL_Rect viewPort;
    ViewPort(int centerX, int centerY, int viewWidth, int viewHeight, Matrix map);
    ~ViewPort();
    Matrix getMap();
    void print();
    void move(Pair);
    void moveMapX(int x);
    void moveMapY(int y);
    Pair getOffset();
    Matrix& getOriginalMap();
};

Matrix& ViewPort::getOriginalMap(){
    return this->originalMap;
}

Matrix ViewPort::getMap(){
    return this->map;
}


void ViewPort::moveMapX(int x){
    if(x < 0){
        std::cout << "moveLeft\n";
        if(buffer.x - 1 >= 0){
            for(int i=0; i < buffer.h; ++i){
                std::cout << i << " " << i + buffer.y << " " << buffer.x - 1 << "\n";
                map[i].insert(map[i].begin(), originalMap[i + buffer.y][buffer.x - 1]);
                map[i].pop_back();
            }
            buffer.x -= 1;
        }
    } else if (x > 0 && buffer.x + buffer.w < originalMap[0].size()){
        std::cout << "moveRight\n";
        for(int i=0; i < buffer.h; ++i){
            map[i].push_back(originalMap[i + buffer.y][buffer.x + buffer.w]);
            map[i].erase(map[i].begin());
        }
        buffer.x+=1;
    }
}

void ViewPort::moveMapY(int y){
    if(y < 0) {
        if(buffer.y - 1 >= 0){
            std::vector<int> row = std::vector<int>(originalMap[buffer.y - 1].begin() + buffer.x, originalMap[buffer.y - 1].begin() + buffer.x + buffer.w);
            map.insert(map.begin(), row);
            map.pop_back();
            buffer.y -= 1;
        }
    } else if(y > 0){
        if(buffer.y + buffer.h < originalMap.size()){
            std::vector<int> row = std::vector<int>(originalMap[buffer.y + 1].begin() + buffer.x, originalMap[buffer.y + 1].begin() + buffer.x + buffer.w);
            map.push_back(row);
            map.erase(map.begin());
            buffer.y += 1;
        }
    }
}


void ViewPort::move(Pair vec){
    Pair oldVal;
    oldVal.x = viewPort.x;
    oldVal.y = viewPort.y;
    this->viewPort.x += vec.x;
    this->viewPort.y += vec.y;
    std::cout << viewPort.x + viewPort.w * SIZE << " " << (buffer.x + buffer.w) * SIZE << "\n"; 
    if(this->viewPort.y + viewPort.h*SIZE > (buffer.y + buffer.h) * SIZE ) viewPort.y -= vec.y;
    if(viewPort.y < buffer.y * SIZE) viewPort.y -= vec.y;
    if(viewPort.x + viewPort.w * SIZE > (buffer.x + buffer.w) * SIZE) viewPort.x -= vec.x;
    if(viewPort.x < buffer.x * SIZE) viewPort.x -= vec.x;

    int left = this->viewPort.x / SIZE;
    int top = this->viewPort.y / SIZE;
    int right = (this->viewPort.x + this->viewPort.w * SIZE) / SIZE;
    int bottom = (this->viewPort.y + this->viewPort.h * SIZE) / SIZE;
    //std::cout << right << " " << this->buffer.x + this->buffer.w << "\n";
    std::cout << right <<  " " << this->buffer.x + this->buffer.w - 1 << "\n";
    if(viewPort.x != oldVal.x){
        if(left == this->buffer.x && vec.x < 0){
            this->moveMapX(-1);
        } else if(right >= this->buffer.x + this->buffer.w - 1 && vec.x > 0){
            this->moveMapX(1);   
        }
    } else if (viewPort.y != oldVal.y){
        if(top == this->buffer.y && vec.y < 0){
            this->moveMapY(-1);
        } else if(bottom == this->buffer.y + this->buffer.h - 1 && vec.y > 0){
            this->moveMapY(1);
        }
    }
}

Pair ViewPort::getOffset(){
    Pair offset;
    offset.x = buffer.x * SIZE - viewPort.x;
    offset.y = buffer.y * SIZE - viewPort.y;
    return offset; 
}


ViewPort::ViewPort(int centerX, int centerY, int viewWidth, int viewHeight, Matrix original):originalMap(original){
    buffer.w = (viewWidth + BUFFER_SIZE) * 2 + 1;
    buffer.h = (viewHeight + BUFFER_SIZE) * 2 + 1;
    viewPort.w = viewWidth * 2 + 1;
    viewPort.h = viewHeight * 2 + 1;

    buffer.x = centerX - viewWidth - BUFFER_SIZE;
    buffer.y = centerY - viewHeight - BUFFER_SIZE;
    
    const int mapWidth = originalMap[0].size();

    if(buffer.x + buffer.w > mapWidth) {
        int diff = mapWidth - (buffer.x + buffer.w);
        buffer.x += diff;
    }

    if(buffer.y + buffer.h > originalMap.size()){
        int diff = originalMap.size() - (buffer.y + buffer.h);
        buffer.y += diff;
    }
    
    if(buffer.x < 0) buffer.x = 0;
    if(buffer.y < 0) buffer.y = 0;



    viewPort.x = centerX - viewWidth;
    viewPort.y = centerY - viewHeight;
    if(viewPort.x < buffer.x) viewPort.x = buffer.x;
    if(viewPort.y < buffer.y) viewPort.y = buffer.y;

    int bufferRight = buffer.x + buffer.w;
    if(viewPort.x + viewPort.w > bufferRight){
        int diff = bufferRight - (viewPort.x + viewPort.w);
        viewPort.x += diff;
    }

    int bufferBottom = buffer.y + buffer.h; 
    if(viewPort.y + viewPort.h > bufferBottom){
        int diff = bufferBottom - (viewPort.y + viewPort.h);
        viewPort.y += diff;
    }
 

    for(int i=buffer.y; i < buffer.y + buffer.h; ++i){
        std::vector<int> row = std::vector<int>(this->originalMap[i].begin() + buffer.x, this->originalMap[i].begin() + buffer.x + buffer.w);
        this->map.push_back(row);
    }

    viewPort.x *= SIZE;
    viewPort.y *= SIZE;

}

ViewPort::~ViewPort(){

}

void ViewPort::print(){
    for(int i=0; i < map.size(); ++i){
        for(int j=0; j < map[i].size(); ++j){
            std::cout << map[i][j] << " ";
        }
        std::cout << "\n";
    }
}




int main(){
    SDL_Event event;
    const int SPEED = 8;
    Map m("map.txt");
    ViewPort v(29, 19, 3, 2, m.getMap());
    Window window("Window", SIZE * v.viewPort.w, SIZE * v.viewPort.h);

    while(window.isRunning()){
        Pair vec = {0, 0};
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT){
                window.close();
            } else
            if(event.type == SDL_KEYDOWN){
                switch(event.key.keysym.sym){
                    case SDLK_LEFT:
                        vec.x = -SPEED;
                        break;
                    case SDLK_RIGHT:
                        vec.x = SPEED;
                        break;
                    case SDLK_UP:
                        vec.y = -SPEED;
                        break;
                    case SDLK_DOWN:
                        vec.y = SPEED;
                        break;
                    default:
                        break;
                }
            }
        }
        v.move(vec);
        window.clear();
        drawMap(v.getMap(), window, v.getOffset().x, v.getOffset().y);
        window.present();
    }
    return 0;
}
