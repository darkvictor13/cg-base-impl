#include "line_cutter.hpp"

#include "debug.hpp"

using namespace cg;

LineCutter &LineCutter::getInstance() {
    static LineCutter instance;
    return instance;
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
        outcode_t &outcodeOut = using_outcode1 ? outcode1 : outcode2;
        const auto &[p1_x, p1_y] = p1;
        const auto &[p2_x, p2_y] = p2;
        if (outcodeOut.test(LEFT)) {
            temp_x = MIN_X;
            temp_y = p1_y + (p2_y - p1_y) * (temp_x - p1_x) / (p2_x - p1_x);
        } else if (outcodeOut.test(RIGHT)) {
            temp_x = MAX_X;
            temp_y = p1_y + (p2_y - p1_y) * (temp_x - p1_x) / (p2_x - p1_x);
        } else if (outcodeOut.test(BOTTOM)) {
            temp_y = MIN_Y;
            temp_x = p1_x + (p2_x - p1_x) * (temp_y - p1_y) / (p2_y - p1_y);
        } else if (outcodeOut.test(TOP)) {
            temp_y = MAX_Y;
            temp_x = p1_x + (p2_x - p1_x) * (temp_y - p1_y) / (p2_y - p1_y);
        }

        point_t &p_to_change = using_outcode1 ? p1 : p2;
        p_to_change = {temp_x, temp_y};
        outcodeOut = calculateOutcode(p_to_change);
    }

    if (accept) {
        std::cout << "Linha aceita\n" << p1 << " -> " << p2 << std::endl;
        std::cout << "Linha aceita\n";
    } else {
        std::cout << "Linha rejeitada\n";
    }

    return accept;
}

void LineCutter::setLimits(const point_t min, point_t max) {
    MIN_X = static_cast<uint16_t>(min.first);
    MIN_Y = static_cast<uint16_t>(min.second);
    MAX_X = static_cast<uint16_t>(max.first);
    MAX_Y = static_cast<uint16_t>(max.second);
}

LineCutter::~LineCutter() {
    DEBUG("LineCutter destructor");
}

LineCutter::LineCutter() : MAX_X(0), MIN_X(0), MAX_Y(0), MIN_Y(0) {
    DEBUG("LineCutter()");
}

outcode_t LineCutter::calculateOutcode(const float x, const float y) const {
    return ((y > MAX_Y) << TOP | (y < MIN_Y) << BOTTOM | (x > MAX_X) << RIGHT |
            (x < MIN_X) << LEFT);
}

outcode_t LineCutter::calculateOutcode(const point_t &p) const {
    return calculateOutcode(p.first, p.second);
}
