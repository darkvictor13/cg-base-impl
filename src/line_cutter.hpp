#pragma once

#include "outcode.hpp"
#include "point.hpp"

namespace cg {
enum Positions { LEFT, RIGHT, BOTTOM, TOP };

class LineCutter {
        friend class DrawPanel;
        friend class MyFrame;

    public:
        static LineCutter &getInstance();
        /**
         * @brief Corta os pontos fora dos limites do clipping,
         * para que somente os os pontos dentro do clipping sejam desenhados.
         *
         * @warning p1 e p2 são alterados.
         *
         * @param p1 referência para o primeiro ponto da linha
         * @param p2 referência para o segundo ponto da linha
         * @return true Se é possível desenhar a linha dentro dos limites do
         * clipping
         * @return false
         */
        bool cohenSutherland(point_t &p1, point_t &p2);
        void setLimits(const point_t min, point_t max);
        bool notInitialized() const;
        ~LineCutter();

    private:
        uint16_t MAX_X, MIN_X, MAX_Y, MIN_Y;

    private:
        LineCutter();
        outcode_t calculateOutcode(const float x, const float y) const;
        outcode_t calculateOutcode(const point_t &p) const;
};

};  // namespace cg