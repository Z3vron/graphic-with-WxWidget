
#include "GUIMyFrame1.h"
#include <vector>
#include <fstream>
#include "vecmat.h"

struct Point {
 float x, y, z;
 Point(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

struct Color {
 int R, G, B;
 Color(int _R, int _G, int _B) : R(_R), G(_G), B(_B) {}
};

struct Segment {
 Point begin, end;
 Color color;
 Segment(Point _begin, Point _end, Color _color) : begin(_begin), end(_end), color(_color) {}
};

std::vector<Segment> data;

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
 m_button_load_geometry->SetLabel(_("Wczytaj Geometri\u0119"));
 m_staticText25->SetLabel(_("Obr\u00F3t X:"));
 m_staticText27->SetLabel(_("Obr\u00F3t Y:"));
 m_staticText29->SetLabel(_("Obr\u00F3t Z:"));

 WxSB_TranslationX->SetRange(0, 200); WxSB_TranslationX->SetValue(100);
 WxSB_TranslationY->SetRange(0, 200); WxSB_TranslationY->SetValue(100);
 WxSB_TranslationZ->SetRange(0, 200); WxSB_TranslationZ->SetValue(100);

 WxSB_RotateX->SetRange(0, 360); WxSB_RotateX->SetValue(0);
 WxSB_RotateY->SetRange(0, 360); WxSB_RotateY->SetValue(0);
 WxSB_RotateZ->SetRange(0, 360); WxSB_RotateZ->SetValue(0);

 WxSB_ScaleX->SetRange(1, 200); WxSB_ScaleX->SetValue(100);
 WxSB_ScaleY->SetRange(1, 200); WxSB_ScaleY->SetValue(100);
 WxSB_ScaleZ->SetRange(1, 200); WxSB_ScaleZ->SetValue(100);
}

void GUIMyFrame1::WxPanel_Repaint( wxUpdateUIEvent& event )
{
 Repaint();
}

void GUIMyFrame1::m_button_load_geometry_click( wxCommandEvent& event )
{
 wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("Geometry file (*.geo)|*.geo"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

 if (WxOpenFileDialog.ShowModal() == wxID_OK)
 {
  double x1, y1, z1, x2, y2, z2;
  int r, g, b;

  std::ifstream in(WxOpenFileDialog.GetPath().ToAscii());
  if (in.is_open())
  {
   data.clear();
   while (!in.eof())
   {
    in >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> r >> g >> b;
    data.push_back(Segment(Point(x1, y1, z1), Point(x2, y2, z2), Color(r, g, b)));
   }
   in.close();
  }
 }
}

void GUIMyFrame1::Scrolls_Updated( wxScrollEvent& event )
{
WxST_TranslationX->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationX->GetValue() - 100) / 50.0));
WxST_TranslationY->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationY->GetValue() - 100) / 50.0));
WxST_TranslationZ->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationZ->GetValue() - 100) / 50.0));

WxST_RotateX->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateX->GetValue()));
WxST_RotateY->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateY->GetValue()));
WxST_RotateZ->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateZ->GetValue()));

WxST_ScaleX->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleX->GetValue() / 100.0));
WxST_ScaleY->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleY->GetValue() / 100.0));
WxST_ScaleZ->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleZ->GetValue() / 100.0));


Repaint();
}


