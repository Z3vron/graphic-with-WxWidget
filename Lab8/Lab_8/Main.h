

#ifndef MYGREATPROJECT_MAIN_H
#define MYGREATPROJECT_MAIN_H

#pragma once

#include "wx/wx.h"
// #include "noname.cpp"
#include "GUIMyFrameMyFrame1.h"

class MyApp : public wxApp
{
public:
	virtual bool OnInit ();
};

class MyFrame : public wxFrame
{
public:
	MyFrame ();

private:
	void OnExit (wxCommandEvent &command_event);
};

bool MyApp::OnInit ()
{
	wxFrame *mainFrame = new GUIMyFrameMyFrame1 (NULL);
	mainFrame->Show (true);
	SetTopWindow (mainFrame);
	return true;
}

MyFrame::MyFrame () : wxFrame (NULL, wxID_ANY, "Monkey Lab_03")
{
	Bind (wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
}

void MyFrame::OnExit (wxCommandEvent &event)
{
	Close (true);
}

#endif //MYGREATPROJECT_MAIN_H


