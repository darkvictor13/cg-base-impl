#include "polygon.hpp"

using namespace cg;

Polygon::Polygon(const std::vector<point_t> &points, const wxColour &color)
    : DrawBaseElement(color), aet(), et() {
    this->points = points;
    uint16_t y_max_global = static_cast<uint16_t>(
        std::max_element(points.begin(), points.end(),
                         [](const point_t &a, const point_t &b) {
                             return a.second < b.second;
                         })
            ->second);
    et.reserve(y_max_global);
    for (size_t i = 1; i < points.size(); i++) {
        auto [x1, y1] = static_cast<int_point_t>(points[i - 1]);
        auto [x2, y2] = static_cast<int_point_t>(points[i]);
        const point_t &p_y_min = (y1 < y2) ? points[i - 1] : points[i];
        et[p_y_min.second].push_back(
            {std::max(y1, y2), p_y_min.first,
             static_cast<double>(x2 - x1) / static_cast<double>(y2 - y1)});
    }
    for (auto &it : et) {
        std::sort(it.begin(), it.end(), [](const Edge &a, const Edge &b) {
            return a.x < b.x;
        });
    }
}

Polygon::~Polygon() {
}

void Polygon::draw(wxDC &dc) {
    /*
    fill the polygon
    */
    dc.SetPen(wxPen(color));

    // while (aet.size() > 0) {
    while (aet.size() > 0 && et.size() > 0) {
        // remove edges from aet
        for (auto it = aet.begin(); it != aet.end();) {
            if (it->y_max == it->x) {
                it = aet.erase(it);
            } else {
                it++;
            }
        }
        // add edges to aet
        for (auto &it : et) {
            for (auto &it2 : it) {
                if (it2.y_max == it2.x) {
                    aet.push_back(it2);
                }
            }
        }
        // sort aet
        std::sort(aet.begin(), aet.end(), [](const Edge &a, const Edge &b) {
            return a.x < b.x;
        });
        // draw lines
        for (size_t i = 0; i < aet.size(); i += 2) {
            dc.DrawLine(aet[i].x, aet[i].y_max, aet[i + 1].x, aet[i + 1].y_max);
        }
        // increment x
        for (auto &it : aet) {
            it.x += it.inc;
        }
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
