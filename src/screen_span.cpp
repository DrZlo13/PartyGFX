#include "screen_span.h"
#include <cassert>

using namespace PartyGFX;

ScreenSpan::ScreenSpan(Rect coords, uint8_t* buffer, size_t buffer_size, size_t bytes_per_pixel) {
    assert(buffer_size >= coords.width() * coords.height() * bytes_per_pixel);
    assert(bytes_per_pixel == 2);
    this->coords = coords;
    this->buffer = buffer;
}

void ScreenSpan::set_pixel(Point point, Color color) {
    size_t buffer_x = point.x - this->coords.top_left.x;
    size_t buffer_y = point.y - this->coords.top_left.y;
    size_t buffer_offset = buffer_y * this->coords.width() + buffer_x;
    uint16_t* buffer = (uint16_t*)this->buffer;
    buffer[buffer_offset] = color;
}