void GUIMyFrame1::Repaint()
{
	// 1 //
	Matrix4 first;
	first.data[0][0] = WxSB_ScaleX->GetValue() / 100.0;
	first.data[1][1] = WxSB_ScaleY->GetValue() / 100.0;
	first.data[2][2] = WxSB_ScaleZ->GetValue() / 100.0;

	Matrix4 second;
	double alpha = WxSB_RotateZ->GetValue() * M_PI / 180.0;
	second.data[0][0] = cos(alpha);
	second.data[0][1] = sin(alpha);
	second.data[1][0] = -sin(alpha);
	second.data[1][1] = cos(alpha);
	second.data[2][2] = 1;

	Matrix4 third;
	alpha = WxSB_RotateY->GetValue() * M_PI / 180.0;
	third.data[0][0] = cos(alpha);
	third.data[0][2] = -sin(alpha);
	third.data[1][1] = 1;
	third.data[2][0] = sin(alpha);
	third.data[2][2] = cos(alpha);

	Matrix4 fourth;
	alpha = WxSB_RotateX->GetValue() * M_PI / 180.0;
	fourth.data[0][0] = 1;
	fourth.data[1][1] = cos(alpha);
	fourth.data[1][2] = sin(alpha);
	fourth.data[2][1] = -sin(alpha);
	fourth.data[2][2] = cos(alpha);

	Matrix4 fith;
	fith.data[0][0] = 1;
	fith.data[0][3] = (WxSB_TranslationX->GetValue() - 100.0) / 50.0;
	fith.data[1][1] = 1;
	fith.data[1][3] = (WxSB_TranslationY->GetValue() - 100.0) / 50.0;
	fith.data[2][2] = 1;
	fith.data[2][3] = (WxSB_TranslationZ->GetValue() - 100.0) / 50.0;

	Matrix4 transforfirst = fith * fourth * third * second * first;

	// 2 //
	Matrix4 sixth;
	sixth.data[0][0] = 1;
	sixth.data[1][1] = 1;
	sixth.data[3][2] = 1.0 / 2.0;

	Matrix4 seventh;
	seventh.data[0][0] = WxPanel->GetSize().GetWidth() / 2;
	seventh.data[1][1] = -WxPanel->GetSize().GetHeight() / 2;
	seventh.data[0][3] = WxPanel->GetSize().GetWidth() / 2;
	seventh.data[1][3] = WxPanel->GetSize().GetHeight() / 2;

	Matrix4 transforsecond = seventh * sixth;

	// a //
	wxClientDC _dc(WxPanel);
	wxBufferedDC dc(&_dc);

	dc.SetBackground(*wxWHITE_BRUSH);
	dc.Clear();
	//int i=0;
	// b //
	for (Segment segment : data) {
		Vector4 startPoint, endPoint;
		//dc.SetPen(wxPen(wxColour(segment.color.R, segment.color.G, segment.color.B)));

		dc.SetPen(wxPen(wxColour(255.0*(segment.begin.y+2)/4,255-255.0*(segment.begin.y+2)/4,255-255.0*(segment.begin.y+2)/4)));
		//i++;
		
		startPoint.Set(segment.begin.x, segment.begin.y, segment.begin.z);
		endPoint.Set(segment.end.x, segment.end.y, segment.end.z);

		startPoint = transforfirst * startPoint;
		endPoint = transforfirst * endPoint;

		startPoint.data[0] /= startPoint.data[3];
		startPoint.data[1] /= startPoint.data[3];
		startPoint.data[2] /= startPoint.data[3];

		endPoint.data[0] /= endPoint.data[3];
		endPoint.data[1] /= endPoint.data[3];
		endPoint.data[2] /= endPoint.data[3];

		if ( (startPoint.GetZ() > -2.0 && endPoint.GetZ() <= -2.0) || (endPoint.GetZ() > -2.0 && startPoint.GetZ() <= -2.0) ) {
			Vector4 temp1 = endPoint.GetZ() <= -2.0 ? endPoint : startPoint;
			Vector4 temp2 = endPoint.GetZ() <= -2.0 ? startPoint : endPoint;
			double r = abs((-2.0 - temp1.data[2]) / (temp2.data[2] - temp1.data[2]));
			temp1.data[0] = (temp2.data[0] - temp1.data[0]) * r + temp1.data[0];
			temp1.data[1] = (temp2.data[1] - temp1.data[1]) * r + temp1.data[1];
			temp1.data[2] = -2.0;

			startPoint = transforsecond * temp1;
			endPoint = transforsecond * temp2;

			startPoint.data[0] /= startPoint.data[3];
			startPoint.data[1] /= startPoint.data[3];
			startPoint.data[2] /= startPoint.data[3];

			endPoint.data[0] /= endPoint.data[3];
			endPoint.data[1] /= endPoint.data[3];
			endPoint.data[2] /= endPoint.data[3];
		}
		else if (startPoint.GetZ() <= -2.0 && endPoint.GetZ() <= -2.0) {
			continue;
		}
		else {
			startPoint = transforsecond * startPoint;
			endPoint = transforsecond * endPoint;

			startPoint.data[0] /= startPoint.data[3];
			startPoint.data[1] /= startPoint.data[3];
			startPoint.data[2] /= startPoint.data[3];

			endPoint.data[0] /= endPoint.data[3];
			endPoint.data[1] /= endPoint.data[3];
			endPoint.data[2] /= endPoint.data[3];
		}

		dc.DrawLine(startPoint.GetX(), startPoint.GetY(), endPoint.GetX(), endPoint.GetY());
	}
}