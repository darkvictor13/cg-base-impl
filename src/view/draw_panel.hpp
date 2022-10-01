#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class DrawPanel : public wxPanel {
    private:
        bool shouldDraw;
        int width, height;
        void paintEvent(wxPaintEvent& evt);
        void sizeEvent(wxSizeEvent& evt);
        void render(wxDC& dc);

        void myDraw(wxDC& dc);
        void clear(wxDC& dc);

    public:
        DrawPanel(wxFrame* parent);
        void paintNow();
        void drawNow();
        void clearNow();
        ~DrawPanel();

        DECLARE_EVENT_TABLE()
};