#pragma once

#include <ostream>
#include <utility>

namespace cg {
typedef std::pair<float, float> point_t;
typedef std::pair<int16_t, int16_t> int_point_t;
};  // namespace cg

std::ostream &operator<<(std::ostream &os, const cg::point_t &p);
cg::point_t parsePoint(const std::string &str);