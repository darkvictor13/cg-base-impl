#include "rectangle.hpp"

using namespace cg;

Rectangle::Rectangle(const point_t &begin, const point_t &end,
                     const wxColour &color)
    : DrawBaseElement(color) {
    points.reserve(2);
    points.push_back(begin);
    points.push_back(end);
}

Rectangle::~Rectangle() {
}

void Rectangle::draw(wxDC &dc) {
    dc.SetPen(wxPen(color));
    auto [x1, y1] = points[0];
    auto [x2, y2] = points[1];
    auto width = x2 - x1;
    auto height = y2 - y1;
    dc.DrawLine(x1, y1, x1 + width, y1);
    dc.DrawLine(x1, y1, x1, y1 + height);
    dc.DrawLine(x1 + width, y1, x1 + width, y1 + height);
    dc.DrawLine(x1, y1 + height, x1 + width, y1 + height);
}
