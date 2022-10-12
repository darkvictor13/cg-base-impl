#include "circle.hpp"

using namespace cg;

void drawCirclePoints(wxDC &dc, int16_t x, int16_t y,
                      const int_point_t &center) {
    auto [cx, cy] = center;

    dc.DrawPoint(cx + x, cy + y);
    dc.DrawPoint(cx - x, cy + y);
    dc.DrawPoint(cx + x, cy - y);
    dc.DrawPoint(cx - x, cy - y);

    dc.DrawPoint(cx + y, cy + x);
    dc.DrawPoint(cx - y, cy + x);
    dc.DrawPoint(cx + y, cy - x);
    dc.DrawPoint(cx - y, cy - x);
}

Circle::Circle(const point_t &center, const float radius, const wxColour &color)
    : DrawBaseElement(color), radius(radius) {
    points.reserve(1);
    points.push_back(center);
}

Circle::~Circle() {
}

void Circle::draw(wxDC &dc) {
    int16_t x = 0;
    int16_t y = radius;
    float h = 1 - radius;
    auto center = static_cast<int_point_t>(points[0]);

    dc.SetPen(wxPen(color));
    drawCirclePoints(dc, x, y, center);
    while (y > x) {
        if (h < 0) {
            h += 2 * x + 3;
        } else {
            h += 2 * (x - y) + 5;
            // Na tela o y cresce para baixo
            y--;
        }
        x++;
        drawCirclePoints(dc, x, y, center);
    }
}
