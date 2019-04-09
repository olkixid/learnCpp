#ifndef LEARNCPP_RECTANGLE_H
#define LEARNCPP_RECTANGLE_H

class Rectangle {
public:
    bool intersects(Rectangle& r2) const;

    double x;
    double y;
    double w;
    double h;
};


#endif //LEARNCPP_RECTANGLE_H
