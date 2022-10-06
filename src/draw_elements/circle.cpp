#include "circle.hpp"

using namespace cg;

Circle::Circle(const point_t &center, const float radius)
    : DrawBaseElement(), radius(radius) {
    points.reserve(1);
    points.push_back(center);
}

Circle::~Circle() {
}

void Circle::draw(wxDC &dc) {
    dc.SetPen(wxPen(color));
    dc.DrawCircle(points[0].first, points[0].second, radius);
}
