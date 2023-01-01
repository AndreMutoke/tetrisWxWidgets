#ifndef MAIN_HPP_INCLUDED
#define MAIN_HPP_INCLUDED
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif // WX_PRECOMP


class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};
DECLARE_APP(MyApp)

#endif // MAIN_HPP_INCLUDED
