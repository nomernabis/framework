#include "Map.h"
#include <fstream>
#include <sstream>
#include <iostream>

Map::Map(std::string filename){
    this->readMap(filename);
}

Matrix Map::getMap(){
    return this->memory;
}

void Map::readMap(std::string filename){
    std::ifstream file(filename);
    std::string line;
    int i=0;
    while(std::getline(file, line)){
        std::istringstream iss(line);
        std::string token;
        this->memory.push_back(std::vector<int>());
        while(std::getline(iss, token, ' ')){
            this->memory[i].push_back(std::stoi(token));
        }
        ++i;
    }
} 


Matrix Map::getSubMap(int& centerRow, int& centerColumn, int size){
    Matrix m;
    int rowStart = centerRow - size / 2;
    if(rowStart < 0) rowStart = 0;
    if(rowStart + size >= this->memory.size()) rowStart -= (rowStart + size - (this->memory.size() - 1));
    int columnStart = centerColumn - size / 2;
    if(columnStart < 0) columnStart = 0;
    if(columnStart + size >= this->memory[0].size()) columnStart -= (columnStart + size - (this->memory.size() - 1));
    for(int i=rowStart; i < rowStart + size; ++i){
        m.push_back(std::vector<int>(this->memory[i].begin() + columnStart, this->memory[i].begin() + columnStart + size));
    }
    return m;
}

void Map::print(){
    for(int i=0; i < this->memory.size(); ++i){
        for(int j=0; j < this->memory[i].size(); ++j){
            std::cout << this->memory[i][j] << " ";
        }
        std::cout << "\n";
    }
}

Map::~Map(){

}
