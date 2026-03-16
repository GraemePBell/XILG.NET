#include "stdafx.h"
#include "form1.h"
#include "xilg_about.h"


namespace XILGNET30alpha {



System::Void Form1::headingFontToolStripMenuItem_Click([[maybe_unused]] System::Object^  sender, [[maybe_unused]] System::EventArgs^  e)
{
	String^ hf = header_font;
	String^ hs = header_font_size;
	String^ hc = header_font_color;
	String^ hy = header_font_style;
	String^ hw = header_font_weight;
	String^ htd = h_text_decoration;

	fontDialog1->ShowColor = true;
	fontDialog1->ShowApply = true;
	fontDialog1->ScriptsOnly = true;

	if(fontDialog1->ShowDialog() != Windows::Forms::DialogResult::Cancel)
	{
		SetHeaderStyles();
		header_font_label->Font = fontDialog1->Font;
		header_font_label->ForeColor = fontDialog1->Color;
	}
	else
	{
		header_font = hf;
		header_font_size = hs;
		header_font_color = hc;
		header_font_style = hy;
		header_font_weight = hw;
		h_text_decoration = htd;
	}
	LoadPreview();
}


System::Void Form1::bodyFontToolStripMenuItem_Click([[maybe_unused]] System::Object^  sender, [[maybe_unused]] System::EventArgs^  e)
{
	String^ bf = body_font;
	String^ bs = body_font_size;
	String^ bc = body_font_color;
	String^ by = body_font_style;
	String^ bw = body_font_weight;
	String^ btd = b_text_decoration;

	fontDialog2->ShowColor = true;
	fontDialog2->ShowApply = true;
	fontDialog2->ScriptsOnly = true;

	if(fontDialog2->ShowDialog() != Windows::Forms::DialogResult::Cancel)
	{
		SetBodyStyles();
		caption_font_label->Font = fontDialog2->Font;
		caption_font_label->ForeColor = fontDialog2->Color;
	}
	else
	{
		body_font = bf;
		body_font_size = bs;
		body_font_color = bc;
		body_font_style = by;
		body_font_weight = bw;
		b_text_decoration = btd;
	}
	LoadPreview();

}


System::Void Form1::bodyColourToolStripMenuItem_Click([[maybe_unused]] System::Object^  sender, [[maybe_unused]] System::EventArgs^  e)
{
	String^ bc = body_color;

	if (colorDialog1->ShowDialog() == Windows::Forms::DialogResult::Cancel)
	{
		body_color = bc;
	}
	else
	{
		String^ tc = L"";
		body_color  = tc->Format(L"#{0:X2}{1:X2}{2:X2}",colorDialog1->Color.R,colorDialog1->Color.G,colorDialog1->Color.B);
		
		color_picker_panel->BackColor = colorDialog1->Color;

		if (header_enabled)
			header_font_panel->BackColor = colorDialog1->Color;
		if (caption_enabled)
			caption_font_panel->BackColor = colorDialog1->Color;
		
		back_color = colorDialog1->Color;
		LoadPreview();
	}

}


System::Void Form1::backgroundImageToolStripMenuItem_Click([[maybe_unused]] System::Object^  sender, [[maybe_unused]] System::EventArgs^  e)
{
	tabControl1->SelectTab(tabPage4);
}

System::Void Form1::bannerImageToolStripMenuItem_Click([[maybe_unused]] System::Object^  sender, [[maybe_unused]] System::EventArgs^  e)
{
	tabControl1->SelectTab(tabPage4);
}

System::Void Form1::includeSubfoldersToolStripMenuItem_Click([[maybe_unused]] System::Object^  sender, [[maybe_unused]] System::EventArgs^  e)
{
	include_subfolders = (!include_subfolders);
	auto_inc_sub_check->Checked = include_subfolders;
}



System::Void Form1::restoreDefaultsToolStripMenuItem_Click([[maybe_unused]] System::Object^  sender, [[maybe_unused]] System::EventArgs^  e) 
{
	if (Windows::Forms::MessageBox::Show(L"Are you sure?","Restore Default Settings",MessageBoxButtons::YesNo,MessageBoxIcon::Question)
		== Windows::Forms::DialogResult::Yes)
	{
		LoadDefaults();
		LoadPreview();
		LoadSettingsPage();
	}
}

System::Void Form1::releaseNotesToolStripMenuItem_Click([[maybe_unused]] System::Object^ sender, [[maybe_unused]] System::EventArgs^ e) 
{
	WCHAR path[MAX_PATH];
	GetModuleFileNameW(nullptr, path, MAX_PATH);
	PathRemoveFileSpecW(path);
	PathAppendW(path, L"xilg_page.html");

	ShellExecuteW(nullptr, L"open", path, nullptr, nullptr, SW_SHOWNORMAL);
}

System::Void Form1::aboutToolStripMenuItem_Click([[maybe_unused]] System::Object^  sender, [[maybe_unused]] System::EventArgs^  e) 
{
	xilg_about^ xa = gcnew xilg_about;
	xa->StartPosition = Windows::Forms::FormStartPosition::CenterParent;
	xa->ShowDialog();
}

System::Void Form1::addImageFolderToolStripMenuItem_Click([[maybe_unused]] System::Object^  sender, [[maybe_unused]] System::EventArgs^  e) 
{
	if ( folderBrowserDialog2->ShowDialog() == Windows::Forms::DialogResult::OK)
	{
		String^ newImageFolder = folderBrowserDialog2->SelectedPath;
		if(newImageFolder == ln->MyComputer())
			return;

		int index = listBox1->FindStringExact( newImageFolder );

		// Determine if a valid index is returned. Select the item if it is valid.
		if ( index != ListBox::NoMatches )
		{
			return;
		}
		else
		{
			listBox1->Items->Add(newImageFolder);
			int ndex = listBox1->FindStringExact( newImageFolder );
			listBox1->SetSelected(ndex,true);
		}
		button3->Enabled = true;
		button4->Enabled = true;
	}
}



} // END OF NAMESPACE
