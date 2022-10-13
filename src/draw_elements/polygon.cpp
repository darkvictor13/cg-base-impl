#include "polygon.hpp"

#include "debug.hpp"

using namespace cg;

Polygon::Polygon(const std::vector<point_t> &points, const wxColour &color)
    : DrawBaseElement(color), aet(), et() {
    DEBUG("Copiando pontos");
    this->points = points;
    uint16_t y_max_global = static_cast<uint16_t>(
        std::max_element(points.begin(), points.end(),
                         [](const point_t &a, const point_t &b) {
                             return a.second < b.second;
                         })
            ->second);
    DEBUG("Achando y_max_global = " << y_max_global);
    et.reserve(y_max_global);
    DEBUG("Criando lista de arestas");
    for (size_t i = 1; i < points.size(); i++) {
        DEBUG("Iteração " << i);
        auto [x1, y1] = static_cast<int_point_t>(points[i - 1]);
        auto [x2, y2] = static_cast<int_point_t>(points[i]);

        const point_t &p_y_min = (y1 < y2) ? points[i - 1] : points[i];

        DEBUG("Criando aresta no y_min: " << p_y_min.second);
        et[p_y_min.second].push_back(
            {std::max(y1, y2), static_cast<int>(p_y_min.first),
             static_cast<double>(x2 - x1) / static_cast<double>(y2 - y1)});
        DEBUG("Aresta criada: " << et[p_y_min.second].back());
    }
    DEBUG("Ordenando lista de arestas");
    for (auto &it : et) {
        std::sort(it.begin(), it.end(), [](const Edge &a, const Edge &b) {
            return a.x < b.x;
        });
    }

    DEBUG("Mostrando lista de arestas:");
    for (const auto &it : et) {
        DEBUG("um elemento do vetor:");
        for (const auto &it2 : it) {
            DEBUG(it2);
        }
        DEBUG('\n');
    }
}

Polygon::~Polygon() {
}

void Polygon::draw(wxDC &dc) {
    /*
    fill the polygon
    */
    dc.SetPen(wxPen(color));

    size_t y = 0;
    while (aet.size() > 0 && et.size() > 0 && y < et.size()) {
        // caso não tenha nenhum bucket nessa posição de et continua
        if (et[y].size() == 0) {
            y++;
            continue;
        }
        // Transfere do bucket y de ET para AET as arestas cujo ymin = y,
        // mantendo a AET ordenada em x,
        for (auto &edge : et[y]) {
            aet.push_back(edge);
        }
        std::sort(aet.begin(), aet.end(), [](const Edge &a, const Edge &b) {
            return a.x < b.x;
        });

        // Retira os lados que possuem y = ymax (Comentario da prof)
        // Nao sei se é para retirar por x
        aet.erase(std::remove_if(aet.begin(), aet.end(),
                                 [](const Edge &edge) {
                                     return edge.y_max == edge.x;
                                 }),
                  aet.end());

        // Desenhe os pixels do bloco na linha de varredura y usando pares de
        // coordenadas x da AET.
        for (size_t i = 0; i < aet.size(); i += 2) {
            dc.DrawLine(aet[i].x, aet[i].y_max, aet[i + 1].x, aet[i + 1].y_max);
        }

        // Incremente y de 1
        y++;

        // Para cada aresta não vertical que permanece na AET, atualiza x para
        // o novo y
        for (auto &edge : aet) {
            // se for vertical, não vai acontecer nada pois o x não vai mudar
            edge.x += edge.inc;
        }

        // reordena a AET
        std::sort(aet.begin(), aet.end(), [](const Edge &a, const Edge &b) {
            return a.x < b.x;
        });
    }
}

/*void AET::AET(){
    ymax = 0;
    x = 0;
    inc = 0;
}

void ET::ET(){
    p = 0;
}

AET *novoAET(const point_t &p1, const point_t &p2, ET* listPolygon){

    AET *novo = (AET*)malloc(sizeof(AET));

    //usar o algoritmo de Bresenham
    auto [x1, y1] = static_cast<int_point_t>(p1);
    auto [x2, y2] = static_cast<int_point_t>(p2);

    if(y1 > y2){
        novo->ymax = y1;
        novo->x = x2;
    } else{
        novo->ymax = y2;
        novo->x = x1;
    }

    novo->prox = NULL;
    insere(novo, listPolygon);

    return novo;

}

ET *insere (AET* aresta, ET* listPolygon){
        listPolygon.insert(aresta, aresta->x);
        //ordenar por x
        //ordenar com Edge
}

ET *remove (ET* listPolygon, AET* aresta){
    if(!empty(listPolygon)){
        listPolygon.remove(aresta);
        //ordenar com Edge
    }
}
*/
