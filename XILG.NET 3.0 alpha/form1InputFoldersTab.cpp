#include "stdafx.h"
#include "form1.h"


namespace XILGNET30alpha {



System::Void Form1::treeView1_AfterSelect([[maybe_unused]] System::Object^  sender, 
	[[maybe_unused]] System::Windows::Forms::TreeViewEventArgs^  e)
{
	Form1::Cursor = Cursors::AppStarting;
	treeView1->BeginUpdate();
	String^ my_selection = treeView1->SelectedNode->Name;
	treeView1->SelectedNode->ToolTipText = my_selection;
	if (my_selection == my_computer_folder)
	{
		treeView1_MyComputer();
	}
	else
	{
		treeView1_folders();
	}
	treeView1->EndUpdate();
	Form1::Cursor = Cursors::Default;
}

System::Void Form1::treeView1_MyComputer() 
{
	int drive_icon = 6;

	my_nodes = treeView1->SelectedNode->Nodes;
	my_nodes->Clear();

	array<String^>^drives = Environment::GetLogicalDrives();

	for (int count=0; count < drives->Length; count++)
	{
		String^ Drive = drives[count]->Replace("\\","");

		IO::DriveInfo^ di = gcnew IO::DriveInfo(Drive);
		switch (di->DriveType)
		{
			case IO::DriveType::Removable:
			{
				drive_icon = 9;
				break;
			}
			case IO::DriveType::CDRom :
			{
				drive_icon = 3;
				break;
			}
			case IO::DriveType::Fixed :
			{
				drive_icon = 2;
				break;
			}
			case IO::DriveType::Network :
			{
				drive_icon = 11;
				break;
			}
			case IO::DriveType::NoRootDirectory :
			{
				drive_icon = 6;
				break;
			}
			case IO::DriveType::Ram :
			{
				drive_icon = 12;
				break;
			}
			case IO::DriveType::Unknown :
			default:
			{
				drive_icon = 13;
				break;
			}
		}

		my_nodes->Add(Drive,drives[count],drive_icon,drive_icon);
	}
}

System::Void Form1::treeView1_folders() 
{
	int closed_folder_icon = 7;
	int open_folder_icon = 6;
	String^ my_selection = treeView1->SelectedNode->Name;

	if (!my_selection->EndsWith(L"\\"))
		my_selection += L"\\";

	my_nodes = treeView1->SelectedNode->Nodes;
	my_nodes->Clear();


	try
	{   // Lovely error handling for inacessible or slow paths
		IO::DirectoryInfo^ dir = gcnew IO::DirectoryInfo(my_selection);

		array<IO::DirectoryInfo^>^folders = dir->GetDirectories();

		for (int count=0; count < folders->Length; count++)
		{
			IO::DirectoryInfo^ mydir = folders[count];

			try 
			{   // Let's not add anything to the list that causes a deeper exception
				[[maybe_unused]] array<IO::DirectoryInfo^>^deeperfolders = mydir->GetDirectories();
				my_nodes->Add(mydir->FullName,mydir->Name,closed_folder_icon,open_folder_icon);
			}
			catch (Exception ^e)
			{
				e;
			}
		}
	}
	catch (Exception^ e)
	{
		e;
	}
}


System::Void Form1::button2_Click([[maybe_unused]] System::Object^  sender, [[maybe_unused]] [[maybe_unused]] System::EventArgs^  e)
{
	if(treeView1->SelectedNode)
	{
		if(treeView1->SelectedNode->Text == ln->MyComputer())
			return;

		String^ my_selection = treeView1->SelectedNode->Name;
		int index = listBox1->FindStringExact( my_selection );

		// Determine if a valid index is returned. Select the item if it is valid.
		if ( index != ListBox::NoMatches )
		{
			return;
		}
		else
		{
			listBox1->Items->Add(my_selection);
			int id = listBox1->FindStringExact( my_selection );
			listBox1->SetSelected(id,true);
			//toolTip1->SetToolTip
		}
		button3->Enabled = true;
		button4->Enabled = true;
	}
}


System::Void Form1::button3_Click([[maybe_unused]] System::Object^  sender, [[maybe_unused]] [[maybe_unused]] System::EventArgs^  e)
{
	if (listBox1->SelectedItem)
	{
		int idx = listBox1->SelectedIndex;
		listBox1->Items->Remove(listBox1->SelectedItem);
		idx--;
		if (idx < 0)
			idx = 0;

		if(listBox1->Items->Count != 0)
			listBox1->SelectedIndex = idx;
	}

	if (listBox1->Items->Count == 0)
	{
		button3->Enabled = false;
		button4->Enabled = false;
	}
}


System::Void Form1::button4_Click([[maybe_unused]] System::Object^  sender, [[maybe_unused]] [[maybe_unused]] System::EventArgs^  e)
{
	listBox1->Items->Clear();
	button3->Enabled = false;
	button4->Enabled = false;
}		 



System::Void Form1::checkBox1_Click([[maybe_unused]] System::Object^  sender, [[maybe_unused]] [[maybe_unused]] System::EventArgs^  e)
{
	include_subfolders = (!include_subfolders);
	if(auto_inc_sub_check->Checked)
	{
		includeSubfoldersToolStripMenuItem->CheckState = CheckState::Checked;
	}
	else
	{
		includeSubfoldersToolStripMenuItem->CheckState = CheckState::Unchecked;
	}
}


System::Void Form1::listBox1_MouseMove([[maybe_unused]] System::Object^  sender, 
	[[maybe_unused]] System::Windows::Forms::MouseEventArgs^  e)
{
	String^ strTip = L"";

	//Get the item
	int nIdx = listBox1->IndexFromPoint(e->Location);
	if ((nIdx >= 0) && (nIdx < listBox1->Items->Count))
		strTip = listBox1->Items[nIdx]->ToString();

	toolTip1->SetToolTip(listBox1, strTip);
}


System::Void Form1::EnableUserCSSCheck_CheckedChanged([[maybe_unused]] System::Object^  sender, [[maybe_unused]] [[maybe_unused]] System::EventArgs^  e)
{
	user_css = !user_css;

	if (user_css)
	{
		labelUserCSS->Enabled = true;
		CSSfilename->Enabled = true;
		BrowseCSS->Enabled = true;
	}
	else
	{
		labelUserCSS->Enabled = false;
		CSSfilename->Enabled = false;
		BrowseCSS->Enabled = false;
	}
}


System::Void Form1::tabPage1_Leave([[maybe_unused]] System::Object^ sender, [[maybe_unused]] [[maybe_unused]] System::EventArgs^  e)
{
	finalise_input_folders_tab();
}

System::Void Form1::finalise_input_folders_tab()
{
	if (user_css)
	{
		if (!System::IO::File::Exists(CSSfilename->Text))
		{
			labelUserCSS->Enabled = false;
			CSSfilename->Enabled = false;
			BrowseCSS->Enabled = false;
			CSSfilename->Text = String::Empty;
			user_css = false;
			EnableUserCSSCheck->Checked = false;
		}
	}
}

} // END OF NAMESPACE
