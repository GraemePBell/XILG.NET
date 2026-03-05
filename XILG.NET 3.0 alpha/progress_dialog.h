#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

#include "clproxy.h"

namespace XILGNET30alpha {

	/// <summary>
	/// Summary for progress_dialog
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class progress_dialog : public System::Windows::Forms::Form
	{
	public:
		progress_dialog(void)
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
		~progress_dialog()
		{
			if (components)
			{
				delete components;
			}
		}

	protected: 
	private: System::Windows::Forms::Label^  making_thumbnails;
	private: System::Windows::Forms::Label^  make_website;
	private: System::Windows::Forms::ProgressBar^  progress_picture_copy;
	private: System::Windows::Forms::ProgressBar^  progress_thumbnail_creation;
	private: System::Windows::Forms::ProgressBar^  progress_site_building;




	private: System::Windows::Forms::Label^  copying_pictures;
	private: System::Windows::Forms::Button^  cancel_build;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
	private: System::Windows::Forms::Panel^  panel1;

		CLProxy^ params;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(progress_dialog::typeid));
			this->making_thumbnails = (gcnew System::Windows::Forms::Label());
			this->make_website = (gcnew System::Windows::Forms::Label());
			this->progress_picture_copy = (gcnew System::Windows::Forms::ProgressBar());
			this->progress_thumbnail_creation = (gcnew System::Windows::Forms::ProgressBar());
			this->progress_site_building = (gcnew System::Windows::Forms::ProgressBar());
			this->copying_pictures = (gcnew System::Windows::Forms::Label());
			this->cancel_build = (gcnew System::Windows::Forms::Button());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// making_thumbnails
			// 
			resources->ApplyResources(this->making_thumbnails, L"making_thumbnails");
			this->making_thumbnails->BackColor = System::Drawing::Color::Transparent;
			this->making_thumbnails->Name = L"making_thumbnails";
			// 
			// make_website
			// 
			resources->ApplyResources(this->make_website, L"make_website");
			this->make_website->BackColor = System::Drawing::Color::Transparent;
			this->make_website->Name = L"make_website";
			// 
			// progress_picture_copy
			// 
			this->progress_picture_copy->ForeColor = System::Drawing::Color::Navy;
			resources->ApplyResources(this->progress_picture_copy, L"progress_picture_copy");
			this->progress_picture_copy->Name = L"progress_picture_copy";
			// 
			// progress_thumbnail_creation
			// 
			this->progress_thumbnail_creation->ForeColor = System::Drawing::Color::Navy;
			resources->ApplyResources(this->progress_thumbnail_creation, L"progress_thumbnail_creation");
			this->progress_thumbnail_creation->Name = L"progress_thumbnail_creation";
			// 
			// progress_site_building
			// 
			this->progress_site_building->ForeColor = System::Drawing::Color::Navy;
			resources->ApplyResources(this->progress_site_building, L"progress_site_building");
			this->progress_site_building->Name = L"progress_site_building";
			// 
			// copying_pictures
			// 
			resources->ApplyResources(this->copying_pictures, L"copying_pictures");
			this->copying_pictures->BackColor = System::Drawing::Color::Transparent;
			this->copying_pictures->Name = L"copying_pictures";
			// 
			// cancel_build
			// 
			this->cancel_build->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			resources->ApplyResources(this->cancel_build, L"cancel_build");
			this->cancel_build->Name = L"cancel_build";
			this->cancel_build->UseVisualStyleBackColor = true;
			this->cancel_build->Click += gcnew System::EventHandler(this, &progress_dialog::cancel_build_Click);
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->WorkerReportsProgress = true;
			this->backgroundWorker1->WorkerSupportsCancellation = true;
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &progress_dialog::backgroundWorker1_DoWork);
			this->backgroundWorker1->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &progress_dialog::backgroundWorker1_RunWorkerCompleted);
			this->backgroundWorker1->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &progress_dialog::backgroundWorker1_ProgressChanged);
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::Moccasin;
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel1->Controls->Add(this->copying_pictures);
			this->panel1->Controls->Add(this->progress_site_building);
			this->panel1->Controls->Add(this->progress_thumbnail_creation);
			this->panel1->Controls->Add(this->progress_picture_copy);
			this->panel1->Controls->Add(this->make_website);
			this->panel1->Controls->Add(this->making_thumbnails);
			resources->ApplyResources(this->panel1, L"panel1");
			this->panel1->Name = L"panel1";
			// 
			// progress_dialog
			// 
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Info;
			this->ControlBox = false;
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->cancel_build);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"progress_dialog";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->Load += gcnew System::EventHandler(this, &progress_dialog::progress_dialog_Load);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
public:  System::Void LoadParameters(CLProxy^ clp); 
private: System::Void ProxyToCommand(CommandLine& cl);
private: System::Void progress_dialog_Load(System::Object^  sender, System::EventArgs^  e);
private: System::Void backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void backgroundWorker1_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
private: System::Void cancel_build_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void backgroundWorker1_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
};
}
