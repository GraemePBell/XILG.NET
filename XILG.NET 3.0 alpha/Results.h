#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Diagnostics;
using namespace Microsoft::Win32;

#include "clproxy.h"

namespace XILGNET30alpha {



	/// <summary>
	/// Summary for Results
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Results : public System::Windows::Forms::Form
	{
	public:
		Results(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Results()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button_view_in_browser;
	protected: 
	private: System::Windows::Forms::ComboBox^  combo_browsers;

	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::Label^  LabelViewSite;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
	private: System::Windows::Forms::Button^  CloseResults;

		CLProxy^ params;
	private: System::Windows::Forms::Label^  UploadWebsiteLabel;
	private: System::Windows::Forms::Button^  FolderOpen;

	private: System::Windows::Forms::Label^  OpenFolder;
	private: System::Windows::Forms::Panel^  panel3;

	private: System::Windows::Forms::Label^  RemoteDir;
	private: System::Windows::Forms::Label^  ftpWindowLabel;
	private: System::Windows::Forms::Label^  PasswordLabel;
	private: System::Windows::Forms::Label^  UserIDLabel;
	private: System::Windows::Forms::Label^  HostURILabel;
	private: System::Windows::Forms::CheckBox^  checkpasv;
	private: System::Windows::Forms::TextBox^  textRemDir;
	private: System::Windows::Forms::TextBox^  textPassword;
	private: System::Windows::Forms::TextBox^  textUserID;
	private: System::Windows::Forms::TextBox^  textURI;
	private: System::Windows::Forms::Button^  ButtonFTPUpload;

	private: System::Windows::Forms::Label^  ftp_label;
	private: System::Windows::Forms::RichTextBox^  FTPWindow;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;



	SortedList^ alsp;
	String^ ftp_out;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Results::typeid));
			this->button_view_in_browser = (gcnew System::Windows::Forms::Button());
			this->combo_browsers = (gcnew System::Windows::Forms::ComboBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->LabelViewSite = (gcnew System::Windows::Forms::Label());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->FTPWindow = (gcnew System::Windows::Forms::RichTextBox());
			this->ButtonFTPUpload = (gcnew System::Windows::Forms::Button());
			this->checkpasv = (gcnew System::Windows::Forms::CheckBox());
			this->textRemDir = (gcnew System::Windows::Forms::TextBox());
			this->textPassword = (gcnew System::Windows::Forms::TextBox());
			this->textUserID = (gcnew System::Windows::Forms::TextBox());
			this->textURI = (gcnew System::Windows::Forms::TextBox());
			this->RemoteDir = (gcnew System::Windows::Forms::Label());
			this->ftpWindowLabel = (gcnew System::Windows::Forms::Label());
			this->PasswordLabel = (gcnew System::Windows::Forms::Label());
			this->UserIDLabel = (gcnew System::Windows::Forms::Label());
			this->HostURILabel = (gcnew System::Windows::Forms::Label());
			this->UploadWebsiteLabel = (gcnew System::Windows::Forms::Label());
			this->ftp_label = (gcnew System::Windows::Forms::Label());
			this->CloseResults = (gcnew System::Windows::Forms::Button());
			this->FolderOpen = (gcnew System::Windows::Forms::Button());
			this->OpenFolder = (gcnew System::Windows::Forms::Label());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->panel1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->panel3->SuspendLayout();
			this->SuspendLayout();
			// 
			// button_view_in_browser
			// 
			resources->ApplyResources(this->button_view_in_browser, L"button_view_in_browser");
			this->button_view_in_browser->Name = L"button_view_in_browser";
			this->button_view_in_browser->UseVisualStyleBackColor = true;
			this->button_view_in_browser->Click += gcnew System::EventHandler(this, &Results::button_view_in_browser_Click);
			// 
			// combo_browsers
			// 
			this->combo_browsers->FormattingEnabled = true;
			resources->ApplyResources(this->combo_browsers, L"combo_browsers");
			this->combo_browsers->Name = L"combo_browsers";
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::LightSteelBlue;
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel1->Controls->Add(this->button_view_in_browser);
			this->panel1->Controls->Add(this->LabelViewSite);
			this->panel1->Controls->Add(this->combo_browsers);
			resources->ApplyResources(this->panel1, L"panel1");
			this->panel1->Name = L"panel1";
			// 
			// LabelViewSite
			// 
			resources->ApplyResources(this->LabelViewSite, L"LabelViewSite");
			this->LabelViewSite->Name = L"LabelViewSite";
			// 
			// panel2
			// 
			this->panel2->BackColor = System::Drawing::Color::LightSteelBlue;
			this->panel2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel2->Controls->Add(this->FTPWindow);
			this->panel2->Controls->Add(this->ButtonFTPUpload);
			this->panel2->Controls->Add(this->checkpasv);
			this->panel2->Controls->Add(this->textRemDir);
			this->panel2->Controls->Add(this->textPassword);
			this->panel2->Controls->Add(this->textUserID);
			this->panel2->Controls->Add(this->textURI);
			this->panel2->Controls->Add(this->RemoteDir);
			this->panel2->Controls->Add(this->ftpWindowLabel);
			this->panel2->Controls->Add(this->PasswordLabel);
			this->panel2->Controls->Add(this->UserIDLabel);
			this->panel2->Controls->Add(this->HostURILabel);
			this->panel2->Controls->Add(this->UploadWebsiteLabel);
			this->panel2->Controls->Add(this->ftp_label);
			resources->ApplyResources(this->panel2, L"panel2");
			this->panel2->Name = L"panel2";
			// 
			// FTPWindow
			// 
			this->FTPWindow->BackColor = System::Drawing::Color::Black;
			this->FTPWindow->DetectUrls = false;
			this->FTPWindow->ForeColor = System::Drawing::Color::Chartreuse;
			resources->ApplyResources(this->FTPWindow, L"FTPWindow");
			this->FTPWindow->Name = L"FTPWindow";
			this->FTPWindow->ReadOnly = true;
			// 
			// ButtonFTPUpload
			// 
			resources->ApplyResources(this->ButtonFTPUpload, L"ButtonFTPUpload");
			this->ButtonFTPUpload->Name = L"ButtonFTPUpload";
			this->ButtonFTPUpload->UseVisualStyleBackColor = true;
			this->ButtonFTPUpload->Click += gcnew System::EventHandler(this, &Results::ButtonFTPUpload_Click);
			// 
			// checkpasv
			// 
			resources->ApplyResources(this->checkpasv, L"checkpasv");
			this->checkpasv->Checked = true;
			this->checkpasv->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkpasv->Name = L"checkpasv";
			this->checkpasv->UseVisualStyleBackColor = true;
			// 
			// textRemDir
			// 
			resources->ApplyResources(this->textRemDir, L"textRemDir");
			this->textRemDir->Name = L"textRemDir";
			// 
			// textPassword
			// 
			resources->ApplyResources(this->textPassword, L"textPassword");
			this->textPassword->Name = L"textPassword";
			// 
			// textUserID
			// 
			resources->ApplyResources(this->textUserID, L"textUserID");
			this->textUserID->Name = L"textUserID";
			// 
			// textURI
			// 
			resources->ApplyResources(this->textURI, L"textURI");
			this->textURI->Name = L"textURI";
			this->textURI->TextChanged += gcnew System::EventHandler(this, &Results::textURI_TextChanged);
			// 
			// RemoteDir
			// 
			resources->ApplyResources(this->RemoteDir, L"RemoteDir");
			this->RemoteDir->Name = L"RemoteDir";
			// 
			// ftpWindowLabel
			// 
			resources->ApplyResources(this->ftpWindowLabel, L"ftpWindowLabel");
			this->ftpWindowLabel->Name = L"ftpWindowLabel";
			// 
			// PasswordLabel
			// 
			resources->ApplyResources(this->PasswordLabel, L"PasswordLabel");
			this->PasswordLabel->Name = L"PasswordLabel";
			// 
			// UserIDLabel
			// 
			resources->ApplyResources(this->UserIDLabel, L"UserIDLabel");
			this->UserIDLabel->Name = L"UserIDLabel";
			// 
			// HostURILabel
			// 
			resources->ApplyResources(this->HostURILabel, L"HostURILabel");
			this->HostURILabel->Name = L"HostURILabel";
			// 
			// UploadWebsiteLabel
			// 
			resources->ApplyResources(this->UploadWebsiteLabel, L"UploadWebsiteLabel");
			this->UploadWebsiteLabel->Name = L"UploadWebsiteLabel";
			// 
			// ftp_label
			// 
			resources->ApplyResources(this->ftp_label, L"ftp_label");
			this->ftp_label->Name = L"ftp_label";
			// 
			// CloseResults
			// 
			this->CloseResults->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			resources->ApplyResources(this->CloseResults, L"CloseResults");
			this->CloseResults->Name = L"CloseResults";
			this->CloseResults->UseVisualStyleBackColor = true;
			this->CloseResults->Click += gcnew System::EventHandler(this, &Results::CloseResults_Click);
			// 
			// FolderOpen
			// 
			resources->ApplyResources(this->FolderOpen, L"FolderOpen");
			this->FolderOpen->Name = L"FolderOpen";
			this->FolderOpen->UseVisualStyleBackColor = true;
			this->FolderOpen->Click += gcnew System::EventHandler(this, &Results::FolderOpen_Click);
			// 
			// OpenFolder
			// 
			resources->ApplyResources(this->OpenFolder, L"OpenFolder");
			this->OpenFolder->Name = L"OpenFolder";
			// 
			// panel3
			// 
			this->panel3->BackColor = System::Drawing::Color::LightSteelBlue;
			this->panel3->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel3->Controls->Add(this->OpenFolder);
			this->panel3->Controls->Add(this->FolderOpen);
			resources->ApplyResources(this->panel3, L"panel3");
			this->panel3->Name = L"panel3";
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->WorkerReportsProgress = true;
			this->backgroundWorker1->WorkerSupportsCancellation = true;
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Results::backgroundWorker1_DoWork);
			this->backgroundWorker1->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Results::backgroundWorker1_ProgressChanged);
			// 
			// Results
			// 
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::SteelBlue;
			this->Controls->Add(this->panel3);
			this->Controls->Add(this->CloseResults);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel1);
			this->Cursor = System::Windows::Forms::Cursors::Default;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"Results";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->Load += gcnew System::EventHandler(this, &Results::Results_Load);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
