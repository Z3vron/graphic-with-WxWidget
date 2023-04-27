///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "noname.h"

///////////////////////////////////////////////////////////////////////////

MyFrame5::MyFrame5(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));

	wxBoxSizer *bSizer36;
	bSizer36 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer *bSizer38;
	bSizer38 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer *bSizer40;
	bSizer40 = new wxBoxSizer(wxHORIZONTAL);

	m_panel2 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	m_panel2->SetBackgroundColour(wxColour(240, 240, 240));

	bSizer40->Add(m_panel2, 1, wxEXPAND | wxALL, 5);

	bSizer38->Add(bSizer40, 2, wxEXPAND, 5);

	bSizer36->Add(bSizer38, 2, wxEXPAND, 5);

	wxBoxSizer *bSizer39;
	bSizer39 = new wxBoxSizer(wxVERTICAL);

	m_button30 = new wxButton(this, wxID_ANY, wxT("Zapis do pliku"), wxPoint(-1, -1), wxSize(-1, -1), 0);
	m_button30->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));
	m_button30->SetMaxSize(wxSize(200, -1));

	bSizer39->Add(m_button30, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	m_slider2 = new wxSlider(this, wxID_ANY, 0, 0, 100, wxDefaultPosition, wxSize(200, -1), wxSL_HORIZONTAL);
	bSizer39->Add(m_slider2, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	m_checkBox1 = new wxCheckBox(this, wxID_ANY, wxT("perla"), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBox1->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));

	bSizer39->Add(m_checkBox1, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	m_gauge2 = new wxGauge(this, wxID_ANY, 100, wxDefaultPosition, wxSize(200, -1), wxGA_HORIZONTAL);
	m_gauge2->SetValue(0);
	bSizer39->Add(m_gauge2, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	m_colourPicker3 = new wxColourPickerCtrl(this, wxID_ANY, wxColour(78, 154, 6), wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE);
	bSizer39->Add(m_colourPicker3, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 20);

	m_textCtrl3 = new wxTextCtrl(this, wxID_ANY, wxT("tekst"), wxDefaultPosition, wxSize(150, -1), 0);
	bSizer39->Add(m_textCtrl3, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 20);

	wxString m_choice4Choices[] = {wxT("gwiazdka"), wxT("slonce"), wxT("ksiezyc")};
	int m_choice4NChoices = sizeof(m_choice4Choices) / sizeof(wxString);
	m_choice4 = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice4NChoices, m_choice4Choices, 0);
	m_choice4->SetSelection(0);
	bSizer39->Add(m_choice4, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	bSizer36->Add(bSizer39, 1, wxEXPAND, 5);

	this->SetSizer(bSizer36);
	this->Layout();

	this->Centre(wxBOTH);
	Bind(wxEVT_PAINT, &MyFrame5::Form_Paint, this);
	// Connect Events
	m_button30->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame5::m_button30OnButtonClick), NULL, this);
	m_slider2->Connect(wxEVT_SCROLL_TOP, wxScrollEventHandler(MyFrame5::m_slider2OnScroll), NULL, this);
	m_slider2->Connect(wxEVT_SCROLL_BOTTOM, wxScrollEventHandler(MyFrame5::m_slider2OnScroll), NULL, this);
	m_slider2->Connect(wxEVT_SCROLL_LINEUP, wxScrollEventHandler(MyFrame5::m_slider2OnScroll), NULL, this);
	m_slider2->Connect(wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler(MyFrame5::m_slider2OnScroll), NULL, this);
	m_slider2->Connect(wxEVT_SCROLL_PAGEUP, wxScrollEventHandler(MyFrame5::m_slider2OnScroll), NULL, this);
	m_slider2->Connect(wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler(MyFrame5::m_slider2OnScroll), NULL, this);
	m_slider2->Connect(wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler(MyFrame5::m_slider2OnScroll), NULL, this);
	m_slider2->Connect(wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler(MyFrame5::m_slider2OnScroll), NULL, this);
	m_slider2->Connect(wxEVT_SCROLL_CHANGED, wxScrollEventHandler(MyFrame5::m_slider2OnScroll), NULL, this);
	m_checkBox1->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(MyFrame5::m_checkBox1OnCheckBox), NULL, this);
	m_colourPicker3->Connect(wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler(MyFrame5::m_colourPicker3OnColourChanged), NULL, this);
	m_textCtrl3->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MyFrame5::m_textCtrl3OnText), NULL, this);
	m_choice4->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(MyFrame5::m_choice4OnChoice), NULL, this);
}

