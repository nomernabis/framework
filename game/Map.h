#pragma once
#include<vector>
#include<string>

using Matrix = std::vector<std::vector<int>>;
class Map{
    void readMap(std::string filename);
    Matrix memory;
    public:
    Map(std::string filename);
    ~Map();
    Matrix getSubMap(int& centerRow, int& centerColumn, int size);
    void print();
    Matrix getMap();
};
