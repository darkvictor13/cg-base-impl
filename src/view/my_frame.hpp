#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "draw_panel.hpp"

enum { ID_HELLO = 1, ID_PAINT_PANEL, ID_CLEAR_PANEL, ID_PAINT };

class MyFrame : public wxFrame {
    private:
        DrawPanel* drawPanel;
        wxBoxSizer *sizer;

    public:
        MyFrame();
};