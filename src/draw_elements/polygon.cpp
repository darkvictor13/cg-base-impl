#include "polygon.hpp"

using namespace cg;

Edge::Edge(const point_t &p1, const point_t &p2) {
    if (p1.second < p2.second) {
        this->p1 = p1;
        this->p2 = p2;
    } else {
        this->p1 = p2;
        this->p2 = p1;
    }
}

Polygon::Polygon(const std::vector<point_t> &points, const wxColour &color)
    : DrawBaseElement(color) {
    this->points = points;
}

Polygon::~Polygon() {
}

void Polygon::draw(wxDC &dc) {
    dc.SetPen(wxPen(color));
    const int size = points.size();
    wxPoint *wx_points = new wxPoint[size];
    for (int i = 0; i < size; i++) {
        wx_points[i] = wxPoint(points[i].first, points[i].second);
    }
    dc.DrawPolygon(size, wx_points);
}

/*void AET::AET(){
    ymax = 0;
    x = 0;
    inc = 0;
}

void ET::ET(){
    p = 0;
}
*/

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
    ET = insere(novo, listPolygon);
    
    return novo;

}

ET *insere (AET* aresta, ET* listPolygon){
        listPolygon.insert(aresta, aresta->x);
        //ordenar por x
}

ET *remove (ET* listPolygon, AET* aresta){
    if(!empty(listPolygon)){
        listPolygon.remove(aresta);
    }
}
