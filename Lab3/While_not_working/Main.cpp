#include "wx/wxprec.h"
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

// #include "noname.cpp"
#include "MyProject1MyFrame5.cpp"
class MyApp : public wxApp
{
public:
  virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
  MyFrame();

private:
  void OnExit(wxCommandEvent &command_event);
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
  wxFrame *mainFrame = new MyProject1MyFrame5(NULL);
  mainFrame->Show(true);
  SetTopWindow(mainFrame);
  return true;
}

MyFrame::MyFrame() : wxFrame(NULL, wxID_ANY, "Student_beer -  Lab_03")
{
  Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
}
void MyFrame::OnExit(wxCommandEvent &event)
{
  Close(true);
}


