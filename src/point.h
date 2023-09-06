#pragma once
#include <cstdint>

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
};