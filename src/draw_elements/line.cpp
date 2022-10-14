#include "line.hpp"

#include "debug.hpp"

using namespace cg;

void bresenham_base(wxDC &dc, uint16_t x1, uint16_t y1, uint16_t x2,
                    uint16_t y2, uint16_t dx, uint16_t dy) {
    int d = 2 * dy - dx;
    for (int i = 0; i <= dx; i++) {
        dc.DrawPoint(x1, y1);
        x1 < x2 ? x1++ : x1--;
        if (d < 0) {
            d += (2 * dy);
        } else {
            y1 < y2 ? y1++ : y1--;
            d += (2 * dy - 2 * dx);
        }
    }
}

// Should be able to draw any line
// Precondition: p1 and p2 are in the same plane and p1 != p2 and p1 < p2
void writeLineBresenham(wxDC &dc, const point_t &initial,
                        const point_t &final) {
    const auto [x1, y1] = static_cast<int_point_t>(initial);
    const auto [x2, y2] = static_cast<int_point_t>(final);

    const int16_t dx = abs(x2 - x1);
    const int16_t dy = abs(y2 - y1);

    if (dx > dy) {
        bresenham_base(dc, x1, y1, x2, y2, dx, dy);
    } else {
        bresenham_base(dc, y1, x1, y2, x2, dy, dx);
    }
}

Line::Line(const point_t &p1, const point_t &p2, const wxColour &color)
    : DrawBaseElement(color) {
    points.reserve(2);
    if (p1 < p2) {
        points.push_back(p1);
        points.push_back(p2);
    } else {
        points.push_back(p2);
        points.push_back(p1);
    }
}

Line::~Line() {
}

void Line::draw(wxDC &dc) {
    dc.SetPen(wxPen(color));
    if (points[0].first == points[1].first) {
        DEBUG("Vertical line");
        auto [x, y1] = static_cast<int_point_t>(points[0]);
        auto [_, y2] = static_cast<int_point_t>(points[1]);

        for (uint16_t y = y1; y <= y2; y++) {
            dc.DrawPoint(x, y);
        }
    } else if (points[0].second == points[1].second) {
        DEBUG("Horizontal line");
        auto [x1, y] = static_cast<int_point_t>(points[0]);
        auto [x2, _] = static_cast<int_point_t>(points[1]);

        for (uint16_t x = x1; x <= x2; x++) {
            dc.DrawPoint(x, y);
        }
    } else {
        // TODO tratar retas tais como: (100, 0) -> (0, 100)
        DEBUG("Bresenham line" << points[0] << points[1]);
        writeLineBresenham(dc, points[0], points[1]);
    }
}