MyFrame5::~MyFrame5()
{
	// Disconnect Events
	m_button30->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame5::m_button30OnButtonClick), NULL, this);
	m_slider2->Disconnect(wxEVT_SCROLL_TOP, wxScrollEventHandler(MyFrame5::m_slider2OnScroll), NULL, this);
	m_slider2->Disconnect(wxEVT_SCROLL_BOTTOM, wxScrollEventHandler(MyFrame5::m_slider2OnScroll), NULL, this);
	m_slider2->Disconnect(wxEVT_SCROLL_LINEUP, wxScrollEventHandler(MyFrame5::m_slider2OnScroll), NULL, this);
	m_slider2->Disconnect(wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler(MyFrame5::m_slider2OnScroll), NULL, this);
	m_slider2->Disconnect(wxEVT_SCROLL_PAGEUP, wxScrollEventHandler(MyFrame5::m_slider2OnScroll), NULL, this);
	m_slider2->Disconnect(wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler(MyFrame5::m_slider2OnScroll), NULL, this);
	m_slider2->Disconnect(wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler(MyFrame5::m_slider2OnScroll), NULL, this);
	m_slider2->Disconnect(wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler(MyFrame5::m_slider2OnScroll), NULL, this);
	m_slider2->Disconnect(wxEVT_SCROLL_CHANGED, wxScrollEventHandler(MyFrame5::m_slider2OnScroll), NULL, this);
	m_checkBox1->Disconnect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(MyFrame5::m_checkBox1OnCheckBox), NULL, this);
	m_colourPicker3->Disconnect(wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler(MyFrame5::m_colourPicker3OnColourChanged), NULL, this);
	m_textCtrl3->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MyFrame5::m_textCtrl3OnText), NULL, this);
	m_choice4->Disconnect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(MyFrame5::m_choice4OnChoice), NULL, this);
}
void MyFrame5::Form_Paint(wxPaintEvent &event)
{
	int i, j;
	wxPoint pts[5], ptsB[4];
	wxPen MyPen;

	pts[0] = wxPoint(200, 40);
	pts[1] = wxPoint(220, 60);
	pts[2] = wxPoint(240, 50);
	pts[3] = wxPoint(260, 60);
	pts[4] = wxPoint(280, 40);
	ptsB[0] = wxPoint(400, 90);
	ptsB[1] = wxPoint(415, 240);
	ptsB[2] = wxPoint(480, 90);
	ptsB[3] = wxPoint(520, 140);

	wxPaintDC *MyDC;
	MyDC = new wxPaintDC(this);

	MyDC->DrawArc(75, 180, 155, 220, 75, 200);
	MyDC->DrawCheckMark(0, 160, 40, 40);
	MyDC->DrawCircle(50, 260, 40);
	MyDC->DrawEllipse(25, 300, 100, 60);
	MyDC->DrawEllipticArc(25, 360, 100, 60, 130, 290);

	MyDC->DrawLine(160, 10, 300, 30);
	MyDC->DrawLines(5, pts);

	MyDC->DrawPolygon(5, pts, -30, 50);

	MyDC->DrawRectangle(170, 120, 120, 60);
	MyDC->DrawRoundedRectangle(170, 190, 100, 35, 12);
	MyDC->DrawSpline(4, ptsB);

	MyDC->DrawText("QWERTY 123 zxcvb", 400, 30);
	MyDC->DrawRotatedText("QWERTY 123 zxcvb", 400, 250, 30);

	for (i = 0; i < 150; i++)
		for (j = 0; j < 150; j++)
		{
			MyPen.SetColour(i, i - j, j);
			MyDC->SetPen(MyPen);
			MyDC->DrawPoint(i, j);
		}

	delete (MyDC);
}
