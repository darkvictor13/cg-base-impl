#include "draw_panel.hpp"

#include "debug.hpp"
#include "line.hpp"

using namespace cg;

BEGIN_EVENT_TABLE(DrawPanel, wxPanel)
EVT_PAINT(DrawPanel::paintEvent)
EVT_SIZE(DrawPanel::sizeEvent)
END_EVENT_TABLE()

void DrawPanel::paintEvent(wxPaintEvent& evt) {
    DEBUG("paintEvent");
    wxPaintDC dc(this);
    render(dc);
}

void DrawPanel::sizeEvent(wxSizeEvent& evt) {
    DEBUG("sizeEvent");
    evt.Skip();
}

void DrawPanel::render(wxDC& dc) {
    int new_width, new_height;
    DEBUG("render");

    dc.GetSize(&new_width, &new_height);
    if (new_width != width || new_height != height) {
        width = new_width;
        height = new_height;
    }

    if (is_cutter_visible) {
        const auto& cutter = LineCutter::getInstance();
        const auto height = cutter.MAX_Y - cutter.MIN_Y;
        const auto width = cutter.MAX_X - cutter.MIN_X;
        dc.DrawRectangle(cutter.MIN_X, cutter.MIN_Y, width, height);
    }

    for (auto& element : elements) {
        element->draw(dc);
    }

    /*
        wxPointList points;
        switch (config.draw_option) {
            case DrawOptions::DRAW_CIRCLE:
                dc.DrawCircle(100, 100, 50);
                break;
            case DrawOptions::DRAW_LINE:
                dc.DrawLine(0, 0, width, height);
                break;
            case DrawOptions::DRAW_POLYGON:
                points.Append(new wxPoint(0, 0));
                points.Append(new wxPoint(width / 2, 0));
                points.Append(new wxPoint(width / 2, height / 2));
                points.Append(new wxPoint(0, height / 2));
                dc.DrawPolygon(&points);
                break;
            case DrawOptions::DRAW_NONE:
                break;
            case DrawOptions::DRAW_CLEAR:
                clear(dc);
                break;
            default:
                break;
        }
        cg::Line line({0, 0}, {width, height});
        line.draw(dc);
        */
}

void DrawPanel::clear(wxDC& dc) {
    DEBUG("clear");
    // dc.SetBackground(*wxWHITE_BRUSH);
    dc.Clear();
}

DrawPanel::DrawPanel(wxFrame* parent) : wxPanel(parent) {
    DEBUG("DrawPanel");
}

void DrawPanel::paintNow() {
    DEBUG("paintNow");
    wxClientDC dc(this);
    render(dc);
}

std::vector<DrawBaseElement*>& DrawPanel::getElements() {
    return elements;
}

void DrawPanel::setCutterVisibility(const bool is_visible) {
    is_cutter_visible = is_visible;
}

DrawPanel::~DrawPanel() {
    DEBUG("DrawPanel destructor");
}
