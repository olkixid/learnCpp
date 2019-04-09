#ifndef LEARNCPP_RECTANGLE_H
#define LEARNCPP_RECTANGLE_H


#include <SDL_rect.h>

class Rectangle {
public:
    Rectangle(double x, double y, double w, double h) : x{x}, y{y}, w{w}, h{h} {}
    Rectangle() = default;
    explicit Rectangle(SDL_Rect* sdlRect);
    bool intersects(Rectangle& r2) const;

    double x{0.0};
    double y{0.0};
    double w{0.0};
    double h{0.0};
};


#endif //LEARNCPP_RECTANGLE_H
