#include "party_gfx.h"
#include <cassert>

using namespace PartyGFX;

Point::Point(Coord x, Coord y) {
    this->x = x;
    this->y = y;
}

Point::Point() {
    this->x = 0;
    this->y = 0;
}

Point::~Point() {
}

bool PartyGFX::Point::operator==(const Point& other) const {
    return this->x == other.x && this->y == other.y;
}

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
    return point.x >= this->top_left.x && point.x <= this->bottom_right.x &&
           point.y >= this->top_left.y && point.y <= this->bottom_right.y;
}

Screen::Screen(Rect coords, uint8_t* buffer, size_t buffer_size, size_t bytes_per_pixel) {
    assert(buffer_size >= coords.width() * coords.height() * bytes_per_pixel);
    assert(bytes_per_pixel == 2);
    this->coords = coords;
    this->buffer = buffer;
}

void Screen::set_pixel(Point point, Color color) {
    size_t buffer_x = point.x - this->coords.top_left.x;
    size_t buffer_y = point.y - this->coords.top_left.y;
    size_t buffer_offset = buffer_y * this->coords.width() + buffer_x;
    uint16_t* buffer = (uint16_t*)this->buffer;
    buffer[buffer_offset] = color;
}

Color::Color() {
    this->r = 0;
    this->g = 0;
    this->b = 0;
}

Color::Color(uint8_t r, uint8_t g, uint8_t b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

Color::operator uint16_t() {
    return (this->r & 0b11111000) << 8 | (this->g & 0b11111100) << 3 | (this->b & 0b11111000) >> 3;
}

Renderer::Renderer() {
}

Renderer::~Renderer() {
}

void Renderer::add_element(std::shared_ptr<Element> element) {
    this->elements.push_back(element);
}

void Renderer::remove_element(std::shared_ptr<Element> element) {
    for(auto it = this->elements.begin(); it != this->elements.end(); it++) {
        if(it->get() == element.get()) {
            this->elements.erase(it);
            return;
        }
    }
}

void Renderer::render(Screen& screen) {
    for(auto it = this->elements.begin(); it != this->elements.end(); it++) {
        it->get()->render(screen);
    }
}

Pixel::Pixel(Point point, Color color) {
    this->point = point;
    this->color = color;
}

Pixel::~Pixel() {
}

void Pixel::render(Screen& screen) {
    if(screen.coords.contains(this->point)) {
        screen.set_pixel(this->point, this->color);
    }
}
