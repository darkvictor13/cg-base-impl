#pragma once

#include <enum.hpp>
#include <point.hpp>
#include <vector>

namespace cg {
struct Config {
    public:
        cg::DrawOptions draw_option;
        std::vector<cg::point_t> points;
        union {
                float radius;
                uint8_t color;
        };
        bool is_cutter_visible;

    public:
        Config()
            : draw_option(cg::DrawOptions::DRAW_CLEAR),
              points(),
              radius(0),
              is_cutter_visible(false) {
        }
        ~Config() {
        }
};
};  // namespace cg