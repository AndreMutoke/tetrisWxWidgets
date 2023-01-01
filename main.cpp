#include <iostream>
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif // WX_PRECOMP
#include "main.hpp"
#include "MyAppFrame.h"


IMPLEMENT_APP(MyApp)
bool MyApp::OnInit()
{
    MyAppFrame* mainWindow = new MyAppFrame(NULL);
    mainWindow->Center();
    mainWindow->Show(true);
    return true;
}
