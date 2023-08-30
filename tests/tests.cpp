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

    operator Screen() {
        return Screen(this->coords, this->buffer, byte_size(), this->bytes_per_pixel);
    }

    bool color_at_points(Color color, std::initializer_list<Point> points) {
        for(auto point : points) {
            if(get_pixel(point.x, point.y) != color) {
                return false;
            }
        }
        return true;
    }

    bool color_except_points(Color color, std::initializer_list<Point> points) {
        for(size_t y = 0; y < this->coords.height(); y++) {
            for(size_t x = 0; x < this->coords.width(); x++) {
                if(get_pixel(x, y) != color) {
                    if(std::find(points.begin(), points.end(), Point(x, y)) == points.end()) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
};

bool basic_test() {
    Renderer renderer;
    Color black(0, 0, 0);
    Color white(255, 255, 255);

    // test for one pixel
    auto pixel = std::make_shared<Pixel>(Point(0, 0), white);
    renderer.add_element(pixel);

    {
        ScreenBuffer screen_buffer({{0, 0}, {15, 15}}, 2);
        Screen screen(screen_buffer);
        renderer.render(screen);
        if(!screen_buffer.color_at_points(white, {{0, 0}})) {
            return false;
        }
        if(!screen_buffer.color_except_points(black, {{0, 0}})) {
            return false;
        }
    }

    // test for removing the pixel
    renderer.remove_element(pixel);
    {
        ScreenBuffer screen_buffer({{0, 0}, {15, 15}}, 2);
        Screen screen(screen_buffer);
        renderer.render(screen);
        if(!screen_buffer.color_except_points(black, {})) {
            return false;
        }
    }

    // test for returning the pixel
    renderer.add_element(pixel);
    {
        ScreenBuffer screen_buffer({{0, 0}, {15, 15}}, 2);
        Screen screen(screen_buffer);
        renderer.render(screen);
        if(!screen_buffer.color_at_points(white, {{0, 0}})) {
            return false;
        }
        if(!screen_buffer.color_except_points(black, {{0, 0}})) {
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