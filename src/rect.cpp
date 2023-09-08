#include "rect.h"
#include <cassert>

using namespace PartyGFX;

Rect::Rect(Point top_left, Point bottom_right) {
    assert(top_left.x <= bottom_right.x);
    assert(top_left.y <= bottom_right.y);
    this->top_left = top_left;
    this->bottom_right = bottom_right;
}

Rect::Rect() {
    this->top_left = Point();
    this->bottom_right = Point();
}

Rect::~Rect() {
}

Coord Rect::width() {
    return this->bottom_right.x - this->top_left.x;
}

Coord Rect::height() {
    return this->bottom_right.y - this->top_left.y;
}

bool Rect::contains(Point point) {
    return point.x >= this->top_left.x && point.x < this->bottom_right.x &&
           point.y >= this->top_left.y && point.y < this->bottom_right.y;
}