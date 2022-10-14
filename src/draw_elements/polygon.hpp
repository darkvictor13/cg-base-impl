#pragma once

#include "draw_base_element.hpp"

namespace cg {

struct Edge {
        int y_max, x;
        double inc;

        Edge(int y_max, int x, double inc) : y_max(y_max), x(x), inc(inc) {
        }
        friend std::ostream &operator<<(std::ostream &os, const Edge &edge) {
            os << "ymax: " << edge.y_max << " x: " << edge.x
               << " inc: " << edge.inc;
            return os;
        }
};

class Polygon : public DrawBaseElement {
    public:
        Polygon(const std::vector<point_t> &points,
                const wxColour &color = wxColour(255, 255, 255));
        ~Polygon();

    public:
        void draw(wxDC &dc) override;
        void criaLista();

    private:
        void insertEdge(const point_t &p1, const point_t &p2);
        //  estruturas aet e et para o algoritmo de preenchimento

        // usar Bresenham para desenhar cada reta
        //  lista de arestas AET
        std::vector<Edge> aet;
        // et
        std::vector<std::vector<Edge>> et;

        /*
        typedef struct listaAET AET;

        struct listaAET
        {
            int16_t ymax;
            int16_t x;
            int16_t inc;
            AET* prox;
        };

        typedef struct listaET ET;

        struct listaET
        {
            AET* aresta;
            int16_t p; //posição
        };
        */
};
};  // namespace cg