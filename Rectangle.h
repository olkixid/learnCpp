#ifndef LEARNCPP_RECTANGLE_H
#define LEARNCPP_RECTANGLE_H


struct SDL_Rect;

class Rectangle {
public:
    Rectangle(double x, double y, double w, double h) : mx{x}, my{y}, mw{w}, mh{h} {}
    Rectangle() = default;
    explicit Rectangle(SDL_Rect* sdlRect);
    bool intersects(const Rectangle& r2) const;
    double x() const { return mx; }
    double y() const { return my; }
    double w() const { return mw; }
    double h() const { return mh; }
    void set_x(double x) { this->mx = x; }
    void set_y(double y) { this->my = y; }
    void set_w(double w) { this->mw = w; }
    void set_h(double h) { this->mh = h; }
private:
    double mx{0.0};
    double my{0.0};
    double mw{0.0};
    double mh{0.0};
};


#endif //LEARNCPP_RECTANGLE_H
