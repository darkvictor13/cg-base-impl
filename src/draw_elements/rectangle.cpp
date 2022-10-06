#include "rectangle.hpp"

using namespace cg;

Rectangle::Rectangle(const point_t &begin, const int width, const int height)
    : DrawBaseElement() {
    color = wxColour(0, 0, 0);
    points.reserve(1);
    points.push_back(begin);
    this->width = width;
    this->height = height;
}

Rectangle::~Rectangle() {
}

void Rectangle::draw(wxDC &dc) {
    dc.SetPen(wxPen(color));
    dc.DrawRectangle(points[0].first, points[0].second, width, height);
}
