#include "line.hpp"

using namespace cg;

Line::Line(const point_t &p1, const point_t &p2) : DrawBaseElement() {
    color = wxColour(0, 0, 0);
    points.reserve(2);
    points.push_back(p1);
    points.push_back(p2);
}

Line::~Line() {
}

void Line::draw(wxDC &dc) {
    dc.SetPen(wxPen(color));
    dc.DrawLine(points[0].first, points[0].second, points[1].first,
                points[1].second);
}
