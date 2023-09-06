#pragma once
#include <cstdint>
#include <cstddef>
#include "rect.h"
#include "color.h"

namespace PartyGFX {
class ScreenSpan {
public:
    Rect coords;
    uint8_t* buffer;

    ScreenSpan(Rect coords, uint8_t* buffer, size_t buffer_size, size_t bytes_per_pixel);
    void set_pixel(Point point, Color color);
};

};