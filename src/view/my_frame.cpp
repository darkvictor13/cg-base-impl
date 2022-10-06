#include "my_frame.hpp"

#include "line_cutter.hpp"

using namespace cg;

MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "Hello World"),
      drawPanel(new DrawPanel(this)),
      sizer(new wxBoxSizer(wxHORIZONTAL)) {
    sizer->Add(drawPanel, 1, wxEXPAND);
    SetSizer(sizer);
    SetAutoLayout(true);

    wxMenu* menuFile = new wxMenu;
    menuFile->Append(wxID_EXIT);

    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenu* menuPaint = new wxMenu;
    menuPaint->Append(ID_PAINT_PANEL, "&Atualizar",
                      "Realiza o desenho no painel");
    menuPaint->Append(ID_CLEAR_PANEL, "&Limpar", "Limpa o painel");

    wxMenu* menuDraw = new wxMenu;
    menuDraw->Append(ID_DRAW_CIRCLE, "&Circulo",
                     "Desenha um círculo no painel");
    menuDraw->Append(ID_DRAW_LINE, "&Reta", "Desenha uma reta no painel");
    menuDraw->Append(ID_DRAW_POLYGON, "&Poligono",
                     wxT("Desenha um polígono no painel"));
    menuDraw->Append(ID_DRAW_CUT_LINE_AREA, "&Area de corte",
                     wxT("Desenha a área de corte no painel"));

    wxMenu* menuCutArea = new wxMenu;
    menuCutArea->Append(ID_SET_CUT_AREA, wxT("&Definir área de corte..."),
                        wxT("Define a área de corte"));

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    menuBar->Append(menuPaint, "&Paint");
    menuBar->Append(menuDraw, "&Draw");
    menuBar->Append(menuCutArea, "&Cut Area");
    SetMenuBar(menuBar);
    CreateStatusBar();
    SetStatusText(wxT("Primitivas de computação gráfica!"));

    Bind(
        wxEVT_MENU,
        [=](wxCommandEvent&) {
            wxMessageBox(wxT("Aplicação de computação gráfica"),
                         "About Hello World", wxOK | wxICON_INFORMATION);
        },
        wxID_ABOUT);

    Bind(
        wxEVT_MENU,
        [=](wxCommandEvent&) {
            Close(true);
        },
        wxID_EXIT);

    Bind(
        wxEVT_MENU,
        [=](wxCommandEvent&) {
            drawPanel->paintNow();
            drawPanel->Refresh(false);
        },
        ID_PAINT_PANEL);

    Bind(
        wxEVT_PAINT,
        [=](wxPaintEvent&) {
            drawPanel->paintNow();
            drawPanel->Refresh(false);
        },
        ID_UPDATE_PANEL);

    Bind(wxEVT_MENU, &MyFrame::drawLine, this, ID_DRAW_LINE);
    Bind(wxEVT_MENU, &MyFrame::drawCircle, this, ID_DRAW_CIRCLE);
    Bind(wxEVT_MENU, &MyFrame::drawPolygon, this, ID_DRAW_POLYGON);
    Bind(wxEVT_MENU, &MyFrame::drawClear, this, ID_CLEAR_PANEL);
    Bind(wxEVT_MENU, &MyFrame::drawCutArea, this, ID_DRAW_CUT_LINE_AREA);
    Bind(wxEVT_MENU, &MyFrame::setCutArea, this, ID_SET_CUT_AREA);
}

void MyFrame::drawLine(wxCommandEvent& event) {
    auto& config_ref = drawPanel->getConfig();
    config_ref.draw_option = cg::DrawOptions::DRAW_LINE;
    drawPanel->paintNow();
    drawPanel->Refresh(false);
}

void MyFrame::drawCircle(wxCommandEvent& event) {
    auto& config_ref = drawPanel->getConfig();
    config_ref.draw_option = cg::DrawOptions::DRAW_CIRCLE;
    drawPanel->paintNow();
    drawPanel->Refresh(false);
}

void MyFrame::drawPolygon(wxCommandEvent& event) {
    auto& config_ref = drawPanel->getConfig();
    config_ref.draw_option = cg::DrawOptions::DRAW_POLYGON;
    drawPanel->paintNow();
    drawPanel->Refresh(false);
}

void MyFrame::drawCutArea(wxCommandEvent& event) {
    auto& config_ref = drawPanel->getConfig();
    if (config_ref.draw_option == cg::DrawOptions::DRAW_CLEAR) {
        config_ref.draw_option = cg::DrawOptions::DRAW_NONE;
    }
    config_ref.is_cutter_visible = true;
    drawPanel->paintNow();
    drawPanel->Refresh(false);
}

void MyFrame::drawClear(wxCommandEvent& event) {
    auto& config_ref = drawPanel->getConfig();
    config_ref.is_cutter_visible = false;
    config_ref.draw_option = cg::DrawOptions::DRAW_CLEAR;
    drawPanel->paintNow();
    drawPanel->Refresh(false);
}

void MyFrame::setCutArea(wxCommandEvent& event) {
    cg::point_t point_min, point_max;
    wxTextEntryDialog* dialog = new wxTextEntryDialog(
        this, wxT("Digite o ponto mínimo da area de corte (x,y):"), "Ponto",
        "(0,0)");
    if (dialog->ShowModal() == wxID_OK) {
        wxString value = dialog->GetValue();
        point_min = parsePoint(value.ToStdString());
        std::cout << "Ponto minimo: " << point_min << '\n';
    }
    delete dialog;
    dialog = new wxTextEntryDialog(
        this, wxT("Digite o ponto máximo da area de corte (x,y):"), "Ponto",
        "(0,0)");
    if (dialog->ShowModal() == wxID_OK) {
        wxString value = dialog->GetValue();
        point_max = parsePoint(value.ToStdString());
        std::cout << "Ponto maximo: " << point_max << '\n';
    }
    cg::LineCutter::getInstance().setLimits(point_min, point_max);
    drawCutArea(event);
}