#include "Rectangle.h"


bool Rectangle::intersects(Rectangle& r2) const {
    if(r2.x >= x + w || x >= r2.x + r2.w || r2.y >= y + h || y >= r2.y + r2.h) {
        return false;
    }
    return true;
}