#include <party_gfx.h>

using namespace PartyGFX;

class ScreenBuffer {
public:
    Rect coords;
    size_t bytes_per_pixel;
    uint8_t* buffer;

    ScreenBuffer(Rect coords, size_t bytes_per_pixel, uint8_t color = 0x00) {
        this->coords = coords;
        this->bytes_per_pixel = bytes_per_pixel;
        this->buffer = new uint8_t[coords.width() * coords.height() * bytes_per_pixel];
        clear(color);
    }

    ~ScreenBuffer() {
        delete[] this->buffer;
    }

    size_t byte_size() {
        return this->coords.width() * this->coords.height() * this->bytes_per_pixel;
    }

    void clear(uint8_t color) {
        for(size_t i = 0; i < byte_size(); i++) {
            this->buffer[i] = color;
        }
    }

    uint16_t get_pixel(size_t x, size_t y) {
        size_t buffer_offset = y * this->coords.width() + x;
        uint16_t* buffer = (uint16_t*)this->buffer;
        return buffer[buffer_offset];
    }

    operator ScreenSpan() {
        return ScreenSpan(this->coords, this->buffer, byte_size(), this->bytes_per_pixel);
    }

    bool color_at_points(Color fg, std::initializer_list<Point> points) {
        for(auto point : points) {
            if(get_pixel(point.x, point.y) != fg) {
                return false;
            }
        }
        return true;
    }

    bool color_except_points(Color bg, std::initializer_list<Point> points) {
        for(size_t y = 0; y < this->coords.height(); y++) {
            for(size_t x = 0; x < this->coords.width(); x++) {
                if(get_pixel(x, y) != bg) {
                    if(std::find(points.begin(), points.end(), Point(x, y)) == points.end()) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    bool check_for_points(Color fg, Color bg, std::initializer_list<Point> points) {
        if(!color_at_points(fg, points)) {
            return false;
        }
        if(!color_except_points(bg, points)) {
            return false;
        }
        return true;
    }
};

bool basic_test() {
    Elements elements;
    Color black(0, 0, 0);
    Color white(255, 255, 255);

    // test for one pixel
    auto pixel = std::make_shared<Pixel>(Point(0, 0), white);
    elements.add_element(pixel);

    {
        ScreenBuffer screen_buffer({{0, 0}, {15, 15}}, 2);
        ScreenSpan screen(screen_buffer);
        elements.render(screen);
        if(!screen_buffer.check_for_points(white, black, {{0, 0}})) {
            return false;
        }
    }

    // test for removing the pixel
    elements.remove_element(pixel);
    {
        ScreenBuffer screen_buffer({{0, 0}, {15, 15}}, 2);
        ScreenSpan screen(screen_buffer);
        elements.render(screen);
        if(!screen_buffer.check_for_points(white, black, {})) {
            return false;
        }
    }

    // test for returning the pixel
    elements.add_element(pixel);
    {
        ScreenBuffer screen_buffer({{0, 0}, {15, 15}}, 2);
        ScreenSpan screen(screen_buffer);
        elements.render(screen);
        if(!screen_buffer.check_for_points(white, black, {{0, 0}})) {
            return false;
        }
    }

    // test for two pixels
    elements.add_element(std::make_shared<Pixel>(Point(0, 1), white));
    {
        ScreenBuffer screen_buffer({{0, 0}, {15, 15}}, 2);
        ScreenSpan screen(screen_buffer);
        elements.render(screen);
        if(!screen_buffer.check_for_points(white, black, {{0, 0}, {0, 1}})) {
            return false;
        }
    }

    return true;
}

int main() {
    std::vector<bool (*)()> tests = {
        basic_test,
    };

    bool all_passed = true;

    for(auto test : tests) {
        bool passed = test();
        all_passed = all_passed && passed;
    }

    return all_passed ? 0 : 1;
}