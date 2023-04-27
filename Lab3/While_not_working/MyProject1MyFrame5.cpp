#include "MyProject1MyFrame5.h"

MyProject1MyFrame5::MyProject1MyFrame5(wxWindow *parent)
    : MyFrame5(parent)
{
    Bind(wxEVT_PAINT, &MyProject1MyFrame5::Form_Paint, this);
    MyImage.AddHandler(new wxJPEGHandler);
    m_panel2->SetBackgroundColour(wxColour("white"));
    WxOpenFileDialog1 = new wxFileDialog(this, _("Choose a file"), _(""), _(""), _("*.*"), wxFD_OPEN);
    wxImage perla = wxImage();
    perla.AddHandler(new wxPNGHandler);
    perla.LoadFile("Beer.png", wxBITMAP_TYPE_PNG);
    _perla = wxBitmap(perla);
    polygons = 1;
    color = wxColor("red");
    text = m_textCtrl3->GetLineText(0);
    m_colourPicker3->SetColour(wxColour("red"));
}

void MyProject1MyFrame5::m_button30OnButtonClick(wxCommandEvent &event)
{

    wxFileDialog fileDialog(this, "", "", "", "PNG files (*.png)|*.png|JPG files (*.jpg)|*.jpg", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (fileDialog.ShowModal() == wxID_CANCEL)
        return;
    MyImage = _pic.ConvertToImage();
    MyImage.SaveFile(fileDialog.GetPath());
}
void MyProject1MyFrame5::m_slider2OnScroll(wxScrollEvent &event)
{
    if (m_checkBox1->IsChecked())
    {
        m_gauge2->SetValue(m_slider2->GetValue());
        right_hand_y = -m_slider2->GetValue() + 180;
    }
    else
    {
        m_slider2->SetValue(0);
        event.Skip();
    }
}
void MyProject1MyFrame5::m_checkBox1OnCheckBox(wxCommandEvent &event)
{
    smile_angle = -smile_angle;
    if (!m_checkBox1->IsChecked())
    {
        m_slider2->SetValue(0);
        right_hand_y = 180;
        m_gauge2->SetValue(0);
        _perla_draw_flag = 0;
    }
    else
        _perla_draw_flag = 1;
}

void MyProject1MyFrame5::m_colourPicker3OnColourChanged(wxColourPickerEvent &event)
{
    color = m_colourPicker3->GetColour();
    Refresh();
}

void MyProject1MyFrame5::m_textCtrl3OnText(wxCommandEvent &event)
{
    text = m_textCtrl3->GetLineText(0);
    Refresh();
}

void MyProject1MyFrame5::m_choice4OnChoice(wxCommandEvent &event)
{
    if (m_choice4->GetString(m_choice4->GetSelection()) == "gwiazdka")
    {
        color = m_colourPicker3->GetColour();
        polygons = 1;
        moon = sun = 0;
    }
    else if (m_choice4->GetString(m_choice4->GetSelection()) == "slonce")
    {
        color = wxColour("yellow");
        sun = 1;
        polygons = moon = 0;
    }
    else if (m_choice4->GetString(m_choice4->GetSelection()) == "ksiezyc")
    {
        color = wxColor("silver");
        moon = 1;
        sun = polygons = 0;
    }
    else
        abort();
}
void MyProject1MyFrame5::Form_Paint(wxPaintEvent &event)
{

    wxClientDC DC(m_panel2);
    _pic = wxBitmap(m_panel_x, m_panel_y);

    MyImage = _pic.ConvertToImage();
    wxBufferedDC *MyDC = new wxBufferedDC(&DC, _pic);

    MyDC->Clear();
    MyDC->DrawCircle(300, 50, 40);
    MyDC->DrawLine(300, 90, 300, 250);
    MyDC->DrawLine(300, 250, 270, 300);
    MyDC->DrawLine(300, 250, 330, 300);
    MyDC->DrawEllipticArc(290, 50, 20, 30, 0, smile_angle);
    MyDC->DrawEllipse(275, 30, 20, 10);
    if (m_checkBox1->IsChecked())
        MyDC->DrawEllipse(305, 30, 20, 10);
    else
    {
        MyDC->DrawEllipse(305, 25, 10, 20);
        MyDC->DrawLine(305, 29, 315, 46);
        MyDC->DrawLine(315, 29, 305, 46);
    }
    MyDC->DrawLine(300, 130, 360, 180);
    MyDC->DrawLine(300, 130, right_hand_x, right_hand_y);

    if (_perla_draw_flag)
        MyDC->DrawBitmap(_perla, right_hand_x - 10, right_hand_y - 10);
    if (polygons)
    {
        MyDC->SetBrush(wxBrush(color));
        MyDC->SetPen(wxPen(color));
        wxPoint points[5];
        points[0] = wxPoint(m_panel_x - 130 - 150, m_panel_y - 250 - 130);
        points[1] = wxPoint(m_panel_x - 150 - 150, m_panel_y - 250 - 80);
        points[2] = wxPoint(m_panel_x - 100 - 150, m_panel_y - 250 - 110);
        points[3] = wxPoint(m_panel_x - 160 - 150, m_panel_y - 250 - 110);
        points[4] = wxPoint(m_panel_x - 110 - 150, m_panel_y - 250 - 80);
        MyDC->DrawPolygon(5, points);
    }
    if (moon)
    {
        MyDC->SetPen(wxPen(wxColor(100, 100, 100), 1, wxTRANSPARENT));
        MyDC->SetBrush(wxBrush(wxColor(100, 100, 100), wxSOLID));
        MyDC->DrawCircle(m_panel_x - 280, m_panel_y - 340, 30);
        MyDC->SetBrush(wxBrush(wxColor(255, 255, 255), wxSOLID));
        MyDC->DrawCircle(m_panel_x - 295, m_panel_y - 350, 30);
    }
    if (sun)
    {
        MyDC->SetBrush(*wxYELLOW_BRUSH);
        MyDC->SetPen(*wxYELLOW_PEN);
        MyDC->DrawCircle(m_panel_x - 280, m_panel_y - 350, 30);
    }

    MyDC->DrawText(text, m_panel_x - 250, m_panel_y - 200);
    MyDC->SetFont(wxFont(30, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD));
    MyDC->DrawRotatedText(text, m_panel_x - 100, m_panel_y - 100, 90);

    delete (MyDC);
}
