#pragma once

#include "draw_base_element.hpp"
#include "line.hpp"

namespace cg {
class Rectangle : public DrawBaseElement {
    public:
        Rectangle(const point_t &begin, const point_t &end,
                  const wxColour &color = wxColour(0, 0, 0));
        ~Rectangle();

    public:
        void draw(wxDC &dc) override;
};
};  // namespace cg