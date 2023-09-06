#include "point.h"

using namespace PartyGFX;

Point::Point(Coord coord_x, Coord coord_y) {
    x = coord_x;
    y = coord_y;
}

Point::Point() {
    x = 0;
    y = 0;
}

Point::~Point() {
}

bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
}