#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <point.hpp>
#include <vector>

namespace cg {
class DrawBaseElement {
    protected:
        std::vector<point_t> points;
        wxColour color;

    public:
        DrawBaseElement(const wxColour &color = wxColour(255, 255, 255))
            : points(), color(color){};

        virtual void draw(wxDC &dc) = 0;
        virtual ~DrawBaseElement() = default;
};
};  // namespace cg