public:  System::Void LoadParameters(CLProxy^ clp); 

private: System::Void Results_Load([[maybe_unused]] System::Object^  sender, [[maybe_unused]] System::EventArgs^  e);
private: System::Void button_view_in_browser_Click([[maybe_unused]] System::Object^  sender, [[maybe_unused]] System::EventArgs^  e);
private: System::Void FolderOpen_Click([[maybe_unused]] System::Object^  sender, [[maybe_unused]] System::EventArgs^  e);
private: System::Void ButtonFTPUpload_Click([[maybe_unused]] System::Object^  sender, [[maybe_unused]] System::EventArgs^  e);
private: bool FTPUploadFile(IO::FileInfo^ file, String^ target);
private: System::Void FTPMakeDirectory(String^ directory);
private: System::Void GatherAndUpload(String^ source, String^ dest);
private: System::Void backgroundWorker1_DoWork([[maybe_unused]] System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void backgroundWorker1_ProgressChanged([[maybe_unused]] System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
private: System::Void CloseResults_Click([[maybe_unused]] System::Object^  sender, [[maybe_unused]] System::EventArgs^  e);
private: System::Void textURI_TextChanged([[maybe_unused]] System::Object^ sender, [[maybe_unused]] System::EventArgs^ e) {
}
};
}
