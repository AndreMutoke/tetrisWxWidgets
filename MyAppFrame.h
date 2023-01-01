#ifndef MYAPPFRAME_H_INCLUDED
#define MYAPPFRAME_H_INCLUDED
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif // WX_PRECOMP

#include <wx/frame.h>
#include <wx/image.h>

//#include "plateforme.h"
#include "board.h"

class MyAppFrame : public wxFrame
{
public:
    MyAppFrame(wxWindow *parent,
                wxWindowID id = -1,
                const wxString& title= _("Tetris"),
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& sizee = wxDefaultSize,
                long style = wxDEFAULT_FRAME_STYLE);

protected:
    void create(wxWindow *parent,
                wxWindowID id = -1,
                const wxString& title= _("MyApp"),
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& sizee = wxDefaultSize,
                long style = wxDEFAULT_FRAME_STYLE);
};



#endif // MYAPPFRAME_H_INCLUDED
