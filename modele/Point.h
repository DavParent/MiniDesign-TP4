#pragma once
#include <string>
#include <vector>

class Point {
public:
    Point(int id_, int x_, int y_) : id(id_), x(x_), y(y_) {}
    int getId() const { return id; }
    int getY() const { return y; }
    int getX() const { return x; }

    void setPosition(int newX, int newY){
        x = newX;
        y = newY;
    }
    
private:
    int id;
    int x;
    int y;
};
