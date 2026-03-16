#include "stdafx.h"
#include "form1.h"


namespace XILGNET30alpha {

System::Void Form1::EnableBackgroundImage_CheckedChanged([[maybe_unused]] System::Object^  sender, [[maybe_unused]] System::EventArgs^  e)
{
	if (EnableBackgroundImageCheck->Checked)
	{
		background_image_enabled = true;

		no_tiling->Enabled = true;
		v_h_tiling->Enabled = true;
		horizontal_tiling->Enabled = true;
		vertical_tiling->Enabled = true;
		label4->Enabled = true;
		textBox4->Enabled = true;
		Form1::button6->Enabled = true;

		if(no_tiling->Checked)
		{
			groupBox1->Enabled = true;
			groupBox2->Enabled = true;
		}
		if(v_h_tiling->Checked)
		{
			groupBox1->Enabled = false;
			groupBox2->Enabled = false;
		}
		if(horizontal_tiling->Checked)
		{
			groupBox1->Enabled = true;
			groupBox2->Enabled = false;
		}
		if(vertical_tiling->Checked)
		{
			groupBox1->Enabled = false;
			groupBox2->Enabled = true;
		}

	}
	else
	{
		background_image_enabled = false;

		groupBox1->Enabled = false;
		groupBox2->Enabled = false;
		no_tiling->Enabled = false;
		v_h_tiling->Enabled = false;
		horizontal_tiling->Enabled = false;
		vertical_tiling->Enabled = false;
		label4->Enabled = false;
		textBox4->Enabled = false;
		Form1::button6->Enabled = false;
	}
}


System::Void Form1::v_h_tiling_Click([[maybe_unused]] System::Object^  sender, [[maybe_unused]] System::EventArgs^  e)
{
	if (v_h_tiling->Checked)
	{
		groupBox1->Enabled = false;
		groupBox2->Enabled = false;
	}
}


System::Void Form1::horizontal_tiling_Click([[maybe_unused]] System::Object^  sender, [[maybe_unused]] System::EventArgs^  e)
{
	if (horizontal_tiling->Checked)
	{
		groupBox1->Enabled = true;
		groupBox2->Enabled = false;
		top->Enabled = true;
		bottom->Enabled = true;
		v_center->Enabled = true;
		h_center->Enabled = false;
		left->Enabled = false;
		right->Enabled = false;
	}
}


System::Void Form1::vertical_tiling_Click([[maybe_unused]] System::Object^  sender, [[maybe_unused]] System::EventArgs^  e)
{
	if (vertical_tiling->Checked)
	{
		groupBox1->Enabled = false;
		groupBox2->Enabled = true;
		top->Enabled = false;
		bottom->Enabled = false;
		v_center->Enabled = false;
		h_center->Enabled = true;
		left->Enabled = true;
		right->Enabled = true;
	}
}



System::Void Form1::no_tiling_Click([[maybe_unused]] System::Object^  sender, [[maybe_unused]] System::EventArgs^  e)
{
	if (no_tiling->Checked)
	{
		groupBox1->Enabled = true;
		groupBox2->Enabled = true;
		top->Enabled = true;
		bottom->Enabled = true;
		v_center->Enabled = true;
		h_center->Enabled = true;
		left->Enabled = true;
		right->Enabled = true;
	}
}

System::Void Form1::button6_Click([[maybe_unused]] System::Object^  sender, [[maybe_unused]] System::EventArgs^  e)
{
	openFileDialog1->Filter = L"Image Files(*.bmp;*.jpg;*.jpeg;*.gif;*.png)|*.bmp;*.jpg;*.jpeg;*.gif;*.png";
	openFileDialog1->InitialDirectory = my_pictures_folder;
	openFileDialog1->RestoreDirectory = true;
	openFileDialog1->CheckFileExists;

	if ( openFileDialog1->ShowDialog() == Windows::Forms::DialogResult::OK)
	{
		textBox4->Text = openFileDialog1->FileName;
	}
}

System::Void Form1::tabPage4_Leave([[maybe_unused]] System::Object^  sender, [[maybe_unused]] System::EventArgs^  e)
{
	finalise_background_tab();
}

System::Void Form1::EnableBannerImage_CheckedChanged([[maybe_unused]] System::Object^  sender, [[maybe_unused]] System::EventArgs^  e)
{
	if (EnableBannerImageCheck->Checked)
	{
		banner_image_enabled = true;

		label5->Enabled = true;
		textBox5->Enabled = true;
		Form1::button7->Enabled = true;
	}
	else
	{
		banner_image_enabled = false;

		label5->Enabled = false;
		textBox5->Enabled = false;
		Form1::button7->Enabled = false;
	}
}

System::Void Form1::button7_Click([[maybe_unused]] System::Object^  sender, [[maybe_unused]] System::EventArgs^  e)
{
	openFileDialog1->Filter = L"Image Files(*.bmp;*.jpg;*.jpeg;*.gif;*.png)|*.bmp;*.jpg;*.jpeg;*.gif;*.png";
	openFileDialog1->InitialDirectory = my_pictures_folder;
	openFileDialog1->RestoreDirectory = true;
	openFileDialog1->CheckFileExists;

	if ( openFileDialog1->ShowDialog() == Windows::Forms::DialogResult::OK)
	{
		textBox5->Text = openFileDialog1->FileName;
	}
}

System::Void Form1::finalise_background_tab()
{
	if (EnableBackgroundImageCheck->Checked)
	{
		if (System::IO::File::Exists(textBox4->Text))
		{
			String^ p1;
			String^ p2;
			String^ p3;

			image_background = textBox4->Text->Replace(L"\\",L"/");

			if (no_tiling->Checked)
			{
				image_background_repeat = L"no-repeat";
				
				if (top->Checked)
					p1 = L"top ";
				if (v_center->Checked)
					p1 = L"center ";
				if (bottom->Checked)
					p1 = L"bottom ";

				if (left->Checked)
					p2 = L"left";
				if (h_center->Checked)
					p2 = L"center";
				if (right->Checked)
					p2 = L"right";
			}


			if (vertical_tiling->Checked)
			{
				image_background_repeat = L"repeat-y";

				if (left->Checked)
					p2 = L"left";
				if (h_center->Checked)
					p2 = L"center";
				if (right->Checked)
					p2 = L"right";
			}

			if (horizontal_tiling->Checked)
			{
				image_background_repeat = L"repeat-x";

				if (top->Checked)
					p2 = L"top";
				if (v_center->Checked)
					p2 = L"center";
				if (bottom->Checked)
					p2 = L"bottom";
			}
			if (v_h_tiling->Checked)
			{
				image_background_repeat = L"repeat";
			}
			
			if (image_background_repeat != L"repeat")
			{
				p3 = L"; background-position:";
				image_background_position = p1 + p2 ;
			}

			image_background_settings
				= L" background-image:url('" 
				+ image_background 
				+ L"'); background-repeat:" 
				+ image_background_repeat
				+ p3
				+ image_background_position;

		}
		else
		{
			EnableBackgroundImageCheck->Checked = false;
			background_image_enabled = false; 
		}
	}
	else
	{
		image_background_settings = String::Empty;
		image_background_repeat = String::Empty;
		image_background_position = String::Empty;
		image_background = String::Empty;
		background_image_enabled = false;
	}

	if (EnableBannerImageCheck->Checked)
	{
		image_banner_div = String::Empty;
		image_banner_settings = String::Empty;
		image_banner = String::Empty;

		if (System::IO::File::Exists(textBox5->Text))
		{
			System::Drawing::Bitmap^ banner_bitmap = gcnew System::Drawing::Bitmap(textBox5->Text);

			image_banner = textBox5->Text->Replace(L"\\",L"/");
			image_banner_settings
				= L"; height:"
				+ banner_bitmap->Height.ToString()
				+ L"px";
			image_banner_div = 	L"\n\t\t<div class=\"banner\">.</div>";
			banner_image_enabled = true;
		}
		else
		{
			EnableBannerImageCheck->Checked = false;
			banner_image_enabled = false;
		}
	}
	else
	{
		image_banner_div = String::Empty;
		image_banner_settings = String::Empty;
		image_banner = String::Empty;
		banner_image_enabled = false;
	}
}

} // END OF NAMESPACE