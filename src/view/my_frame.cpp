#include "my_frame.hpp"

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
    menuPaint->Append(ID_PAINT_PANEL, "&Paint...\tCtrl-P",
                      "Realiza o desenho no painel");
    menuPaint->Append(ID_CLEAR_PANEL, "&Clear...\tCtrl-C", "Limpa o painel");

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    menuBar->Append(menuPaint, "&Paint");
    SetMenuBar(menuBar);
    CreateStatusBar();
    SetStatusText(wxT("Primeira aplicação de computação gráfica!"));

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
            drawPanel->drawNow();
            drawPanel->Refresh();
        },
        ID_PAINT_PANEL);

    Bind(
        wxEVT_MENU,
        [=](wxCommandEvent&) {
            drawPanel->clearNow();
            drawPanel->Refresh();
        },
        ID_CLEAR_PANEL);
    
    Bind(
        wxEVT_PAINT,
        [=](wxPaintEvent&) {
            drawPanel->paintNow();
            //drawPanel->Refresh();
        },
        ID_PAINT);
}