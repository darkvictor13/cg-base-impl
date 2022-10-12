#include "polygon.hpp"

using namespace cg;

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
    delete[] wx_points;
}
