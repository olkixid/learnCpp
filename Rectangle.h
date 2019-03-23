#ifndef LEARNCPP_RECTANGLE_H
#define LEARNCPP_RECTANGLE_H

#include "RenderWindow.h"

class Rectangle {
public:
    bool intersects(Rectangle& r2) const;
    void draw_to(RenderWindow& targetRenderer) const;

    double x;
    double y;
    double w;
    double h;
};


#endif //LEARNCPP_RECTANGLE_H
