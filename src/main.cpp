#include "view/my_frame.hpp"

class MyApp : public wxApp {
    public:
        virtual bool OnInit() override {
            auto frame = new cg::MyFrame();
            frame->Show(true);
            return true;
        }
};

wxIMPLEMENT_APP(MyApp);