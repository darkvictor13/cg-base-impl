#pragma once

#include "draw_base_element.hpp"

namespace cg {
class Line : public DrawBaseElement {
    public:
        Line(const point_t &p1, const point_t &p2);
        ~Line();

    public:
        void draw(wxDC &dc) override;
};
};  // namespace cg