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
        void criaLista();

    private:
        // estruturas aet e et para o algoritmo de preenchimento

        //usar Bresenham para desenhar cada reta

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

};
};  // namespace cg