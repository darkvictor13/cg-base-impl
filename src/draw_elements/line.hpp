#pragma once

#include "draw_base_element.hpp"

namespace cg {
class Line : public DrawBaseElement {
    public:
        Line(const point_t &p1, const point_t &p2,
             const wxColour &color = wxColour(255, 255, 255));
        ~Line();

    public:
        void draw(wxDC &dc) override;
        void writeLineBresenham(wxDC &dc, const point_t &initial, const point_t &final);
        void reta_pos(wxDC &dc, int_point_t &x1, int_point_t &y1, int_point_t &x2, int_point_t &y2, int16_t dx, int16_t dy);
        void reta_neg(wxDC &dc, int_point_t &x1, int_point_t &y1, int_point_t &x2, int_point_t &y2, int16_t dx, int16_t dy);

};
};  // namespace cg