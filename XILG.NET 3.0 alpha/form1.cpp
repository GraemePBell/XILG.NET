#include "stdafx.h"
#include "form1.h"
#include "Results.h"

bool diagnostic = false;

namespace XILGNET30alpha {

System::Void Form1::Form1_Load([[maybe_unused]] System::Object^  sender, [[maybe_unused]] [[maybe_unused]] System::EventArgs^  e)
{
	LoadDefaults();

	LoadInitialFolder();
	LoadSettingsPage();
}


System::Void Form1::LoadDefaults()
{
	// INPUT FOLDERS TAB
	ln = gcnew LocalNames;

	desktop_folder = Environment::GetFolderPath(Environment::SpecialFolder::DesktopDirectory);
	my_computer_folder = "All Folders!";
	my_documents_folder = Environment::GetFolderPath(Environment::SpecialFolder::MyDocuments);
	my_pictures_folder = Environment::GetFolderPath(Environment::SpecialFolder::MyPictures);

	includeSubfoldersToolStripMenuItem->Checked = false;
	auto_inc_sub_check->Checked = false;
	include_subfolders = false;

	// SETTINGS TAB
	
	page_title = Environment::UserName;
	page_title += L"\'s Pictures";
	page_title_enabled = true;

	project =  L"My New Website";
	project_name_enabled = true;

	internal_css = false;

	user_css = false;
	EnableUserCSSCheck->Checked = false;
	CSSfilename->Text = String::Empty;

	xml_plus_html->Checked = true;
	only_html = false;
	no_html = false;

	enable_header_check->Checked = true;
	header_enabled = true;

	enable_caption_check->Checked = true;
	caption_enabled = true;

	enable_multipage_check->Checked = false;
	multipage_enabled = false;

	Drawing::Font^ def_h_font = gcnew Drawing::Font(L"Times New Roman",26.25F);
	header_font_label->Enabled = true;
	header_font_panel->BackColor = Color::Silver;
	headingFontToolStripMenuItem->Enabled = true;
	header_font_label->ForeColor = Color::Black;
	header_font_label->Font = def_h_font;

	Drawing::Font^ def_b_font = (gcnew System::Drawing::Font(L"Tahoma", 10));
	caption_font_label->Enabled = true;
	caption_font_panel->BackColor = Color::Silver;
	bodyFontToolStripMenuItem->Enabled = true;
	caption_font_label->ForeColor = Color::Black;
	caption_font_label->Font = def_b_font;


	// BACKGROUND TAB

	EnableBackgroundImageCheck->Checked = false;
	background_image_enabled = false;
	v_h_tiling->Checked = true;
	textBox4->Text = String::Empty;
	top->Checked = true;
	left->Checked = true;
	image_background_settings = String::Empty;
	image_background_repeat = L"repeat";
	image_background_position = String::Empty;

	EnableBannerImageCheck->Checked = false;
	banner_image_enabled = false;
	textBox5->Text = String::Empty;

	// WATERMARK TAB

	enable_watermark_check->Checked = false;
	watermark_enabled = false;
	WaterMarkImageName->Text = String::Empty;
	WaterMarkOpacity->Value = Decimal(0.2);
	WaterMarkScale->Value = Decimal(0.2);

	// PREVIEW TAB

	image_banner		= String::Empty;
	image_background	= String::Empty;
	image_thumb1		= L"\"res://xilg.exe/#2/#104\"";
	image_thumb2		= L"\"res://xilg.exe/#2/#106\"";
	image_thumb3		= L"\"res://xilg.exe/#2/#105\"";
	image_thumb4		= L"\"res://xilg.exe/#2/#107\"";
	image_thumb5		= L"\"res://xilg.exe/#2/#108\"";
	image_thumb6		= L"\"res://xilg.exe/#2/#109\"";

	header_font			= L"serif";
	header_font_size	= L"24pt";
	header_font_weight	= L"bold";
	header_font_color	= L"black";
	header_font_style	= L"normal";

	body_font			= L"sans-serif";
	body_font_size		= L"10pt";;
	body_font_weight	= L"bold";
	body_font_color		= L"black";
	body_font_style		= L"normal";

	body_color			= L"silver";
	back_color			= Color::Silver;
	color_picker_panel->BackColor = Color::Silver;
	header_font_panel->BackColor = Color::Silver;
	caption_font_panel->BackColor = Color::Silver;

	h_text_decoration	= String::Empty; 
	b_text_decoration	= String::Empty; 

	header_strike	= String::Empty;
	body_strike	= String::Empty;

	header_underline	= String::Empty;
	body_underline	= String::Empty;

}


System::Void Form1::LoadInitialFolder()
{
	treeView1->Nodes->Add(my_pictures_folder,ln->MyPictures(),8,8);
	treeView1->Nodes->Add(my_documents_folder,ln->MyDocuments(),5,5);
	treeView1->Nodes->Add(desktop_folder,ln->Desktop(),0);
	treeView1->Nodes->Add(my_computer_folder,ln->MyComputer(),1,1);
	treeView1->SelectedNode = treeView1->TopNode;
}



System::Void Form1::button1_Click([[maybe_unused]] System::Object^  sender, [[maybe_unused]] [[maybe_unused]] System::EventArgs^  e)
{
	Close();
}

System::Void Form1::button_view_website_Click([[maybe_unused]] System::Object^  sender, [[maybe_unused]] [[maybe_unused]] System::EventArgs^  e)
{
	CLProxy^ parameters = gcnew CLProxy;
	
	if (SetParameters(parameters))
	{
		Results^ res = gcnew Results;
		res->LoadParameters(parameters);
		res->ShowDialog();
	}
}


} // END NAMESPACE