///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <wx/slider.h>
#include <wx/checkbox.h>
#include <wx/gauge.h>
#include <wx/clrpicker.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame5
///////////////////////////////////////////////////////////////////////////////
class MyFrame5 : public wxFrame
{
  private:
  protected:
	wxCheckBox *m_checkBox1;
	void Form_Paint(wxPaintEvent &e);
	// Virtual event handlers, overide them in your derived class
	virtual void m_button30OnButtonClick(wxCommandEvent &event) { event.Skip(); }
	virtual void m_slider2OnScroll(wxScrollEvent &event) { event.Skip(); }

	virtual void m_checkBox1OnCheckBox(wxCommandEvent &event) { event.Skip(); }
	virtual void m_colourPicker3OnColourChanged(wxColourPickerEvent &event) { event.Skip(); }
	virtual void m_textCtrl3OnText(wxCommandEvent &event) { event.Skip(); }
	virtual void m_choice4OnChoice(wxCommandEvent &event) { event.Skip(); }

  public:
	wxPanel *m_panel2;
	wxButton *m_button30;
	wxSlider *m_slider2;
	wxGauge *m_gauge2;
	wxColourPickerCtrl *m_colourPicker3;
	wxTextCtrl *m_textCtrl3;
	wxChoice *m_choice4;

	MyFrame5(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString &title = wxEmptyString, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxSize(692, 422), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~MyFrame5();
};
