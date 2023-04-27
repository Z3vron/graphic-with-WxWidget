#include "GUIMyFrameMyFrame1.h"

GUIMyFrameMyFrame1::GUIMyFrameMyFrame1 (wxWindow *parent)
		:
		MyFrame1 (parent)
{

}


void GUIMyFrameMyFrame1::m_button1OnButtonClick (wxCommandEvent &event)
{
	wxInitAllImageHandlers ();
	wxClientDC DC (m_panel1);

	wxFileDialog *file_dialog = new wxFileDialog (this, "Load file", "", "", wxT("to jpg (*.jpg)|*.jpg"),
												  wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	file_dialog->ShowModal ();

	std::string file_info ("Rozmiar obrazka: ");

	m_image->LoadFile (file_dialog->GetPath (), wxBITMAP_TYPE_JPEG);


	FIBITMAP *F_obj = FreeImage_Load (FIF_JPEG, file_dialog->GetPath (), JPEG_DEFAULT);
	FITAG *tagMake = NULL;

	file_info += std::to_string (FreeImage_GetWidth (F_obj)) + " x " + std::to_string (FreeImage_GetHeight (F_obj)) +
				 "\n__EXIF Info__:\n";

	FreeImage_GetMetadata (FIMD_EXIF_MAIN, F_obj, "Artist", &tagMake);
	file_info += std::string ("Artist: ") + std::string ((FreeImage_TagToString (FIMD_EXIF_MAIN, tagMake))) +
				 std::string ("\n");

	FreeImage_GetMetadata (FIMD_EXIF_MAIN, F_obj, "Copyright", &tagMake);
	file_info += std::string ("Copyright: ") + FreeImage_TagToString (FIMD_EXIF_MAIN, tagMake) + std::string ("\n");

	FreeImage_GetMetadata (FIMD_EXIF_MAIN, F_obj, "ResolutionUnit", &tagMake);
	file_info +=
			std::string ("Resolution Unit: ") + FreeImage_TagToString (FIMD_EXIF_MAIN, tagMake) + std::string ("\n");

	FreeImage_GetMetadata (FIMD_EXIF_MAIN, F_obj, "XResolution", &tagMake);
	file_info += std::string ("XResolution: ") + FreeImage_TagToString (FIMD_EXIF_MAIN, tagMake) + std::string ("\n");

	FreeImage_GetMetadata (FIMD_EXIF_MAIN, F_obj, "YCbCrPositioning", &tagMake);
	file_info +=
			std::string ("YCbCrPositioning: ") + FreeImage_TagToString (FIMD_EXIF_MAIN, tagMake) + std::string ("\n");

	FreeImage_GetMetadata (FIMD_EXIF_MAIN, F_obj, "YResolution", &tagMake);
	file_info += std::string ("YResolution: ") + FreeImage_TagToString (FIMD_EXIF_MAIN, tagMake);

	FreeImage_Unload (F_obj);

	m_richText5->SetValue (file_info);

	refresh (DC);

}

void GUIMyFrameMyFrame1::m_button2OnButtonClick (wxCommandEvent &event)
{
	wxClientDC DC (m_panel1);

	int height = 0.1 * m_image->GetHeight ();
	int width = 0.2 * m_image->GetWidth ();
	int x_start = 0.55 * m_image->GetWidth ();
	int y_start = 0.05 * m_image->GetHeight ();

	cimg_library::CImg<unsigned char> cImg (width, height, 1, 3);

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			cImg (i, j, 0) = m_image->GetRed (x_start + i, y_start + j);
			cImg (i, j, 1) = m_image->GetGreen (x_start + i, y_start + j);
			cImg (i, j, 2) = m_image->GetBlue (x_start + i, y_start + j);
		}
	}
	cImg.blur (2.5);

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			m_image->SetRGB (x_start + i, y_start + j, cImg (i, j, 0), cImg (i, j, 1), cImg (i, j, 2));
		}
	}

	refresh (DC);
}

void GUIMyFrameMyFrame1::m_erode (wxCommandEvent &event)
{
	wxClientDC DC (m_panel1);

	int height = m_image->GetHeight ();
	int width = m_image->GetWidth ();

	cimg_library::CImg<unsigned char> cImg (width, height, 1, 3);

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			cImg (i, j, 0) = m_image->GetRed (i, j);
			cImg (i, j, 1) = m_image->GetGreen (i, j);
			cImg (i, j, 2) = m_image->GetBlue (i, j);
		}
	}
	cImg.erode (5, 10);

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			m_image->SetRGB (i, j, cImg (i, j, 0), cImg (i, j, 1), cImg (i, j, 2));
		}
	}
	refresh (DC);

}

void GUIMyFrameMyFrame1::m_animacja (wxCommandEvent &event)
{
// TODO: Implement m_animacja
}

void GUIMyFrameMyFrame1::refresh (wxClientDC &dc)
{
	wxBufferedDC buff (&dc);

	auto *temp = new wxImage (*m_image);
	if (temp->Ok ())
	{
		temp->Rescale (dc.GetSize ().x, dc.GetSize ().y);
		wxBitmap bitmap (*temp);
		buff.DrawBitmap (bitmap, 0, 0);
	}
	delete temp;
}

void GUIMyFrameMyFrame1::MyFrame1OnUpdateUI (wxUpdateUIEvent &event)
{
	wxClientDC dc (m_panel1);
	refresh (dc);
}



