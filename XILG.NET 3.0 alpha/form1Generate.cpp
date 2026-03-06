#include "stdafx.h"
#include "form1.h"
#include "progress_dialog.h"
#include "Results.h"


namespace XILGNET30alpha {

System::Void Form1::build_website_Click([[maybe_unused]] System::Object^  sender, [[maybe_unused]] [[maybe_unused]] System::EventArgs^  e)
{
	// finalise all our sheets!
	finalise_input_folders_tab();
	finalise_background_tab();
	finalise_watermark_tab();
	finalise_settings_tab();

	CLProxy^ parameters = gcnew CLProxy;
	
	if (SetParameters(parameters))
	{
		progress_dialog^ pd = gcnew progress_dialog;
		pd->LoadParameters(parameters);
		pd->ShowDialog();

		button_view_website->Enabled = true;

		Results^ res = gcnew Results;
		res->LoadParameters(parameters);
		res->ShowDialog();
	}
}


position Form1::WatermarkPos()
{
	auto p = position::bad_pos;

	if (topleft->Checked)
		p = position::tl;
	if (centerright->Checked)
		p = position::cr;
	if (topcenter->Checked)
		p = position::tc;
	if (this->middle->Checked)
		p = position::center;
	if (topright->Checked)
		p = position::tr;
	if (bottomright->Checked)
		p = position::br;
	if (centerleft->Checked)
		p = position::lc;
	if (bottomleft->Checked)
		p = position::bl;
	if (bottomcenter->Checked)
		p = position::bc;

	return p;
}

System::Boolean Form1::SetParameters(CLProxy^ parameters)
{
	parameters->acolor = body_font_color;
	parameters->afont = body_font;
	parameters->asize = body_font_size;
	parameters->astyle = body_font_style;
	parameters->aweight = body_font_weight;
	parameters->astrike = body_strike;
	parameters->aunderline = body_underline;
	parameters->create_path = true;
	parameters->internal_css = internal_css;
	parameters->default_css = user_css;
	parameters->h1color = header_font_color;
	parameters->h1font = header_font;
	parameters->h1size = header_font_size;
	parameters->h1style = header_font_style;	
	parameters->h1weight = header_font_weight;
	parameters->h1strike = header_strike;
	parameters->h1underline = header_underline;
	parameters->html_background_color = body_color;
	parameters->no_html = no_html;
	parameters->only_html = only_html;
	parameters->no_caption = !caption_enabled;
	parameters->recurse = include_subfolders;

	if (banner_image_enabled)
	{
		if (System::IO::File::Exists(image_banner))
		{
			parameters->banner = image_banner;
			Bitmap^ img = gcnew Bitmap(image_banner);
			parameters->banner_height = img->Height;
		}
		else
		{
			MessageBox::Show(L"Banner image enabled\nbut no valid image selected!",
								L"XILG has found a problem",
								MessageBoxButtons::OK, 
								MessageBoxIcon::Exclamation);
			return false;
		}
	}
	else
	{
		parameters->banner = String::Empty;
		parameters->banner_height = 0;
	}

	if (user_css)
	{
		if (System::IO::File::Exists(CSSfilename->Text))
		{
			parameters->usercss = CSSfilename->Text;
		}
		else
		{
			MessageBox::Show(L"User CSS enabled\nbut no CSS file selected!",
								L"XILG has found a problem",
								MessageBoxButtons::OK, 
								MessageBoxIcon::Exclamation);
			return false;
		}
	}
	else
	{
		parameters->usercss = String::Empty;
	}

	if (background_image_enabled)
	{
		if (System::IO::File::Exists(image_background))
		{
			parameters->html_background_image = image_background;
			parameters->html_background_image_position = image_background_position;
			parameters->html_background_image_repeat = Form1::image_background_repeat;
		}
		else
		{
			MessageBox::Show(L"Background image enabled\nbut no valid image selected!",
								L"XILG has found a problem",
								MessageBoxButtons::OK, 
								MessageBoxIcon::Exclamation);
			return false;
		}
	}
	else
	{
		parameters->html_background_image = String::Empty;
		parameters->html_background_image_position = String::Empty;
		parameters->html_background_image_repeat = String::Empty;
	}
	
	if (multipage_enabled) 
	{
		parameters->pics_per_page = Decimal::ToInt32(numericUpDown4->Value);
	}
	else
	{
		parameters->pics_per_page = 0;
	}

	if (page_title_enabled)
	{
		parameters->page_title = page_title;
		parameters->no_title = false;
	}
	else
	{
		parameters->no_title = true;
	}

	if (watermark_enabled)
	{
		if (System::IO::File::Exists(WaterMarkImageName->Text))
		{
			parameters->water_mark = WaterMarkImageName->Text;
			parameters->wm_alpha = Decimal::ToSingle(WaterMarkOpacity->Value);
			parameters->wm_scale = Decimal::ToSingle(WaterMarkScale->Value);
			parameters->pos = WatermarkPos();
		}
		else
		{
			MessageBox::Show(L"Watermark image enabled\nbut no valid image selected!",
								L"XILG has found a problem",
								MessageBoxButtons::OK, 
								MessageBoxIcon::Exclamation);
			return false;
		}
	}
	else
	{
		parameters->water_mark = String::Empty;
		parameters->pos = position::bl;
	}

	if (!PassFoldersToParameter(parameters))
	{
		MessageBox::Show(L"No input folders selected!",
							L"XILG has found a problem",
							MessageBoxButtons::OK, 
							MessageBoxIcon::Exclamation);
		return false;
	}

	if (project == String::Empty)
	{
		MessageBox::Show(L"Please choose a project name!",
							L"XILG has found a problem",
							MessageBoxButtons::OK, 
							MessageBoxIcon::Exclamation);
		return false;
	}
	else
	{
		parameters->project_name = project;	
	}

	if (textBox1->Text != String::Empty)
	{
		parameters->output_path = textBox1->Text;
	}
	else
	{
		MessageBox::Show(L"Please choose a destination folder!",
							L"XILG has found a problem",
							MessageBoxButtons::OK, 
							MessageBoxIcon::Exclamation);
		return false;
	}
	return true;
}

bool Form1::PassFoldersToParameter(CLProxy^ cl)
{
	for (int count = 0; count < listBox1->Items->Count; count++)
	{
		String^ st = listBox1->Items[count]->ToString();
			//listBox1->Items[count]->ToString();
		
		cl->input_paths->Add(st);
	}

	return true;
}


} // END OF NAMESPACE
