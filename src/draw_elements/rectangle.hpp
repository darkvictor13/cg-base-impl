#pragma once

#include "draw_base_element.hpp"

namespace cg {
class Rectangle : public DrawBaseElement {
    public:
        Rectangle(const point_t &begin, const int width, const int height);
        ~Rectangle();

    public:
        void draw(wxDC &dc) override;

    private:
        int width;
        int height;
};
};  // namespace cg