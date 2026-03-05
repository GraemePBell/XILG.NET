#include "stdafx.h"
#include "form1.h"

namespace XILGNET30alpha {


System::Void Form1::enable_watermark_check_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
{
	if (enable_watermark_check->Checked)
	{
		watermark_enabled = true;
		
		WaterMarkOpacity->Enabled = true;
		WaterMarkScale->Enabled = true;

		this->WaterMarkImageName->Enabled = true;
		button8->Enabled = true;

		bottomright->Visible = true;
		bottomcenter->Visible = true;
		bottomleft->Visible = true;
		centerright->Visible = true;
		middle->Visible = true;
		centerleft->Visible = true;
		topright->Visible = true;
		topcenter->Visible = true;
		topleft->Visible = true;

		bottomright->Enabled = true;
		bottomcenter->Enabled = true;
		bottomleft->Enabled = true;
		centerright->Enabled = true;
		middle->Enabled = true;
		centerleft->Enabled = true;
		topright->Enabled = true;
		topcenter->Enabled = true;
		topleft->Enabled = true;

		label6->Enabled = true;
		label7->Enabled = true;
		label8->Enabled = true;
		label9->Enabled = true;
	}
	else
	{
		watermark_enabled = false;

		WaterMarkImageName->Enabled = false;
		button8->Enabled = false;

		bottomright->Enabled = false;
		bottomcenter->Enabled = false;
		bottomleft->Enabled = false;
		centerright->Enabled = false;
		middle->Enabled = false;
		centerleft->Enabled = false;
		topright->Enabled = false;
		topcenter->Enabled = false;
		topleft->Enabled = false;


		WaterMarkOpacity->Enabled = false;
		WaterMarkScale->Enabled = false;
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

		label6->Enabled = false;
		label7->Enabled = false;
		label8->Enabled = false;
		label9->Enabled = false;
	}
}

System::Void Form1::button8_Click(System::Object^  sender, System::EventArgs^  e) 
{
	openFileDialog1->Filter = L"Image Files(*.bmp;*.jpg;*.jpeg;*.gif;*.png)|*.bmp;*.jpg;*.jpeg;*.gif;*.png";
	openFileDialog1->InitialDirectory = my_pictures_folder;
	openFileDialog1->RestoreDirectory = true;
	openFileDialog1->CheckFileExists;

	if ( openFileDialog1->ShowDialog() == Windows::Forms::DialogResult::OK)
	{
		WaterMarkImageName->Text = openFileDialog1->FileName;
	}
}

System::Void Form1::tabPage5_Leave(System::Object^  sender, System::EventArgs^  e) 
{
	finalise_watermark_tab();
}


System::Void Form1::finalise_watermark_tab()
{
	if (watermark_enabled)
	{
		if (System::IO::File::Exists(WaterMarkImageName->Text))
		{
			image_watermark = WaterMarkImageName->Text;
		}
		else
		{
			enable_watermark_check->Checked = false;
			watermark_enabled = false;
			WaterMarkImageName->Text = L"";
		}
	}
	else
	{
		image_watermark = L"";
	}
}
	
} // END OF NAMESPACE