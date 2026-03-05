#include "stdafx.h"
#include "form1.h"


namespace XILGNET30alpha {


System::Void Form1::LoadSettingsPage()
{
	textBox1->Text = my_documents_folder;
	webpage_title_text->Text = page_title;
	project_name->Text = project;
	enable_watermark_check->Checked = false;
	default_size->Checked = true;
	custom_size->Checked = false;
	numericUpDown1->Enabled = false;
	numericUpDown1->Value = 100;
	numericUpDown1->Maximum = 1000;
	numericUpDown1->Minimum = 10;
	WaterMarkOpacity->Enabled = false;
	WaterMarkOpacity->Maximum = Decimal(1.0);
	WaterMarkOpacity->Minimum = Decimal(0.01);
	WaterMarkOpacity->DecimalPlaces = 2;
	WaterMarkOpacity->Value = Decimal(0.2);
	WaterMarkScale->Enabled = false;
	WaterMarkScale->Maximum = Decimal(1.0);
	WaterMarkScale->Minimum = Decimal(0.01);
	WaterMarkScale->DecimalPlaces = 2;
	WaterMarkScale->Value = Decimal(0.2);

	button8->Enabled = false;
	
	WaterMarkImageName->Enabled = false;
	bottomright->Visible = false;
	bottomcenter->Visible = false;
	bottomleft->Visible = false;
	centerright->Visible = false;
	middle->Visible = false;
	centerleft->Visible = false;
	topright->Visible = false;
	topcenter->Visible = false;
	topleft->Visible = false;
	bottomright->Checked = true;

	enable_multipage_check->Checked = false;
	label10->Enabled = false;
	numericUpDown4->Enabled = false;
	numericUpDown4->Value = Decimal(16);

}


System::Void Form1::textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	page_title = webpage_title_text->Text;
}


System::Void Form1::button5_Click(System::Object^  sender, System::EventArgs^  e) 
{
	String^ mdf;
	if (IO::Directory::Exists(textBox1->Text))
		mdf = textBox1->Text;
	else
		mdf = my_documents_folder;
		
	
	folderBrowserDialog1->RootFolder = Environment::SpecialFolder::Desktop;
	folderBrowserDialog1->SelectedPath = mdf;
	folderBrowserDialog1->ShowDialog();
	destination_folder = folderBrowserDialog1->SelectedPath;
	textBox1->Text = destination_folder;
	toolTip1->SetToolTip(textBox1, destination_folder);

}

System::Void Form1::default_size_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
{
	if (default_size->Checked)
	{
		custom_size->Checked = false;
		numericUpDown1->Enabled = false;
		numericUpDown1->Value = 100;
	}
}

System::Void Form1::custom_size_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
{
	if (custom_size->Checked)
	{
		default_size->Checked = false;
		numericUpDown1->Enabled = true;
	}
}


System::Void Form1::enable_multipage_check_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
{
	if(enable_multipage_check->Checked)
	{
		multipage_enabled = true;
		label10->Enabled = true;
		numericUpDown4->Enabled = true;
		multipage_enabled = true;
	}
	else
	{
		multipage_enabled = false;
		label10->Enabled = false;
		numericUpDown4->Enabled = false;
		multipage_enabled = false;
	}
}


System::Void Form1::xml_plus_html_Clicked(System::Object^  sender, System::EventArgs^  e) 
{
	if (xml_plus_html->Checked)
	{
		only_html = false;
		no_html = false;
	}
	if (xml_only->Checked)
	{
		only_html = false;
		no_html = true;
	}
	if (xhtml_only->Checked)
	{
		only_html = true;
		no_html = false;
	}
}

System::Void Form1::enable_header_check_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
{
	if (enable_header_check->Checked)
	{
		header_enabled = true;

		header_font_label->Text = L"Choose title font";
		header_font_label->Enabled = true;
		header_enabled = true;
		header_font_panel->BackColor = back_color;
		headingFontToolStripMenuItem->Enabled = true;
	}
	else
	{
		header_enabled = false;

		header_font_label->Text = L"No Page Title";
		header_font_label->Enabled = false;
		header_enabled = false;
		header_font_panel->BackColor = Color::Transparent;
		headingFontToolStripMenuItem->Enabled = false;
	}
}

System::Void Form1::enable_caption_check_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
{
	if (enable_caption_check->Checked)
	{
		caption_enabled = true;

		caption_font_label->Text = L"Choose caption font";
		caption_font_label->Enabled = true;
		caption_enabled = true;
		caption_font_panel->BackColor = back_color;
		bodyFontToolStripMenuItem->Enabled = true;
	}
	else
	{
		caption_enabled = false;

		caption_font_label->Text = L"No captions";
		caption_font_label->Enabled = false;
		caption_enabled = false;
		caption_font_panel->BackColor = Color::Transparent;
		bodyFontToolStripMenuItem->Enabled = false;
	}
}

System::Void Form1::project_name_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	String^ my_title = project_name->Text->Trim(L' ');

	if (my_title != String::Empty)
		this->Text = my_title + L" - XILG";
	else
		this->Text = L"XILG";

	project = project_name->Text;
}


System::Void Form1::BrowseCSS_Click(System::Object^  sender, System::EventArgs^  e) 
{
	openFileDialog1->Filter = L"Cascading Style Sheet(*.css)|*.css";
	openFileDialog1->InitialDirectory = my_documents_folder;
	openFileDialog1->RestoreDirectory = true;
	openFileDialog1->CheckFileExists;

	if ( openFileDialog1->ShowDialog() == Windows::Forms::DialogResult::OK)
	{
		CSSfilename->Text = openFileDialog1->FileName;
	}
}

System::Void Form1::finalise_settings_tab()
{
	project = project_name->Text->Trim(L' ');
	if (project->Length == 0)
		project = String::Empty;
}

} // END OF NAMESPACE
