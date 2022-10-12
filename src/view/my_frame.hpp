#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "draw_panel.hpp"

enum {
    ID_HELLO = 1,
    ID_GET_PANEL_SIZE,
    ID_SET_CUT_AREA,
    ID_PAINT_PANEL,
    ID_CLEAR_PANEL,
    ID_UPDATE_PANEL,
    ID_DRAW_CIRCLE,
    ID_DRAW_LINE,
    ID_DRAW_POLYGON,
    ID_DRAW_CUT_LINE_AREA,
};

namespace cg {
class MyFrame : public wxFrame {
    public:
        MyFrame();

    private:
        DrawPanel *drawPanel;
        wxBoxSizer *sizer;

    private:
        void drawLine(wxCommandEvent &event);
        void drawCircle(wxCommandEvent &event);
        void drawPolygon(wxCommandEvent &event);
        void drawCutArea(wxCommandEvent &event);
        void drawClear(wxCommandEvent &event);

        void setCutArea(wxCommandEvent &event);
};
};  // namespace cg