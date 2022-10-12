#include "my_frame.hpp"

#include <sstream>

#include "circle.hpp"
#include "line.hpp"
#include "line_cutter.hpp"
#include "polygon.hpp"
#include "rectangle.hpp"

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
    cg::point_t p1, p2;
    wxTextEntryDialog* dialog = new wxTextEntryDialog(
        this, wxT("Digite o ponto inicial da reta (x,y):"), "Ponto", "(0,0)");
    if (dialog->ShowModal() == wxID_OK) {
        wxString value = dialog->GetValue();
        p1 = parsePoint(value.ToStdString());
    }
    delete dialog;
    dialog = new wxTextEntryDialog(
        this, wxT("Digite o ponto final da reta (x,y):"), "Ponto", "(100,100)");
    if (dialog->ShowModal() == wxID_OK) {
        wxString value = dialog->GetValue();
        p2 = parsePoint(value.ToStdString());
    }
    delete dialog;
    drawPanel->getElements().push_back(new cg::Line(p1, p2));
    drawPanel->paintNow();
    // drawPanel->Refresh(false);
}

void MyFrame::drawCircle(wxCommandEvent& event) {
    cg::point_t center = {0, 0};
    auto dialog =
        wxTextEntryDialog(this, wxT("Digite o contro da circunferência (x,y):"),
                          "Ponto", "(0,0)");
    if (dialog.ShowModal() == wxID_OK) {
        wxString value = dialog.GetValue();
        center = parsePoint(value.ToStdString());
    }
    auto dialog_radius = wxTextEntryDialog(
        this, wxT("Digite o raio da circunferência:"), "Raio", "100");
    if (dialog_radius.ShowModal() == wxID_OK) {
        wxString value = dialog_radius.GetValue();
        auto radius = std::stof(value.ToStdString());
        drawPanel->getElements().push_back(new cg::Circle(center, radius));
        drawPanel->paintNow();
        drawPanel->Refresh(false);
    }
}

void MyFrame::drawPolygon(wxCommandEvent& event) {
    auto dialog = wxTextEntryDialog(
        this, wxT("Digite os pontos do polígono (x,y):"), "Ponto",
        "(0,0)\n(100, 100)", wxOK | wxCANCEL | wxTE_MULTILINE);
    if (dialog.ShowModal() == wxID_OK) {
        auto lines = dialog.GetValue().ToStdString();
        std::vector<cg::point_t> points;
        std::stringstream ss(lines);
        std::string line;
        while (std::getline(ss, line)) {
            points.push_back(parsePoint(line));
        }
        drawPanel->getElements().push_back(new cg::Polygon(points));
    }
    drawPanel->paintNow();
    drawPanel->Refresh(false);
}

void MyFrame::drawCutArea(wxCommandEvent& event) {
    drawPanel->setCutterVisibility(true);
    drawPanel->paintNow();
    drawPanel->Refresh(false);
}

void MyFrame::drawClear(wxCommandEvent& event) {
    auto& elements = drawPanel->getElements();
    for (auto& element : elements) {
        delete element;
    }
    elements.clear();
    drawPanel->setCutterVisibility(false);
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
    delete dialog;
    cg::LineCutter::getInstance().setLimits(point_min, point_max);
    drawCutArea(event);
}