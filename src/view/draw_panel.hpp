#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "config.hpp"
#include "line_cutter.hpp"

namespace cg {
class DrawPanel : public wxPanel {
    private:
        cg::Config config;
        int width, height;
        void paintEvent(wxPaintEvent& evt);
        void sizeEvent(wxSizeEvent& evt);
        void render(wxDC& dc);
        void clear(wxDC& dc);

        void drawLine(point_t begin, point_t end, bool use_line_cutter = false);
        void drawCircle(point_t center, uint16_t radius);

    public:
        DrawPanel(wxFrame* parent);
        void setConfig(const Config& config);
        void setConfig(Config&& config);
        void setDrawOption(const DrawOptions option);
        void paintNow();

        cg::Config& getConfig();

        ~DrawPanel();

        DECLARE_EVENT_TABLE()
};
};  // namespace cg