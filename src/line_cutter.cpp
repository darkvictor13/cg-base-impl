#include "line_cutter.hpp"
#include "debug.hpp"

using namespace cg;

std::ostream &operator<<(std::ostream &os, const point_t &p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

LineCutter::LineCutter() : MAX_X(0), MIN_X(0), MAX_Y(0), MIN_Y(0) {
    DEBUG("LineCutter()");
}

LineCutter::LineCutter(uint16_t max_x, uint16_t min_x, uint16_t max_y,
                       uint16_t min_y)
    : MAX_X(max_x), MIN_X(min_x), MAX_Y(max_y), MIN_Y(min_y) {
    DEBUG("LineCutter(uint16_t, uint16_t, uint16_t, uint16_t)");
}

bool LineCutter::cohenSutherland(point_t &p1, point_t &p2) {
    float temp_x = 0, temp_y = 0;
    bool accept = false;
    bool done = false;
    outcode_t outcode1 = calculateOutcode(p1);
    outcode_t outcode2 = calculateOutcode(p2);

    while (!done) {
        TRACE(p1);
        TRACE(p2);

        // trivialmente aceito
        if (outcode1.none() && outcode2.none()) {
            accept = true;
            done = true;
            break;
        }
        // trivialmente rejeitado
        if ((outcode1 & outcode2).any()) {
            done = true;
            break;
        }

        const bool using_outcode1 = outcode1.any();
        outcode_t &outcodeOut = using_outcode1? outcode1 : outcode2;
        const auto &[p1_x, p1_y] = p1;
        const auto &[p2_x, p2_y] = p2;
        if (outcodeOut.test(LEFT)) {
            temp_x = MIN_X;
            temp_y = p1_y + (p2_y - p1_y) * (temp_x - p1_x) / (p2_x - p1_x);
        }else if (outcodeOut.test(RIGHT)) {
            temp_x = MAX_X;
            temp_y = p1_y + (p2_y - p1_y) * (temp_x - p1_x) / (p2_x - p1_x);
        }else if (outcodeOut.test(BOTTOM)) {
            temp_y = MIN_Y;
            temp_x = p1_x + (p2_x - p1_x) * (temp_y - p1_y) / (p2_y - p1_y);
        }else if (outcodeOut.test(TOP)) {
            temp_y = MAX_Y;
            temp_x = p1_x + (p2_x - p1_x) * (temp_y - p1_y) / (p2_y - p1_y);
        }

        point_t &p_to_change = using_outcode1? p1 : p2;
        p_to_change = {temp_x, temp_y};
        outcodeOut = calculateOutcode(p_to_change);
    }

    if (accept) {
        std::cout << "Linha aceita\n" << p1 << " -> " << p2 << std::endl;
        std::cout << "Linha aceita\n";
    }else {
        std::cout << "Linha rejeitada\n";
    }

    return accept;
}

LineCutter::~LineCutter() {
    DEBUG("LineCutter destructor");
}

outcode_t LineCutter::calculateOutcode(const float x, const float y) const {
    return ((y > MAX_Y) << TOP | (y < MIN_Y) << BOTTOM | (x > MAX_X) << RIGHT |
            (x < MIN_X) << LEFT);
}

outcode_t LineCutter::calculateOutcode(const point_t &p) const {
    return calculateOutcode(p.first, p.second);
}
