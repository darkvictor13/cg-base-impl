#include "line.hpp"

#include "debug.hpp"

using namespace cg;

void reta_pos(wxDC &dc, const int_point_t &x1, const int_point_t &y1, const int_point_t &x2, const int_point_t
&y2, int16_t dx, int16_t dy){

    int16_t incNE, incE, d;

    if(dx > dy){
        d = 2 * dy - dx;

        incE = 2 * dy;
        incNE = 2 * (dy - dx);

        dc.DrawPoint(x,y);

        while(x < x2){
            if(d <= 0){
                d += incE;
                x++;
            } else {
                d += incNE;
                x++;
                y++;
            }
            dc.DrawPoint(x,y);
        }
    } else{
        d = 2 * dx - dy;

        incE = 2 * dx;
        incNE = 2 * (dx - dy);

        dc.DrawPoint(x,y);

        while(y < y2){
            if(d <= 0){
                d += incE;
                y++;
            } else {
                d += incNE;
                x++;
                y++;
            }
            dc.DrawPoint(x,y);
        }
    }
}

void reta_neg(wxDC &dc, const int_point_t &x1, const int_point_t &y1, const int_point_t &x2, const int_point_t
&y2, int16_t dx, int16_t dy){

    int16_t incNE, incE, d;

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);

    x = x1;
    y = y1;

    if(dx > dy){
        d = 2 * dy - dx;

        incE = 2 * dy;
        incNE = 2 * (dy - dx);

        dc.DrawPoint(x,y);

        while(x > x2){
            if(d <= 0){
                d += incE;
                x--;
            } else {
                d += incNE;
                x--;
                y++;
            }
            dc.DrawPoint(x,y);
        }
    } else{
        d = 2 * dx - dy;

        incE = 2 * dx;
        incNE = 2 * (dx - dy);

        dc.DrawPoint(x,y);

        while(y < y2){
            if(d <= 0){
                d += incE;
                y++;
            } else {
                d += incNE;
                x--;
                y++;
            }
            dc.DrawPoint(x,y);
        }
    }
}

// Should be able to draw any line
// Precondition: p1 and p2 are in the same plane and p1 != p2 and p1 < p2
void writeLineBresenham(wxDC &dc, const point_t &initial,
                        const point_t &final) {
    int16_t dx, dy, incNE, incE, x, y, d;
    auto [x1, y1] = static_cast<int_point_t>(initial);
    auto [x2, y2] = static_cast<int_point_t>(final);

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);

    x = x1;
    y = y1;

    if(y2 > y1){
        reta_pos(dc, x1, y1, x2, y2, dx, dy);
    } else{
        reta_neg(dc, x1, y1, x2, y2, dx, dy);
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