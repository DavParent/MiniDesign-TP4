#pragma once
#include "NuageElement.h"
#include <string>
#include <vector>

class Point : public NuageElement {
public:
    Point(int id, int x, int y) : NuageElement(id), x(x), y(y) {}
    
    int getY() const { return y; }
    int getX() const { return x; }

    void setPosition(int newX, int newY){
        x = newX;
        y = newY;
    }
    
private:
    int x;
    int y;
};

