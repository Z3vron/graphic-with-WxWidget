#include <wx/wx.h>
#include "GUIMyFrame1.h"
// UWAGA: TO JEST JEDYNY PLIK, KTORY NALEZY EDYTOWAC **************************

inline float sheperd (const float d[100][3], const float x, const float y, int N)
{
	float licznik = 0;
	float mianownik = 0;
	float temp_sum = 0;

	for (int i = 0; i < N; i++)
	{
		temp_sum = 1.0 / (fabs (pow ((x - d[i][0]), 2) + pow (y - d[i][1], 2)));
		licznik += temp_sum * d[i][2];
		mianownik += temp_sum;
	}
	return licznik / mianownik;
}

void GUIMyFrame1::DrawMap (int N, float d[100][3], bool Contour, int MappingType, int NoLevels, bool ShowPoints)
{
	wxMemoryDC memDC;
	memDC.SelectObject (MemoryBitmap);
	memDC.SetBackground (*wxWHITE_BRUSH);
	memDC.Clear ();

	// demo.....
	memDC.SetPen (*wxBLACK_PEN);
	memDC.SetBrush (*wxTRANSPARENT_BRUSH);

	if (MappingType == 1) memDC.DrawText ("Mapa niebiesko-czerwona...", wxPoint (10, 30));
	if (MappingType == 2) memDC.DrawText ("Mapa niebiesko-zielono-czerwona...", wxPoint (10, 30));
	if (MappingType == 3) memDC.DrawText ("Mapa szara...", wxPoint (10, 30));

	if (Contour) memDC.DrawText ("Kontury...", wxPoint (10, 10));
	if (ShowPoints) memDC.DrawText ("Punkty...", wxPoint (10, 50));


	float shep_intp[500][500]; // bitmap size
	float min = d[0][2];
	float max = d[0][2];

	for (int i = 0; i < N; i++)
	{
		if (d[i][2] < min)
			min = d[i][2];
		if (d[i][2] > max)
			max = d[i][2];
	}

	for (int i = 0; i < 500; i++)
	{
		for (int j = 0; j < 500; j++)
		{
			shep_intp[i][j] = sheperd (d, static_cast<double>(j) / 100.0 - 2.5, static_cast<double>(-i) / 100.0 + 2.5,
									   N);
		}
	}

	//// Mapping Type Draw ////

	for (int i = 0; i < 500; i++)
	{
		for (int j = 0; j < 500; j++)
		{
			int color = static_cast<int>((shep_intp[j][i] - min)) * (255 / (max - min));

			if (MappingType == 1)
			{
				memDC.SetPen (wxColour (255 - color, 0, color));
				memDC.DrawPoint (j, i);
			}
			else if (MappingType == 2)
			{
				memDC.SetPen (
						wxColor (255 - 2 * color < 0 ? 0 : 255 - 2 * color, color < 128 ? 2 * color : 2 * (255 - color),
								 2 * color - 255 < 0 ? 0 : 2 * color - 255));
				memDC.DrawPoint (j, i);
			}
			else if (MappingType == 3)
			{
				memDC.SetPen (wxColour (color, color, color));
				memDC.DrawPoint (j, i);
			}
		}
	}


	//// Contour Draw ////


	if (Contour)
	{
		for (int i = 0; i < NoLevels; i++)
		{
			float point = min + (i + 1) * (max - min) / (NoLevels + 1.0);

			for (int x = 0; x < 500; x++)
				for (int y = 0; y < 500; y++)
					if (shep_intp[y][x] > point)
					{
						for (int a = -1; a <= 1; a++)
							for (int b = -1; b <= 1; b++)
								if (a && b && (a + y >= 0) && (b + x >= 0) && (a + y < 500) && (b + x < 500) &&
									(shep_intp[a + y][b + x] < point))
									memDC.DrawPoint (y, x);

					}
		}
	}

	//// Point Showing ////

	if (ShowPoints)
	{
		memDC.SetPen (*wxBLACK);
		memDC.SetBrush ((*wxTRANSPARENT_BRUSH));

		for (int i = 0; i < N; i++)
		{
			int x = (d[i][0] + 2.5) * 100;
			int y = (2.5 - d[i][1]) * 100;
			memDC.DrawLine (x, y + 3, x, y - 3);
			memDC.DrawLine (x - 3, y, x + 3, y);
		}
	}

}
