#pragma once

#include "draw_base_element.hpp"

namespace cg {
class Circle : public DrawBaseElement {
    public:
        Circle(const point_t &center, const float radius);
        ~Circle();

    public:
        void draw(wxDC &dc) override;

    private:
        float radius;
};
};  // namespace cg