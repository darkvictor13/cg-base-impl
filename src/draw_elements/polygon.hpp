#pragma once

#include "draw_base_element.hpp"

namespace cg {
struct Edge {
        // pontos da aresta sempre ordenados pelo eixo y
        point_t p1, p2;

        Edge() : p1(), p2(){};
        Edge(const point_t &p1, const point_t &p2);
};

class Polygon : public DrawBaseElement {
    public:
        Polygon(const std::vector<point_t> &points,
                const wxColour &color = wxColour(255, 255, 255));
        ~Polygon();

    public:
        void draw(wxDC &dc) override;

    private:
        // estruturas aet e et para o algoritmo de preenchimento
};
};  // namespace cg