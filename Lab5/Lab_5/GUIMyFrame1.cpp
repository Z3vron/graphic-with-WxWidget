#include "GUIMyFrame1.h"
#include <vector>
#include <fstream>
//#include "vecmat.h"

struct Point
{
	float x, y, z;

	Point (float _x, float _y, float _z) : x (_x), y (_y), z (_z)
	{}
};

struct Color
{
	int R, G, B;

	Color (int _R, int _G, int _B) : R (_R), G (_G), B (_B)
	{}
};

struct Segment
{
	Point begin, end;
	Color color;

	Segment (Point _begin, Point _end, Color _color) : begin (_begin), end (_end), color (_color)
	{}
};

std::vector<Segment> data;

GUIMyFrame1::GUIMyFrame1 (wxWindow *parent)
		:
		MyFrame1 (parent)
{
	m_button_load_geometry->SetLabel (_("Wczytaj Geometri\u0119"));
	m_staticText25->SetLabel (_("Obr\u00F3t X:"));
	m_staticText27->SetLabel (_("Obr\u00F3t Y:"));
	m_staticText29->SetLabel (_("Obr\u00F3t Z:"));

	WxSB_TranslationX->SetRange (0, 200);
	WxSB_TranslationX->SetValue (100);
	WxSB_TranslationY->SetRange (0, 200);
	WxSB_TranslationY->SetValue (100);
	WxSB_TranslationZ->SetRange (0, 200);
	WxSB_TranslationZ->SetValue (100);

	WxSB_RotateX->SetRange (0, 360);
	WxSB_RotateX->SetValue (0);
	WxSB_RotateY->SetRange (0, 360);
	WxSB_RotateY->SetValue (0);
	WxSB_RotateZ->SetRange (0, 360);
	WxSB_RotateZ->SetValue (0);

	WxSB_ScaleX->SetRange (1, 200);
	WxSB_ScaleX->SetValue (100);
	WxSB_ScaleY->SetRange (1, 200);
	WxSB_ScaleY->SetValue (100);
	WxSB_ScaleZ->SetRange (1, 200);
	WxSB_ScaleZ->SetValue (100);
}

void GUIMyFrame1::WxPanel_Repaint (wxUpdateUIEvent &event)
{
	Repaint ();
}

Matrix4 GUIMyFrame1::center ()
{
	Matrix4 temp_matrix;

	for (int i = 0; i < 3; i++)
		temp_matrix.data[i][i] = 1.0;

	temp_matrix.data[0][3] = 0.5;
	temp_matrix.data[1][3] = 0.5;

	return temp_matrix;
}

Matrix4 GUIMyFrame1::rotate_x (double rotation)
{
	Matrix4 temp_matrix;
	double alpha = (rotation * M_PI) / 180.0;

	temp_matrix.data[0][0] = 1;
	temp_matrix.data[1][1] = cos (alpha);
	temp_matrix.data[1][2] = -sin (alpha);
	temp_matrix.data[2][1] = sin (alpha);
	temp_matrix.data[2][2] = cos (alpha);

	return temp_matrix;

}

Matrix4 GUIMyFrame1::rotate_y (double rotation)
{
	double alpha = (rotation * M_PI) / 180.0;
	Matrix4 temp_matrix;
	temp_matrix.data[0][0] = cos (alpha);
	temp_matrix.data[0][2] = -sin (alpha);
	temp_matrix.data[1][1] = 1.0;
	temp_matrix.data[2][0] = sin (alpha);
	temp_matrix.data[2][2] = cos (alpha);

	return temp_matrix;
}

Matrix4 GUIMyFrame1::rotate_z (double rotation)
{
	double alpha = (rotation * M_PI) / 180.0;
	Matrix4 temp_matrix;
	temp_matrix.data[0][0] = cos (alpha);
	temp_matrix.data[0][1] = -sin (alpha);
	temp_matrix.data[1][0] = sin (alpha);
	temp_matrix.data[1][1] = cos (alpha);
	temp_matrix.data[2][2] = 1.0;

	return temp_matrix;

}

Matrix4 GUIMyFrame1::scale (double x, double y, double z)
{
	Matrix4 temp_matrix;
	temp_matrix.data[0][0] = x;
	temp_matrix.data[1][1] = -y;
	temp_matrix.data[2][2] = z;
	return temp_matrix;
}

