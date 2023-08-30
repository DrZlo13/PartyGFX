#pragma once
#include <cstdint>
#include <cstddef>
#include <vector>
#include <memory>

namespace PartyGFX {
typedef int32_t Coord;

class Point {
public:
    Coord x;
    Coord y;
    Point(Coord x, Coord y);
    Point();
    ~Point();

    bool operator==(const Point& other) const;
};

class Rect {
public:
    Point top_left;
    Point bottom_right;
    Rect(Point top_left, Point bottom_right);
    Rect();
    ~Rect();

    Coord width();
    Coord height();
    bool contains(Point point);
};

class Color {
private:
    uint8_t r;
    uint8_t g;
    uint8_t b;

public:
    Color();
    Color(uint8_t r, uint8_t g, uint8_t b);
    operator uint16_t();
};

class Screen {
public:
    Rect coords;
    uint8_t* buffer;

    Screen(Rect coords, uint8_t* buffer, size_t buffer_size, size_t bytes_per_pixel);
    void set_pixel(Point point, Color color);
};

class Element {
public:
    virtual void render(Screen& screen) = 0;
    virtual ~Element(){};
};

class Renderer {
private:
    std::vector<std::shared_ptr<Element> > elements;

public:
    Renderer();
    ~Renderer();

    void add_element(std::shared_ptr<Element> element);
    void remove_element(std::shared_ptr<Element> element);
    void render(Screen& screen);
};

class Pixel : public Element {
private:
    Point point;
    Color color;

public:
    Pixel(Point point, Color color);
    ~Pixel();

    void render(Screen& screen);
};

}