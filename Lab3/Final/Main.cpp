#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#define _USE_ANTIALIASING
#include <wx/wxprec.h>
#include <wx/panel.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/filedlg.h>
#include <wx/checkbox.h>
#include <wx/scrolbar.h>
#include <wx/gauge.h>
#include <wx/colordlg.h>
#include <wx/textctrl.h>
#include <wx/combobox.h>
#include <wx/frame.h>
#include <wx/dcbuffer.h>
#include <wx/dcgraph.h>
#include <iostream>

class MyFrame : public wxFrame  {
	private:
	//extra part
	int help1{1};
	bool help2 {false};
	void Timer1_Timer(wxTimerEvent& e);

	//regular
		void WxButtonFile_Click   (wxCommandEvent&  e);
		void WxCheckBox_Click     (wxCommandEvent&  e);
		void WxScrollBar_Scroll   (wxScrollEvent&   e);
		void WxButtonColour_Click (wxCommandEvent&  e);
		void WxTextCtrl_Updated   (wxCommandEvent&  e);
		void WxComboBox_Choise    (wxCommandEvent&  e);

		void Draw();
		void Form_Paint           (wxPaintEvent&    e);
		void Form_Update          (wxUpdateUIEvent& e);

		enum {
			ID_WXBUTTON_FILE   = 1001,
			ID_WXCHECKBOX      = 1002,
			ID_WXSCROLLBAR     = 1003,
			ID_WXGAUGE         = 1004,
			ID_WXBUTTON_COLOUR = 1005,
			ID_WXTEXTCTRL      = 1006,
			ID_WXCOMBOBOX      = 1007,
		};

		wxBoxSizer*         m_sizer1;
		wxBoxSizer*         m_sizer2;
		wxBoxSizer*         m_sizer3;

		wxPanel*            m_panel;
		wxButton*           m_buttonFile;
		wxCheckBox*         m_checkBox;
		wxScrollBar*        m_scrollBar;
		wxGauge*            m_gauge;
		wxButton*           m_buttonColour;
		wxTextCtrl*         m_textCtrl;
		wxComboBox*         m_comboBox;

		wxString            m_text = "Flanki";
		int                 m_shapeChoise;

		wxImage             m_image;
		wxBitmap            m_buffer;
		wxColour            m_shapeColour;
		wxBitmap            m_beer;
		wxTimer* WxTimer1;
	public:
		MyFrame (wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(600, 400), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
		~MyFrame();
        
};
int help{0};


MyFrame::MyFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style) {
	this          -> SetSizeHints(wxSize(600, 400), wxDefaultSize);

	m_sizer1       = new wxBoxSizer(wxHORIZONTAL);
	m_sizer2       = new wxBoxSizer(wxHORIZONTAL);
	m_sizer3       = new wxBoxSizer(wxVERTICAL);

	m_panel        = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	m_panel       -> SetBackgroundColour(wxColour(255, 255, 255));
	m_sizer2      -> Add(m_panel, 1, wxEXPAND | wxALL, 5);
	m_sizer1      -> Add(m_sizer2, 1, wxEXPAND, 5);
	
	m_sizer3      -> SetMinSize(wxSize(196, 350));
	m_sizer1      -> Add(m_sizer3, 0, wxEXPAND, 5);

	m_buttonFile   = new wxButton(this, ID_WXBUTTON_FILE, "Save to file", wxDefaultPosition, wxDefaultSize, 0);
	m_sizer3      -> Add(m_buttonFile, 0, wxALIGN_CENTER | wxALL, 5);
	
	m_checkBox     = new wxCheckBox(this, ID_WXCHECKBOX, "beer", wxDefaultPosition, wxDefaultSize, 0);
	m_sizer3      -> Add(m_checkBox, 0, wxALIGN_CENTER | wxALL, 5);
	
	m_scrollBar    = new wxScrollBar(this, ID_WXSCROLLBAR, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL);
	m_scrollBar   -> SetScrollbar(0, 1, 100, 1);
	m_scrollBar   -> Disable();
	m_sizer3      -> Add(m_scrollBar, 0, wxALL | wxEXPAND, 5);
	
	m_gauge        = new wxGauge(this, ID_WXGAUGE, 99, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL);
	m_gauge       -> SetValue(0);
	m_sizer3      -> Add(m_gauge, 0, wxALL | wxEXPAND, 5);
	
	m_buttonColour = new wxButton(this, ID_WXBUTTON_COLOUR, "Choose color of object", wxDefaultPosition, wxDefaultSize, 0);
	m_sizer3      -> Add(m_buttonColour, 0, wxALIGN_CENTER | wxALL, 5);
	
	m_textCtrl     = new wxTextCtrl(this, ID_WXTEXTCTRL, m_text, wxDefaultPosition, wxDefaultSize, 0);
	m_sizer3      -> Add(m_textCtrl, 0, wxALIGN_CENTER | wxALL, 5);
	
	m_comboBox     = new wxComboBox(this, ID_WXCOMBOBOX, "Star", wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_DROPDOWN | wxCB_READONLY);
	m_comboBox    -> Append("Star");
	m_comboBox    -> Append("Moon");
	m_comboBox    -> Append("Beer cap");
	m_comboBox    -> SetSelection(0);
	m_sizer3      -> Add(m_comboBox, 0, wxALIGN_CENTER | wxALL, 5);
		
	this          -> SetSizer(m_sizer1);
	this          -> Layout();
	this          -> Centre(wxBOTH);

	Bind(wxEVT_BUTTON,            &MyFrame::WxButtonFile_Click,   this, ID_WXBUTTON_FILE);
	Bind(wxEVT_CHECKBOX,          &MyFrame::WxCheckBox_Click,     this, ID_WXCHECKBOX);
	Bind(wxEVT_SCROLL_THUMBTRACK, &MyFrame::WxScrollBar_Scroll,   this, ID_WXSCROLLBAR);
	Bind(wxEVT_BUTTON,            &MyFrame::WxButtonColour_Click, this, ID_WXBUTTON_COLOUR);
	Bind(wxEVT_TEXT,              &MyFrame::WxTextCtrl_Updated,   this, ID_WXTEXTCTRL);
	Bind(wxEVT_COMBOBOX,          &MyFrame::WxComboBox_Choise,    this, ID_WXCOMBOBOX);
	Bind(wxEVT_PAINT,             &MyFrame::Form_Paint,           this);
	Bind(wxEVT_UPDATE_UI,         &MyFrame::Form_Update,          this);

	m_shapeColour = wxColour(*wxYELLOW);

	wxImage beer = wxImage();
	beer.AddHandler (new wxPNGHandler);
	beer.LoadFile ("Beer.png", wxBITMAP_TYPE_PNG);
	m_beer = wxBitmap(beer);

	WxTimer1 = new wxTimer();
	WxTimer1->SetOwner(this, wxID_ANY);

}

