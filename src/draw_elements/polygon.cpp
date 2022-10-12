#include "polygon.hpp"

using namespace cg;

Edge::Edge(const point_t &p1, const point_t &p2) {
    if (p1.second < p2.second) {
        this->p1 = p1;
        this->p2 = p2;
    } else {
        this->p1 = p2;
        this->p2 = p1;
    }
}

Polygon::Polygon(const std::vector<point_t> &points, const wxColour &color)
    : DrawBaseElement(color) {
    this->points = points;
}

Polygon::~Polygon() {
}

void Polygon::draw(wxDC &dc) {
    dc.SetPen(wxPen(color));
    const int size = points.size();
    wxPoint *wx_points = new wxPoint[size];
    for (int i = 0; i < size; i++) {
        wx_points[i] = wxPoint(points[i].first, points[i].second);
    }
    dc.DrawPolygon(size, wx_points);
}
