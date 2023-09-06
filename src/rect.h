#pragma once
#include <cstdint>
#include "point.h"

namespace PartyGFX {
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
};