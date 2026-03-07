#include "StdAfx.h"
#include "Results.h"

using namespace System::Net;
using namespace System::IO;

namespace XILGNET30alpha {


System::Void Results::LoadParameters(CLProxy^ clp)
{
	params = clp;
}

System::Void Results::Results_Load([[maybe_unused]] System::Object^  sender, [[maybe_unused]] System::EventArgs^  e)
{
	combo_browsers->Items->Add(L"[Default Browser]");

	RegistryKey^ rk = Registry::LocalMachine;
	RegistryKey^ SMIkey;
	RegistryKey^ BrowserNameKey;
	RegistryKey^ BrowserPathKey;
	alsp = gcnew SortedList(0); 

	SMIkey = rk->OpenSubKey(L"SOFTWARE\\Clients\\StartMenuInternet");
	
	array<String^>^subKeyNames = SMIkey->GetSubKeyNames();

	for (int count = 0; count < subKeyNames->Length ;count++)
	{
		String^ bn = String::Empty;

		BrowserNameKey = SMIkey->OpenSubKey(subKeyNames[count]);
		bn = (String^)(BrowserNameKey->GetValue(L""));
		if (bn)
		{
			BrowserPathKey = BrowserNameKey->OpenSubKey(L"shell\\open\\command");
			String^ pn = (String^)(BrowserPathKey->GetValue(L""));
			if (pn)
			{
				alsp->Add(bn,pn);
				combo_browsers->Items->Add(bn);
			}
		}
	}
	combo_browsers->SelectedIndex = 0;
}

System::Void Results::button_view_in_browser_Click([[maybe_unused]] System::Object^  sender, [[maybe_unused]] System::EventArgs^  e) 
{
	String^ ext = params->no_html ? L".xml" : L".html";
	String^ number = params->pics_per_page > 1 ? L"-1" : L"";
	String^ filename = params->output_path + L"\\" + params->project_name + L"\\" + params->project_name + number + ext;

	Process^ mybrowser = gcnew Process;

	String^ mytext = combo_browsers->Text;
	
	try 
	{
		if (mytext == L"[Default Browser]")
		{
			mybrowser->StartInfo->FileName = filename;
			mybrowser->StartInfo->Verb = "Open";
			mybrowser->Start();

		}
		else
		{
			mybrowser->StartInfo->Arguments = L"\"" + filename + L"\"";
			mybrowser->StartInfo->FileName = (String^) alsp[mytext];
			mybrowser->StartInfo->Verb = "Open";
			mybrowser->StartInfo->UseShellExecute = true;
			mybrowser->Start();
		}
	}
	catch (...)
	{
		MessageBox::Show(L"Couldn't open the Website with your chosen browser!",L"XILG - Error!");
	}
}


System::Void Results::FolderOpen_Click([[maybe_unused]] System::Object^  sender, [[maybe_unused]] System::EventArgs^  e) 
{
	try 
	{
		Process^ mybrowser = gcnew Process;
		mybrowser->StartInfo->FileName = params->output_path + L"\\" + params->project_name;
		mybrowser->StartInfo->Verb = "Open";
		mybrowser->Start();
	}
	catch (...)
	{
		MessageBox::Show(L"Couldn't open the Website Folder!",L"XILG - Error!");
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//		FTPWindow->AppendText("**Test**\n");
//		FTPWindow->SelectionColor = Color::Red;
//		FTPWindow->SelectionFont = gcnew System::Drawing::Font("Verdana", 12, FontStyle::Bold );
//		FTPWindow->AppendText("**Good URI!**\n");
//		FTPWindow->SelectionColor = Color::LawnGreen;
//		FTPWindow->AppendText("**Test**\n");
/////////////////////////////////////////////////////////////////////////////////////////////////////

System::Void Results::ButtonFTPUpload_Click([[maybe_unused]] System::Object^  sender, [[maybe_unused]] System::EventArgs^  e) 
{
	backgroundWorker1->RunWorkerAsync();
}

System::Void Results::backgroundWorker1_DoWork([[maybe_unused]] System::Object^  sender, 
	[[maybe_unused]] System::ComponentModel::DoWorkEventArgs^  e)
{
	ButtonFTPUpload->Enabled = false;
	
	// String^ filename = L"d:\\test.txt";
	String^ dirname = textRemDir->Text + L"/" + params->project_name;
	String^ i_dirname = dirname + L"/images";
	String^ t_dirname = dirname + L"/thumbs";
	
//	FTPUploadFile(filename,L"/");
	FTPMakeDirectory(dirname);
	FTPMakeDirectory(i_dirname);
	FTPMakeDirectory(t_dirname);

	/////////////////////////////////////////////////////
	String^ localname = params->output_path + L"\\" + params->project_name;
	String^ local_i_name = localname + L"\\images";
	String^ local_t_name = localname + L"\\thumbs";

	GatherAndUpload(localname,dirname);
	GatherAndUpload(local_i_name,i_dirname);
	GatherAndUpload(local_t_name,t_dirname);

	ftp_out = (backgroundWorker1->CancellationPending) ? L"FTP Upload Cancelled!" : L"FTP Upload Completed!";

	backgroundWorker1->ReportProgress(1);
	ButtonFTPUpload->Enabled = true;
}


System::Void Results::GatherAndUpload(String^ source, String^ dest)
{
	if (backgroundWorker1->CancellationPending)
		return;

	int errCount = 0;
	DirectoryInfo^ dir = gcnew DirectoryInfo(source);
	cli::array<FileInfo^>^ infos = dir->GetFiles(L"*.*");

	bool IsSuccess = true;

	for each (FileInfo^ fileInfo in infos)
	{
		if (backgroundWorker1->CancellationPending)
			return;
		
		if (fileInfo)
		{
			IsSuccess = FTPUploadFile(fileInfo,dest);
			if (!IsSuccess)
			{
				errCount = errCount + 1;
			}
		}
		if (errCount > 100)
		{
			break;
		}
    }
}


bool Results::FTPUploadFile(FileInfo^ fileInf, String^ target)
{
	if (backgroundWorker1->CancellationPending)
		return false;

	String^ uri = L"ftp://" + textURI->Text + L"/" + target + L"/" + fileInf->Name;

	FtpWebRequest^ reqFTP;

	try
	{
		reqFTP = (FtpWebRequest^)FtpWebRequest::Create(gcnew Uri(uri));
		reqFTP->Credentials = gcnew NetworkCredential(textUserID->Text, textPassword->Text);
		reqFTP->KeepAlive = false;
		reqFTP->Method = WebRequestMethods::Ftp::UploadFile;
		reqFTP->UseBinary = true;
		reqFTP->ContentLength = fileInf->Length;
		reqFTP->Timeout = 10000;
		reqFTP->UsePassive = false;

		int buffLength = 2048;
		cli::array<byte>^ buff = gcnew cli::array<byte>(buffLength);
		int contentLen;

		// Opens a file stream (System.IO.FileStream) to read the file to be uploaded
		FileStream^ fs = fileInf->OpenRead();
		Stream^ strm = reqFTP->GetRequestStream();
		contentLen = fs->Read(buff, 0, buffLength);

		while (contentLen != 0)
		{
			strm->Write(buff, 0, contentLen);
			contentLen = fs->Read(buff, 0, buffLength);
		}
		// Close the file stream and the Request Stream
		strm->Close();
		fs->Close();
		
		ftp_out = fileInf->Name + L" => " + uri->ToString() + L"\n";
		backgroundWorker1->ReportProgress(1);

	}
	catch(Exception^ ex)
	{
		ftp_out = ex->Message + L"\n";
		backgroundWorker1->ReportProgress(1);
		return false;
	}
	return true;
}

System::Void Results::FTPMakeDirectory(String^ directory)
{
	if (backgroundWorker1->CancellationPending)
		return;

	[[maybe_unused]] DirectoryInfo^ DirInf = gcnew DirectoryInfo(directory);
	String^ uri = L"ftp://" + textURI->Text + L"/" + directory;

	FtpWebRequest^ reqFTP;

    try
    {
		// dirName = name of the directory to create.
		reqFTP = (FtpWebRequest^)FtpWebRequest::Create(gcnew Uri(uri));
		reqFTP->Method = WebRequestMethods::Ftp::MakeDirectory;
        reqFTP->UseBinary = true;
		reqFTP->Timeout = 10000;
		reqFTP->UsePassive = false;
        reqFTP->Credentials = gcnew NetworkCredential(textUserID->Text, textPassword->Text);
        FtpWebResponse^ response = (FtpWebResponse^)reqFTP->GetResponse();
        Stream^ ftpStream = response->GetResponseStream();

		ftp_out = L"MkDir:" + directory + L"\n";
		backgroundWorker1->ReportProgress(1);

        ftpStream->Close();
        response->Close();
	}
	catch (Exception^ ex)
	{
		ftp_out = ex->Message + L"\n";
		backgroundWorker1->ReportProgress(1);
	}
}

System::Void Results::backgroundWorker1_ProgressChanged([[maybe_unused]] System::Object^  sender, 
	[[maybe_unused]] System::ComponentModel::ProgressChangedEventArgs^  e) 
{
	FTPWindow->AppendText(ftp_out);
}	

System::Void Results::CloseResults_Click([[maybe_unused]] System::Object^  sender, [[maybe_unused]] System::EventArgs^  e) 
{
	if (backgroundWorker1->IsBusy)
		backgroundWorker1->CancelAsync();

	Sleep(500);
	Results::Close();
}


}; // END OF NAMESPACE