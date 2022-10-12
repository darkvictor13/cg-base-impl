#include "ponto_medio.hpp"

#include "debug.hpp"

using namespace cg;

/*
void PontoMedio::write_pixel(x, y){
    // coloca a cor que vai pintar o pixel também?

    //coloco como bool (pinta - true, n pinta - false)?
    //ou adicionar os pontos em uma lista para depois printar?
}

void PontoMedio::write_circle(x, y){
    write_pixel(x, y);
    write_pixel(x , -y);
    write_pixel(-x, y);
    write_pixel(-x, -y);
    write_pixel(y, x);
    write_pixel(y, -x);
    write_pixel(-y, x);
    write_pixel(-y, -x);
}

// caminho: reta ou circunferência (nova função ou arquivos separados para
cada?)

void PontoMedio::BresenhamReta (point_t &x1, point_t &y1, point_t &x2, point_t
&y2){

    int dx, dy, incNE, incE, x, y, d;

    dx = x2 - x1;
    dy = y2 - y1;

    d = 2 * dy - dx;

    incE = 2 * dy;
    incNE = 2 * (dy - dx);

    x = x1;
    y = y1;

    if(dx/dy >= 0 && dx/dy <= 1){ //inclinação da reta
        write_pixel(x, y);

        while(x < x2){
            if(d <= 0){
                d += incE;
                x++;
            } else {
                d += incNE;
                x++;
                y++;
            }
            write_pixel(x, y);
        }
    }

}

void PontoMedio::BresenhamCircun (int &r){

    int x, y;
    float h;

    x = 0;
    y = r;
    h = 1 - r;

    write_circle(x, y);

    while(y > x){
        if(h < 0){
            h = h + 2*x + 3;
            x++;
        } else{
            h = h + 2*(x - y) + 5;
            x++;
            y++;
        }
        write_circle(x, y);
    }
}
*/