MyFrame::~MyFrame() {
	delete m_panel;
	delete m_buttonFile;
	delete m_checkBox;
	delete m_scrollBar;
	delete m_gauge;
	delete m_buttonColour;
	delete m_textCtrl;
	delete m_comboBox;
}

void MyFrame::WxButtonFile_Click   (wxCommandEvent& WXUNUSED(e)) {
	wxFileDialog saveFileDialog(this, "Choose a file", "", "", "BMP files (*.bmp)|*.bmp|JPG files (*.jpg)|*.jpg|PNG files (*.png)|*.png", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (saveFileDialog.ShowModal() == wxID_CANCEL)
		return;
	m_image = m_buffer.ConvertToImage();
	m_image.AddHandler (new wxJPEGHandler);
	m_image.AddHandler (new wxPNGHandler);
	m_image.SaveFile   (saveFileDialog.GetPath());
}

void MyFrame::WxCheckBox_Click     (wxCommandEvent& WXUNUSED(e)) {
	m_scrollBar -> Enable(m_checkBox -> IsChecked());
}

void MyFrame::WxScrollBar_Scroll   (wxScrollEvent&  WXUNUSED(e)) {
	m_gauge -> SetValue(m_scrollBar -> GetThumbPosition());
	Draw();
}

void MyFrame::WxButtonColour_Click (wxCommandEvent& WXUNUSED(e)) {
	wxColourDialog chooseColourDialog(this, nullptr);
	if (chooseColourDialog.ShowModal() == wxID_CANCEL)
		return;
	m_shapeColour = chooseColourDialog.GetColourData().GetColour();
    help = 1;
}

void MyFrame::WxTextCtrl_Updated   (wxCommandEvent& WXUNUSED(e)) {
	m_text = m_textCtrl -> GetValue();
}

void MyFrame::WxComboBox_Choise   (wxCommandEvent&  WXUNUSED(e)) {
	m_shapeChoise = m_comboBox -> GetSelection();
}

void MyFrame::Draw() {

	wxClientDC __MyDC   (m_panel);
	m_buffer = wxBitmap (m_panel -> GetSize().x, m_panel -> GetSize().y);
	wxBufferedDC _MyDC  (&__MyDC, m_buffer);
	#ifdef _USE_ANTIALIASING
		wxGCDC MyDC     (_MyDC);
	#else
		#define MyDC _MyDC
	#endif

	wxSize XY = m_panel -> GetSize();
	int x     = (XY.x - 377) / 2;
	int y     = (XY.y - 346) / 2;

	MyDC.SetBackground(*wxWHITE_BRUSH);
	MyDC.Clear();
 // draw beer
	/*if (!m_checkBox -> IsChecked()) {
		MyDC.DrawBitmap    (m_beer, x + 149 - m_beer.GetWidth() / 2, y + 192 - 0.38 * m_gauge->GetValue() - m_beer.GetHeight() / 2);
	}*/

	MyDC.DrawCircle      (x + 188, y + 143, 20   );
	MyDC.DrawEllipse     (x + 176, y + 135, 10, 7);

	if (m_checkBox->IsChecked()) {
		MyDC.DrawEllipticArc (x + 174, y + 148, 26, 5 , 180, 360);
		MyDC.DrawEllipse     (x + 191, y + 135, 10, 7           );
	} else {
		MyDC.DrawEllipticArc (x + 174, y + 148, 26, 5 , 0  , 180);
		MyDC.DrawEllipse     (x + 191, y + 133, 7 , 10          );
	}
	//chest
	MyDC.DrawLine    (x + 188, y + 164, x + 188, y + 234);
	//left leg 
	MyDC.DrawLine    (x + 188, y + 234, x + 159, y + 262);
	//right leg
	MyDC.DrawLine    (x + 188, y + 234, x + 217, y + 262);
	//right arm
	MyDC.DrawLine    (x + 188, y + 173, x + 227, y + 192);
	
	
	MyDC.DrawLine    (x + 188, y + 173, x + 149, y + 192 - 0.38 *help1);
	MyDC.DrawBitmap    (m_beer, x + 149 - m_beer.GetWidth() / 2, y + 192 - 0.38 *help1 - m_beer.GetHeight() / 2);
	 if (m_checkBox->IsChecked()){
		 WxTimer1->Start(10);
		
				
						//drawing endless
	if(help1<100 && help2 == false){
					//std::cout<<"\n help1: " << help1;
					help1++;
				}
					else if(help1 == 100 && help2 == false){
							help2 = true;
					};
					if(help2==true)
						help1--;
					if(help1==-1)
							help2=false;
				
					
		//std::cout<<"\n suwak: "<<m_gauge->GetValue();
	}
	
	
	wxString text1       (m_text);
	MyDC.SetFont         (wxFont(10, wxFONTFAMILY_DEFAULT   , wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Calibri"      ));
	MyDC.DrawText        (text1 , x + 98,  y + 253    );
	wxString text2       (m_text);
	MyDC.SetFont         (wxFont(30, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD  , false, "Comic Sans MS"));
	MyDC.DrawRotatedText (m_text, x + 239, y + 263, 90);

	if      (m_shapeChoise == 0) {
		MyDC.SetBrush   (wxBrush(m_shapeColour));
		MyDC.SetPen     (wxPen  (m_shapeColour));
		wxPoint points[5] = {
			wxPoint(128, 83 ),
			wxPoint(153, 128),
			wxPoint(98 , 103),
			wxPoint(158, 103),
			wxPoint(108, 128)
		};
		MyDC.DrawPolygon(5, points, x, y);
	}
	else if (m_shapeChoise == 1) {
		MyDC.SetBrush   (*wxLIGHT_GREY_BRUSH                );
		MyDC.SetPen     (*wxLIGHT_GREY_PEN                  );
		MyDC.DrawCircle (x + 118, y + 103, 20               );
		MyDC.SetBrush   (*wxWHITE_BRUSH                     );
		MyDC.SetPen     (*wxWHITE_PEN                       );
		MyDC.DrawCircle (x + 108, y + 93 , 20               );
		MyDC.SetBrush   (*wxBLACK_BRUSH                     );
		MyDC.SetPen     (*wxBLACK_PEN                       );
		MyDC.DrawCircle (x + 128, y + 103, 2                );
		MyDC.DrawLine   (x + 118, y + 110, x + 123, y + 113 );
	}
	else if (m_shapeChoise == 2) {
		if(help==1){
			MyDC.SetBrush   (wxBrush(m_shapeColour) );
			MyDC.SetPen     (wxPen  (m_shapeColour) );
		}
		else {
		
			MyDC.SetBrush   (wxBrush(*wxGREEN) );
			MyDC.SetPen     (wxPen  (*wxGREEN) );
		}
		
		MyDC.DrawCircle (x + 118, y + 103, 20);
	}
}

void MyFrame::Form_Paint          (wxPaintEvent&    WXUNUSED(e)) {
	//Draw();
}

void MyFrame::Form_Update         (wxUpdateUIEvent& WXUNUSED(e)) {
		Draw();
}

class MyApp : public wxApp {
	public:
		virtual bool OnInit() {
			MyFrame *frame = new MyFrame(NULL, wxID_ANY, "GFK - Lab3 - student-biwo");
			frame -> Show(true);
			SetTopWindow(frame);
			return true;
		}
};

wxIMPLEMENT_APP(MyApp);