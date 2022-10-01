#include "draw_panel.hpp"

#include "debug.hpp"

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

    if (shouldDraw) {
        myDraw(dc);
    } else {
        clear(dc);
    }
}

void DrawPanel::myDraw(wxDC& dc) {
    DEBUG("myDraw");

    const int mid_x = width / 2;
    const int one_third_y = height / 3;
    const int head_radius = one_third_y / 4;

    dc.SetBrush(*wxWHITE_BRUSH);
    dc.SetPen({wxColour(0, 0, 0), 1});

    // Draw the head
    dc.DrawCircle(mid_x, one_third_y - head_radius, head_radius);

    // Draw the eyes
    dc.DrawCircle(mid_x - head_radius / 3, one_third_y - head_radius,
                  head_radius / 4);
    dc.DrawCircle(mid_x + head_radius / 3, one_third_y - head_radius,
                  head_radius / 4);

    // Draw the eyeballs
    dc.SetBrush(*wxBLACK_BRUSH);
    dc.DrawCircle(mid_x - head_radius / 3, one_third_y - head_radius,
                  head_radius / 8);
    dc.DrawCircle(mid_x + head_radius / 3, one_third_y - head_radius,
                  head_radius / 8);

    // Draw the mouth
    dc.DrawLine(mid_x - head_radius / 3, one_third_y - head_radius / 2,
                mid_x + head_radius / 3, one_third_y - head_radius / 2);

    // draw the body
    dc.DrawLine(mid_x, one_third_y, mid_x, height - one_third_y);

    // draw the legs
    dc.DrawLine(mid_x, height - one_third_y, mid_x - one_third_y / 2, height);
    dc.DrawLine(mid_x, height - one_third_y, mid_x + one_third_y / 2, height);

    // draw the arms
    dc.DrawLine(mid_x, one_third_y, mid_x - one_third_y / 2,
                one_third_y + one_third_y / 2);
    dc.DrawLine(mid_x, one_third_y, mid_x + one_third_y / 2,
                one_third_y + one_third_y / 2);
}

void DrawPanel::clear(wxDC& dc) {
    DEBUG("clear");
    // dc.SetBackground(*wxWHITE_BRUSH);
    dc.Clear();
}

DrawPanel::DrawPanel(wxFrame* parent) : wxPanel(parent), shouldDraw(false) {
    DEBUG("DrawPanel");
}

void DrawPanel::paintNow() {
    DEBUG("paintNow");
    wxClientDC dc(this);
    render(dc);
}

void DrawPanel::drawNow() {
    DEBUG("drawNow");
    shouldDraw = true;
    paintNow();
}

void DrawPanel::clearNow() {
    DEBUG("clearNow");
    shouldDraw = false;
    paintNow();
}

DrawPanel::~DrawPanel() {
    DEBUG("DrawPanel destructor");
}