Matrix4 GUIMyFrame1::translate (double x, double y, double z)
{
	Matrix4 temp_matrix;
	for (int i = 0; i < 3; i++)
		temp_matrix.data[i][i] = 1.0;

	temp_matrix.data[0][3] = x;
	temp_matrix.data[1][3] = -y;
	temp_matrix.data[2][3] = z;
	return temp_matrix;
}

void GUIMyFrame1::m_button_load_geometry_click (wxCommandEvent &event)
{
	wxFileDialog WxOpenFileDialog (this, wxT("Choose a file"), wxT(""), wxT(""), wxT("Geometry file (*.geo)|*.geo"),
								   wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (WxOpenFileDialog.ShowModal () == wxID_OK)
	{
		double x1, y1, z1, x2, y2, z2;
		int r, g, b;

		std::ifstream in (WxOpenFileDialog.GetPath ().ToStdString() );
		if (in.is_open ())
		{
			data.clear ();
			while (!in.eof ())
			{
				in >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> r >> g >> b;
				data.push_back (Segment (Point (x1, y1, z1), Point (x2, y2, z2), Color (r, g, b)));
			}
			in.close ();
		}
	}
}

void GUIMyFrame1::Scrolls_Updated (wxScrollEvent &event)
{
	WxST_TranslationX->SetLabel (wxString::Format (wxT("%g"), (WxSB_TranslationX->GetValue () - 100) / 50.0));
	WxST_TranslationY->SetLabel (wxString::Format (wxT("%g"), (WxSB_TranslationY->GetValue () - 100) / 50.0));
	WxST_TranslationZ->SetLabel (wxString::Format (wxT("%g"), (WxSB_TranslationZ->GetValue () - 100) / 50.0));

	WxST_RotateX->SetLabel (wxString::Format (wxT("%d"), WxSB_RotateX->GetValue ()));
	WxST_RotateY->SetLabel (wxString::Format (wxT("%d"), WxSB_RotateY->GetValue ()));
	WxST_RotateZ->SetLabel (wxString::Format (wxT("%d"), WxSB_RotateZ->GetValue ()));

	WxST_ScaleX->SetLabel (wxString::Format (wxT("%g"), WxSB_ScaleX->GetValue () / 100.0));
	WxST_ScaleY->SetLabel (wxString::Format (wxT("%g"), WxSB_ScaleY->GetValue () / 100.0));
	WxST_ScaleZ->SetLabel (wxString::Format (wxT("%g"), WxSB_ScaleZ->GetValue () / 100.0));


	Repaint ();
}


void GUIMyFrame1::Repaint ()
{
// tu rysowac

	wxClientDC DC (WxPanel);
	wxBufferedDC BufferedDC (&DC);
	int width;
	int height;
	WxPanel->GetSize (&width, &height);
	BufferedDC.SetBackground (wxBrush (wxColour ("white")));
	BufferedDC.Clear ();


	Matrix4 Scale (scale (WxSB_ScaleX->GetValue () / 100.0, WxSB_ScaleY->GetValue () / 100.0,
						  WxSB_ScaleZ->GetValue () / 100.0));
	Matrix4 Rotate_via_x (rotate_x (WxSB_RotateX->GetValue ()));
	Matrix4 Rotate_via_y (rotate_y (WxSB_RotateY->GetValue ()));
	Matrix4 Rotate_via_z (rotate_z (WxSB_RotateZ->GetValue ()));
	Matrix4 Rotate (Rotate_via_x * Rotate_via_y * Rotate_via_z);
	Matrix4 Translate (
			translate ((WxSB_TranslationX->GetValue () - 100.0) / 50.0, (WxSB_TranslationY->GetValue () - 100.0) / 50.0,
					   (WxSB_TranslationZ->GetValue () - 100.0) / 50.0 + 2));
	Matrix4 Center (center ());
	Matrix4 AllInOne (Translate * Rotate * Scale);


	for (int i = 0; i < static_cast<int>(data.size ()); i++)
	{

		Vector4 begin, end;
		begin.Set (data[i].begin.x, data[i].begin.y, data[i].begin.z);
		begin = AllInOne * begin;
		begin.Set (begin.GetX () / begin.GetZ (), begin.GetY () / begin.GetZ (), begin.GetZ ());
		begin = Center * begin;
		end.Set (data[i].end.x, data[i].end.y, data[i].end.z);
		end = AllInOne * end;
		end.Set (end.GetX () / end.GetZ (), end.GetY () / end.GetZ (), end.GetZ ());
		end = Center * end;
	}

}