#include "stdafx.h"
#include "form1.h"


namespace XILGNET30alpha {



System::Void Form1::tabPage2_Enter(System::Object^  sender, System::EventArgs^  e) 
{
	LoadPreview();
}


System::Void Form1::fontDialog1_Apply(System::Object^  sender, System::EventArgs^  e) 
{
	header_font_label->Font = fontDialog1->Font;
	header_font_label->ForeColor = fontDialog1->Color;

	SetHeaderStyles();
	LoadPreview();
}

System::Void Form1::fontDialog2_Apply(System::Object^  sender, System::EventArgs^  e) 
{
	caption_font_label->Font = fontDialog2->Font;
	caption_font_label->ForeColor = fontDialog2->Color;

	SetBodyStyles();
	LoadPreview();
}

System::Void Form1::SetBodyStyles()
{
	body_font_size = Convert::ToString(fontDialog2->Font->SizeInPoints);
	body_font_size += L"pt";
	body_font = L"\'" + fontDialog2->Font->Name + L"\'";
	
	String^ tc = String::Empty;
	body_font_color = tc->Format(L"#{0:X2}{1:X2}{2:X2}",fontDialog2->Color.R,fontDialog2->Color.G,fontDialog2->Color.B);
	
	body_font_weight = L"normal";
	body_font_style = L"normal";
	if (fontDialog2->Font->Bold)
		body_font_weight = L"bold";
	if (fontDialog2->Font->Italic)
		body_font_style = L"italic";

	b_text_decoration = String::Empty;
	String^ temp = String::Empty;
	String^ temp1 = String::Empty;
	String^ temp2 = String::Empty;
	if(fontDialog2->Font->Strikeout)
	{
		body_strike = L"line-through";
		temp1 = L" line-through ";
	}
	if(fontDialog2->Font->Underline)
	{
		body_underline = L"underline";
		temp2 = L" underline ";
	}
	temp = temp1+temp2;

	if (temp != String::Empty)
		b_text_decoration = L"; text-decoration:" + temp;
}

System::Void Form1::SetHeaderStyles()
{
	header_font_size = Convert::ToString(fontDialog1->Font->SizeInPoints);
	header_font_size += L"pt";
	header_font = L"\'" + fontDialog1->Font->Name + L"\'";
	
	String^ tc = String::Empty;
	header_font_color = tc->Format(L"#{0:X2}{1:X2}{2:X2}",fontDialog1->Color.R,fontDialog1->Color.G,fontDialog1->Color.B);
	
	header_font_weight = L"normal";
	header_font_style = L"normal";
	if (fontDialog1->Font->Bold)
		header_font_weight = L"bold";
	if (fontDialog1->Font->Italic)
		header_font_style = L"italic";

	h_text_decoration = String::Empty;
	String^ temp = String::Empty;
	String^ temp1 = String::Empty;
	String^ temp2 = String::Empty;
	if(fontDialog1->Font->Strikeout)
	{
		header_strike = L"line-through";
		temp1 = L" line-through ";
	}
	if(fontDialog1->Font->Underline)
	{
		header_underline = L"underline";
		temp2 = L" underline ";
	}
	temp = temp1+temp2;

	if (temp != String::Empty)
		h_text_decoration = L"; text-decoration:" + temp;
}


} // END OF NAMESPACE
