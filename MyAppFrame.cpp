#include "MyAppFrame.h"

MyAppFrame::MyAppFrame(wxWindow *parent,
                       wxWindowID id,
                       const wxString& title,
                       const wxPoint& pos,
                       const wxSize& sizee,
                       long style)
{

    create(parent, id, title, pos, sizee, style);
}
void MyAppFrame::create(wxWindow *parent,
                wxWindowID id,
                const wxString& title,
                const wxPoint& pos,
                const wxSize& sizee,
                long style)
{
    wxFrame::Create(parent, id, title, pos, sizee, style);
    wxStatusBar *stb = CreateStatusBar();
    stb->SetStatusText(wxT("0"));

    Board *plateau = new Board(this);
    plateau->SetFocus();
    plateau->Start();
}
