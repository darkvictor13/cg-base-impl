#pragma once

#include "draw_base_element.hpp"

namespace cg {
class Polygon : public DrawBaseElement {
    public:
        Polygon(const std::vector<point_t> &points,
                const wxColour &color = wxColour(255, 255, 255));
        ~Polygon();

    public:
        void draw(wxDC &dc) override;
};
};  // namespace cg