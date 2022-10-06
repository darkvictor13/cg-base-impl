#include "point.hpp"

#include <limits>
#include <sstream>

using namespace cg;

std::ostream &operator<<(std::ostream &os, const point_t &p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

cg::point_t parsePoint(const std::string &str) {
    if (str.empty() || str.size() < 3) {
        return {std::numeric_limits<float>::infinity(),
                std::numeric_limits<float>::infinity()};
    }
    std::stringstream ss(str);
    float x, y;

    if (str[0] == '(') {
        ss.ignore(1);
        ss >> x;
        if (ss.peek() == ',') {
            ss.ignore(1);
        }
        ss >> y;
        ss.ignore(1);
    } else {
        ss >> x;
        if (ss.peek() == ',') {
            ss.ignore(1);
        }
        ss >> y;
    }

    return {x, y};
}