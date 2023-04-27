

#include <wx/dc.h>
#include <memory>

#include "ChartClass.h"
#include "vecmat.h"
#include <math.h>

ChartClass::ChartClass (std::shared_ptr<ConfigClass>c)
{
	cfg = std::move (c);
	x_step = 200;
}

void ChartClass::Set_Range ()
{
	double xmin = 9999.9, xmax = -9999.9, ymin = 9999.9, ymax = -9999.9;
	double x, y, step;
	int i;

	xmin = cfg->Get_x_start ();
	xmax = cfg->Get_x_stop ();

	step = (cfg->Get_x_stop () - cfg->Get_x_start ()) / (double) x_step;
	x = cfg->Get_x_start ();

	for (i = 0; i <= x_step; i++)
	{
		y = GetFunctionValue (x);
		if (y > ymax) ymax = y;
		if (y < ymin) ymin = y;
		x = x + step;
	}

	y_min = ymin;
	y_max = ymax;
	x_min = xmin;
	x_max = xmax;
}


double ChartClass::GetFunctionValue (double x)
{
	if (cfg->Get_F_type () == 1) return x * x;
	if (cfg->Get_F_type () == 2) return 0.5 * exp (4 * x - 3 * x * x);
	return x + sin (x * 4.0);
}

void ChartClass::Draw (wxDC *dc, int w, int h)
{
	dc->SetBackground (wxBrush (wxColour ("white")));
	dc->Clear ();
	dc->SetPen (wxPen (wxColour ("red")));
	dc->DrawRectangle (10, 10, w - 20, h - 20);
//	dc->DrawText ("Tu trzeba narysowac wykres", wxPoint (20, 20));
	dc->SetClippingRegion (wxRect (10, 10, w - 20, h - 20));

	dc->SetFont (*wxSMALL_FONT);
	dc->SetPen (wxPen (wxColour ("green")));
	Matrix trans_matrix;
	if (cfg->RotateScreenCenter ())
		trans_matrix = Get_Rotate (w, h) * Move_Via_Axis () * Get_Scale (w, h);
	else
		trans_matrix = Move_Via_Axis () * Get_Rotate (w, h) * Get_Scale (w, h);

	// axis drawing


	line2d (trans_matrix, cfg->Get_x_start (), 0, cfg->Get_x_stop (), 0, w, h, dc);
	line2d (trans_matrix, 0, Get_Y_min (), 0, Get_Y_max (), w, h, dc);

	double x_jump = 0.8 + static_cast<int>((cfg->Get_x1 () - cfg->Get_x0 ()) / 10);
	double y_jump = 0.8 + static_cast<int>((cfg->Get_y1 () - cfg->Get_y0 ()) / 10);

	for (double x = x_min; x <= x_max; x += x_jump / 2)
	{
		line2d (trans_matrix, x, -0.05, x, 0.05, w, h, dc);
		line2d (trans_matrix, x, -0.05, x, 0.05, w, h, dc);
		RotateText (dc, trans_matrix, wxString::Format (wxT("%2.1f"), x), x - 0.02, -0.05, w, h);
	}

	line2d (trans_matrix, x_max, 0, x_max - 0.05, 0 + 0.05, w, h, dc);
	line2d (trans_matrix, x_max, 0, x_max - 0.05, 0 - 0.05, w, h, dc);

	for (double y = y_min; y <= y_max; y += y_jump / 2)
	{
		line2d (trans_matrix, -0.05, y, 0.05, y, w, h, dc);
		RotateText (dc, trans_matrix, wxString::Format (wxT("%2.1f"), y), 0.075, y + 0.05, w, h);
	}

	line2d (trans_matrix, 0, y_max, 0 + 0.05, y_max - 0.05, w, h, dc);
	line2d (trans_matrix, 0, y_max, 0 - 0.05, y_max - 0.05, w, h, dc);


	// end of axis drawing



	dc->SetPen (wxPen (wxColour ("blue")));

	double step = (cfg->Get_x1 () - cfg->Get_x0 ()) / x_step;
	for (double x{cfg->Get_x_start ()}; x < cfg->Get_x_stop (); x += step)
		line2d (trans_matrix, x, GetFunctionValue (x), x + step, GetFunctionValue (x + step), w, h, dc);

}

void ChartClass::line2d (Matrix t, double x1, double y1, double x2, double y2, int w, int h, wxDC *dc)
{
	// ...... cos .......
	Vector start, end;

	start.data[0] = x1;
	start.data[1] = y1;
	start.data[2] = 1;

	end.data[0] = x2;
	end.data[1] = y2;
	end.data[2] = 1;

	start = t * start;
	end = t * end;

	dc->DrawLine (static_cast<wxCoord>(start.GetX ()), static_cast<wxCoord>(h - start.GetY ()), static_cast<wxCoord>(end.GetX ()),
				  static_cast<wxCoord>(h - end.GetY ()));
}

double ChartClass::Get_Y_min ()
{
	Set_Range ();
	return y_min;
}

double ChartClass::Get_Y_max ()
{
	Set_Range ();
	return y_max;
}

Matrix ChartClass::Get_Rotate (int w, int h)
{
	Matrix temp_object;
	double cosinus = cos (cfg->Get_Alpha ());
	double sinus = sin (cfg->Get_Alpha ());
	temp_object.data[0][0] = cosinus;
	temp_object.data[0][1] = sinus;
	temp_object.data[1][0] = -sinus;
	temp_object.data[1][1] = cosinus;

	if (cfg->RotateScreenCenter ())
	{
		temp_object.data[0][2] = (w / 2.0) * (1 - cosinus) + (h / 2.0) * (-sinus);
		temp_object.data[1][2] = (w / 2.0) * sinus + (h / 2.0) * (1 - cosinus);
	}

	else
	{
		Matrix tmp = Get_Scale (w, h);
		temp_object.data[0][2] = tmp.data[0][2] * (1 - cosinus) + tmp.data[1][2] * (-sinus);
		temp_object.data[1][2] = tmp.data[0][2] * sinus + tmp.data[1][2] * (1 - cosinus);
	}
	return temp_object;
}

Matrix ChartClass::Get_Scale (int w, int h)
{
	Matrix temp_object;
	double Sx, Sy;

	Sx = (w - x_min) / (cfg->Get_x1 () - cfg->Get_x0 ());
	Sy = (h - y_min) / (cfg->Get_y1 () - cfg->Get_y0 ());

	temp_object.data[0][0] = Sx;
	temp_object.data[0][2] = x_min - Sx * cfg->Get_x0 ();
	temp_object.data[1][1] = Sy;
	temp_object.data[1][2] = y_min - Sy * cfg->Get_y0 ();

	return temp_object;

}

Matrix ChartClass::Move_Via_Axis ()
{
	Matrix temp_object;

	temp_object.data[0][0] = temp_object.data[1][1] = 1;
	temp_object.data[0][2] = cfg->Get_dX ();
	temp_object.data[1][2] = cfg->Get_dY ();

	return temp_object;

}

void ChartClass::RotateText (wxDC *DC, Matrix trans_matrix, wxString str, double x, double y, int w, int h)
{
	Vector vector;
	vector.Set (x, y);
	vector = trans_matrix * vector;
	DC->DrawRotatedText (str, static_cast<wxCoord>(vector.GetX ()), static_cast<wxCoord>(h - vector.GetY ()), -cfg->Get_Alpha ());
   
}
