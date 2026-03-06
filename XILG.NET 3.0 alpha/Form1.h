#pragma once
#include "LocalisedNames.h"
#include "commandline.h"
#include "clproxy.h"

namespace XILGNET30alpha {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace LocalisedNames;
	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
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
		~Form1()
		{
			if (components)
			{
				delete components;
			}
			if (ln != nullptr)
			{
				delete ln;   // This calls IDisposable::Dispose()
				ln = nullptr;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  generateToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  cancelToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  viewPageToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  advancedToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  headingFontToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  bodyFontToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  bodyColourToolStripMenuItem;



	private: System::Windows::Forms::ToolStripMenuItem^  restoreDefaultsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  releaseNotesToolStripMenuItem;

	private: System::Windows::Forms::ImageList^  imageList1;
	private: System::Windows::Forms::FontDialog^  fontDialog1;
	private: System::Windows::Forms::FontDialog^  fontDialog2;
	private: System::Windows::Forms::ColorDialog^  colorDialog1;
	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;

	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.

	private: System::Windows::Forms::ToolStripMenuItem^  includeSubfoldersToolStripMenuItem;
	private: System::Windows::Forms::ToolTip^  toolTip1;
	private: System::Windows::Forms::TreeNodeCollection^ my_nodes;
	private: System::Windows::Forms::TabPage^  tabPage3;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::WebBrowser^  webBrowser1;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::CheckBox^  auto_inc_sub_check;

	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::ListBox^  listBox1;
	private: System::Windows::Forms::TreeView^  treeView1;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  project_name;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  webpage_title_text;


	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator3;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator4;
	private: System::Windows::Forms::TabPage^  tabPage4;
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::CheckBox^  EnableBannerImageCheck;


	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::RadioButton^  no_tiling;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::RadioButton^  left;
	private: System::Windows::Forms::RadioButton^  h_center;
	private: System::Windows::Forms::RadioButton^  right;
	private: System::Windows::Forms::CheckBox^  EnableBackgroundImageCheck;

	private: System::Windows::Forms::RadioButton^  v_h_tiling;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::RadioButton^  bottom;
	private: System::Windows::Forms::RadioButton^  v_center;
	private: System::Windows::Forms::RadioButton^  top;
	private: System::Windows::Forms::RadioButton^  horizontal_tiling;
	private: System::Windows::Forms::RadioButton^  vertical_tiling;


		/// </summary>
	// My Variables
	private: bool include_subfolders;
	private: bool internal_css;
	private: bool user_css;
	private: bool no_html;
	private: bool only_html;

	private: bool header_enabled;
	private: bool caption_enabled;

	private: bool banner_image_enabled;
	private: bool multipage_enabled;
	private: bool page_title_enabled;
	private: bool project_name_enabled;
	private: bool internal_css_enabled;
	private: bool background_image_enabled;
	private: bool watermark_enabled;

	private: LocalNames^ ln;

	private: String^ desktop;
	private: String^ my_computer;
	private: String^ my_documents;
	private: String^ my_pictures;

	private: String^ desktop_folder;
	private: String^ my_computer_folder;
	private: String^ my_documents_folder;
	private: String^ destination_folder;
	private: String^ page_title;
	private: String^ page_title_2;
	private: String^ my_pictures_folder;

	private: String^ project;

	// Image strings for Preview
	private: String^ image_banner;
	private: String^ image_background;
	private: String^ image_thumb1;
	private: String^ image_thumb2;
	private: String^ image_thumb3;
	private: String^ image_thumb4;
	private: String^ image_thumb5;
	private: String^ image_thumb6;
	private: String^ newpage;
	private: String^ caption1;
	private: String^ caption2;
	private: String^ caption3;
	private: String^ caption4;
	private: String^ caption5;
	private: String^ caption6;

	// web page style settings
	private: String^ header_font;
	private: String^ header_font_size;
	private: String^ header_font_weight;
	private: String^ header_font_color;
	private: String^ header_font_style;
	private: String^ header_strike;
	private: String^ header_underline;

	private: String^ body_font;
	private: String^ body_font_size;
	private: String^ body_font_weight;
	private: String^ body_font_color;
	private: String^ body_font_style;
	private: String^ body_strike;
	private: String^ body_underline;

	private: String^ body_color;
	private: System::Drawing::Color back_color;


	private: String^ h_text_decoration;
	private: String^ b_text_decoration;


	private: String^ image_background_repeat;
	private: String^ image_background_position;
	private: String^ image_background_settings;
	private: String^ image_banner_settings;

	private: System::Windows::Forms::Panel^  panel3;
	private: System::Windows::Forms::Panel^  panel4;
	private: System::Windows::Forms::Panel^  panel6;


	private: System::Windows::Forms::RadioButton^  custom_size;
	private: System::Windows::Forms::RadioButton^  default_size;
	private: System::Windows::Forms::Label^  thumbnail_label;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;


	private: System::Windows::Forms::Button^  build_website;



	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown4;
	private: System::Windows::Forms::CheckBox^  enable_multipage_check;


	private: System::Windows::Forms::Panel^  panel8;
	private: System::Windows::Forms::TabPage^  tabPage5;
	private: System::Windows::Forms::Panel^  panel5;
	private: System::Windows::Forms::Panel^  panel7;
	private: System::Windows::Forms::RadioButton^  topleft;
	private: System::Windows::Forms::RadioButton^  centerright;
	private: System::Windows::Forms::RadioButton^  topcenter;
	private: System::Windows::Forms::RadioButton^  middle;
	private: System::Windows::Forms::RadioButton^  topright;
	private: System::Windows::Forms::RadioButton^  bottomright;
	private: System::Windows::Forms::RadioButton^  centerleft;
	private: System::Windows::Forms::RadioButton^  bottomleft;
	private: System::Windows::Forms::RadioButton^  bottomcenter;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::NumericUpDown^  WaterMarkScale;

	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::NumericUpDown^  WaterMarkOpacity;

	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::CheckBox^  enable_watermark_check;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::TextBox^  WaterMarkImageName;


	private: String^ image_watermark;
	private: System::Windows::Forms::Label^  if_title;
	private: System::Windows::Forms::Label^  bs_title;

	private: System::Windows::Forms::Panel^  panel9;
	private: System::Windows::Forms::Label^  bs2_title;
	private: System::Windows::Forms::Label^  wms_title;
	private: System::Windows::Forms::Panel^  panel11;
	private: System::Windows::Forms::Panel^  header_font_panel;


	private: System::Windows::Forms::RadioButton^  xml_only;
	private: System::Windows::Forms::RadioButton^  xhtml_only;
	private: System::Windows::Forms::RadioButton^  xml_plus_html;
	private: System::Windows::Forms::Panel^  color_picker_panel;
	private: System::Windows::Forms::Label^  background_color_label;
	private: System::Windows::Forms::Label^  header_font_label;
	private: System::Windows::Forms::Panel^  caption_font_panel;

	private: System::Windows::Forms::Label^  caption_font_label;
	private: System::Windows::Forms::CheckBox^  enable_caption_check;
	private: System::Windows::Forms::CheckBox^  enable_header_check;
	private: System::Windows::Forms::Panel^  panel10;
	private: System::Windows::Forms::Panel^  panel12;
	private: System::Windows::Forms::Label^  labelUserCSS;
	private: System::Windows::Forms::TextBox^  CSSfilename;
	private: System::Windows::Forms::Button^  BrowseCSS;
	private: System::Windows::Forms::CheckBox^  EnableUserCSSCheck;
	private: System::Windows::Forms::ToolStripMenuItem^  userCSSToolStripMenuItem;
	private: System::Windows::Forms::Button^  button_view_website;
	private: System::Windows::Forms::ToolStripMenuItem^  addImageFolderToolStripMenuItem;
	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog2;


	private: String^ image_banner_div;

	// My Functions
	private: System::Void LoadDefaults();
	private: System::Void LoadSettingsPage();
	private: System::Void SetHeaderStyles();
	private: System::Void SetBodyStyles();
	private: position WatermarkPos();
		   [System::Diagnostics::CodeAnalysis::SuppressMessage(
			   "Microsoft.Security",
			   "CA2122:DoNotIndirectlyExposeMethodsWithLinkDemands")]


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->generateToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->cancelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->viewPageToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->advancedToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->headingFontToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bodyFontToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bodyColourToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->addImageFolderToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->includeSubfoldersToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->userCSSToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator4 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->restoreDefaultsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->releaseNotesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->imageList1 = (gcnew System::Windows::Forms::ImageList(this->components));
			this->fontDialog1 = (gcnew System::Windows::Forms::FontDialog());
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->webBrowser1 = (gcnew System::Windows::Forms::WebBrowser());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->if_title = (gcnew System::Windows::Forms::Label());
			this->panel9 = (gcnew System::Windows::Forms::Panel());
			this->panel12 = (gcnew System::Windows::Forms::Panel());
			this->labelUserCSS = (gcnew System::Windows::Forms::Label());
			this->CSSfilename = (gcnew System::Windows::Forms::TextBox());
			this->BrowseCSS = (gcnew System::Windows::Forms::Button());
			this->EnableUserCSSCheck = (gcnew System::Windows::Forms::CheckBox());
			this->panel10 = (gcnew System::Windows::Forms::Panel());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->auto_inc_sub_check = (gcnew System::Windows::Forms::CheckBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->treeView1 = (gcnew System::Windows::Forms::TreeView());
			this->topleft = (gcnew System::Windows::Forms::RadioButton());
			this->centerright = (gcnew System::Windows::Forms::RadioButton());
			this->topcenter = (gcnew System::Windows::Forms::RadioButton());
			this->topright = (gcnew System::Windows::Forms::RadioButton());
			this->bottomright = (gcnew System::Windows::Forms::RadioButton());
			this->centerleft = (gcnew System::Windows::Forms::RadioButton());
			this->bottomleft = (gcnew System::Windows::Forms::RadioButton());
			this->bottomcenter = (gcnew System::Windows::Forms::RadioButton());
			this->color_picker_panel = (gcnew System::Windows::Forms::Panel());
			this->header_font_label = (gcnew System::Windows::Forms::Label());
			this->caption_font_label = (gcnew System::Windows::Forms::Label());
			this->middle = (gcnew System::Windows::Forms::RadioButton());
			this->build_website = (gcnew System::Windows::Forms::Button());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->caption_font_panel = (gcnew System::Windows::Forms::Panel());
			this->enable_caption_check = (gcnew System::Windows::Forms::CheckBox());
			this->panel11 = (gcnew System::Windows::Forms::Panel());
			this->xml_only = (gcnew System::Windows::Forms::RadioButton());
			this->xhtml_only = (gcnew System::Windows::Forms::RadioButton());
			this->xml_plus_html = (gcnew System::Windows::Forms::RadioButton());
			this->header_font_panel = (gcnew System::Windows::Forms::Panel());
			this->enable_header_check = (gcnew System::Windows::Forms::CheckBox());
			this->bs_title = (gcnew System::Windows::Forms::Label());
			this->panel8 = (gcnew System::Windows::Forms::Panel());
			this->numericUpDown4 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->enable_multipage_check = (gcnew System::Windows::Forms::CheckBox());
			this->panel6 = (gcnew System::Windows::Forms::Panel());
			this->custom_size = (gcnew System::Windows::Forms::RadioButton());
			this->default_size = (gcnew System::Windows::Forms::RadioButton());
			this->thumbnail_label = (gcnew System::Windows::Forms::Label());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->project_name = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->webpage_title_text = (gcnew System::Windows::Forms::TextBox());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
			this->bs2_title = (gcnew System::Windows::Forms::Label());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->EnableBannerImageCheck = (gcnew System::Windows::Forms::CheckBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->background_color_label = (gcnew System::Windows::Forms::Label());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->no_tiling = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->left = (gcnew System::Windows::Forms::RadioButton());
			this->h_center = (gcnew System::Windows::Forms::RadioButton());
			this->right = (gcnew System::Windows::Forms::RadioButton());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->EnableBackgroundImageCheck = (gcnew System::Windows::Forms::CheckBox());
			this->v_h_tiling = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->bottom = (gcnew System::Windows::Forms::RadioButton());
			this->v_center = (gcnew System::Windows::Forms::RadioButton());
			this->top = (gcnew System::Windows::Forms::RadioButton());
			this->horizontal_tiling = (gcnew System::Windows::Forms::RadioButton());
			this->vertical_tiling = (gcnew System::Windows::Forms::RadioButton());
			this->tabPage5 = (gcnew System::Windows::Forms::TabPage());
			this->wms_title = (gcnew System::Windows::Forms::Label());
			this->panel5 = (gcnew System::Windows::Forms::Panel());
			this->panel7 = (gcnew System::Windows::Forms::Panel());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->WaterMarkScale = (gcnew System::Windows::Forms::NumericUpDown());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->WaterMarkOpacity = (gcnew System::Windows::Forms::NumericUpDown());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->enable_watermark_check = (gcnew System::Windows::Forms::CheckBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->WaterMarkImageName = (gcnew System::Windows::Forms::TextBox());
			this->fontDialog2 = (gcnew System::Windows::Forms::FontDialog());
			this->button_view_website = (gcnew System::Windows::Forms::Button());
			this->folderBrowserDialog2 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->menuStrip1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->panel9->SuspendLayout();
			this->panel12->SuspendLayout();
			this->panel10->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->caption_font_panel->SuspendLayout();
			this->panel11->SuspendLayout();
			this->header_font_panel->SuspendLayout();
			this->panel8->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown4))->BeginInit();
			this->panel6->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->BeginInit();
			this->panel4->SuspendLayout();
			this->panel3->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->tabPage4->SuspendLayout();
			this->panel2->SuspendLayout();
			this->panel1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->tabPage5->SuspendLayout();
			this->panel5->SuspendLayout();
			this->panel7->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->WaterMarkScale))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->WaterMarkOpacity))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			resources->ApplyResources(this->button1, L"button1");
			this->button1->Name = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->toolStripMenuItem1, 
				this->advancedToolStripMenuItem, this->helpToolStripMenuItem});
			resources->ApplyResources(this->menuStrip1, L"menuStrip1");
			this->menuStrip1->Name = L"menuStrip1";
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->generateToolStripMenuItem, 
				this->cancelToolStripMenuItem, this->viewPageToolStripMenuItem, this->toolStripSeparator1, this->exitToolStripMenuItem});
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			resources->ApplyResources(this->toolStripMenuItem1, L"toolStripMenuItem1");
			// 
			// generateToolStripMenuItem
			// 
			this->generateToolStripMenuItem->Name = L"generateToolStripMenuItem";
			resources->ApplyResources(this->generateToolStripMenuItem, L"generateToolStripMenuItem");
			// 
			// cancelToolStripMenuItem
			// 
			resources->ApplyResources(this->cancelToolStripMenuItem, L"cancelToolStripMenuItem");
			this->cancelToolStripMenuItem->Name = L"cancelToolStripMenuItem";
			// 
			// viewPageToolStripMenuItem
			// 
			resources->ApplyResources(this->viewPageToolStripMenuItem, L"viewPageToolStripMenuItem");
			this->viewPageToolStripMenuItem->Name = L"viewPageToolStripMenuItem";
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			resources->ApplyResources(this->toolStripSeparator1, L"toolStripSeparator1");
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			resources->ApplyResources(this->exitToolStripMenuItem, L"exitToolStripMenuItem");
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// advancedToolStripMenuItem
			// 
			this->advancedToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(9) {this->headingFontToolStripMenuItem, 
				this->bodyFontToolStripMenuItem, this->bodyColourToolStripMenuItem, this->toolStripSeparator3, this->addImageFolderToolStripMenuItem, 
				this->includeSubfoldersToolStripMenuItem, this->userCSSToolStripMenuItem, this->toolStripSeparator4, this->restoreDefaultsToolStripMenuItem});
			this->advancedToolStripMenuItem->Name = L"advancedToolStripMenuItem";
			resources->ApplyResources(this->advancedToolStripMenuItem, L"advancedToolStripMenuItem");
			// 
			// headingFontToolStripMenuItem
			// 
			this->headingFontToolStripMenuItem->Name = L"headingFontToolStripMenuItem";
			resources->ApplyResources(this->headingFontToolStripMenuItem, L"headingFontToolStripMenuItem");
			this->headingFontToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::headingFontToolStripMenuItem_Click);
			// 
			// bodyFontToolStripMenuItem
			// 
			this->bodyFontToolStripMenuItem->Name = L"bodyFontToolStripMenuItem";
			resources->ApplyResources(this->bodyFontToolStripMenuItem, L"bodyFontToolStripMenuItem");
			this->bodyFontToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::bodyFontToolStripMenuItem_Click);
			// 
			// bodyColourToolStripMenuItem
			// 
			this->bodyColourToolStripMenuItem->Name = L"bodyColourToolStripMenuItem";
			resources->ApplyResources(this->bodyColourToolStripMenuItem, L"bodyColourToolStripMenuItem");
			this->bodyColourToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::bodyColourToolStripMenuItem_Click);
			// 
			// toolStripSeparator3
			// 
			this->toolStripSeparator3->Name = L"toolStripSeparator3";
			resources->ApplyResources(this->toolStripSeparator3, L"toolStripSeparator3");
			// 
			// addImageFolderToolStripMenuItem
			// 
			this->addImageFolderToolStripMenuItem->Name = L"addImageFolderToolStripMenuItem";
			resources->ApplyResources(this->addImageFolderToolStripMenuItem, L"addImageFolderToolStripMenuItem");
			this->addImageFolderToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::addImageFolderToolStripMenuItem_Click);
			// 
			// includeSubfoldersToolStripMenuItem
			// 
			this->includeSubfoldersToolStripMenuItem->Checked = true;
			this->includeSubfoldersToolStripMenuItem->CheckOnClick = true;
			this->includeSubfoldersToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->includeSubfoldersToolStripMenuItem->Name = L"includeSubfoldersToolStripMenuItem";
			resources->ApplyResources(this->includeSubfoldersToolStripMenuItem, L"includeSubfoldersToolStripMenuItem");
			this->includeSubfoldersToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::includeSubfoldersToolStripMenuItem_Click);
			// 
			// userCSSToolStripMenuItem
			// 
			this->userCSSToolStripMenuItem->Name = L"userCSSToolStripMenuItem";
			resources->ApplyResources(this->userCSSToolStripMenuItem, L"userCSSToolStripMenuItem");
			// 
			// toolStripSeparator4
			// 
			this->toolStripSeparator4->Name = L"toolStripSeparator4";
			resources->ApplyResources(this->toolStripSeparator4, L"toolStripSeparator4");
			// 
			// restoreDefaultsToolStripMenuItem
			// 
			this->restoreDefaultsToolStripMenuItem->Name = L"restoreDefaultsToolStripMenuItem";
			resources->ApplyResources(this->restoreDefaultsToolStripMenuItem, L"restoreDefaultsToolStripMenuItem");
			this->restoreDefaultsToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::restoreDefaultsToolStripMenuItem_Click);
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->releaseNotesToolStripMenuItem, 
				this->aboutToolStripMenuItem});
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			resources->ApplyResources(this->helpToolStripMenuItem, L"helpToolStripMenuItem");
			// 
			// releaseNotesToolStripMenuItem
			// 
			this->releaseNotesToolStripMenuItem->Name = L"releaseNotesToolStripMenuItem";
			resources->ApplyResources(this->releaseNotesToolStripMenuItem, L"releaseNotesToolStripMenuItem");
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			resources->ApplyResources(this->aboutToolStripMenuItem, L"aboutToolStripMenuItem");
			this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::aboutToolStripMenuItem_Click);
			// 
			// imageList1
			// 
			this->imageList1->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^  >(resources->GetObject(L"imageList1.ImageStream")));
			this->imageList1->Tag = L"0";
			this->imageList1->TransparentColor = System::Drawing::Color::White;
			this->imageList1->Images->SetKeyName(0, L"");
			this->imageList1->Images->SetKeyName(1, L"");
			this->imageList1->Images->SetKeyName(2, L"");
			this->imageList1->Images->SetKeyName(3, L"");
			this->imageList1->Images->SetKeyName(4, L"");
			this->imageList1->Images->SetKeyName(5, L"");
			this->imageList1->Images->SetKeyName(6, L"");
			this->imageList1->Images->SetKeyName(7, L"");
			this->imageList1->Images->SetKeyName(8, L"");
			this->imageList1->Images->SetKeyName(9, L"");
			this->imageList1->Images->SetKeyName(10, L"");
			this->imageList1->Images->SetKeyName(11, L"");
			this->imageList1->Images->SetKeyName(12, L"");
			this->imageList1->Images->SetKeyName(13, L"");
			this->imageList1->Images->SetKeyName(14, L"");
			this->imageList1->Images->SetKeyName(15, L"");
			this->imageList1->Images->SetKeyName(16, L"");
			this->imageList1->Images->SetKeyName(17, L"");
			// 
			// fontDialog1
			// 
			this->fontDialog1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 26.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->fontDialog1->ShowApply = true;
			this->fontDialog1->ShowColor = true;
			this->fontDialog1->Apply += gcnew System::EventHandler(this, &Form1::fontDialog1_Apply);
			// 
			// colorDialog1
			// 
			this->colorDialog1->AnyColor = true;
			this->colorDialog1->Color = System::Drawing::Color::Silver;
			// 
			// folderBrowserDialog1
			// 
			this->folderBrowserDialog1->ShowNewFolderButton = false;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->AddExtension = false;
			// 
			// toolTip1
			// 
			this->toolTip1->AutoPopDelay = 5000;
			this->toolTip1->InitialDelay = 0;
			this->toolTip1->ReshowDelay = 100;
			this->toolTip1->ShowAlways = true;
			this->toolTip1->UseAnimation = false;
			this->toolTip1->UseFading = false;
			// 
			// tabPage2
			// 
			this->tabPage2->BackColor = System::Drawing::Color::MediumTurquoise;
			this->tabPage2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->tabPage2->Controls->Add(this->webBrowser1);
			resources->ApplyResources(this->tabPage2, L"tabPage2");
			this->tabPage2->Name = L"tabPage2";
			this->toolTip1->SetToolTip(this->tabPage2, resources->GetString(L"tabPage2.ToolTip"));
			this->tabPage2->UseVisualStyleBackColor = true;
			this->tabPage2->Enter += gcnew System::EventHandler(this, &Form1::tabPage2_Enter);
			// 
			// webBrowser1
			// 
			this->webBrowser1->AllowWebBrowserDrop = false;
			resources->ApplyResources(this->webBrowser1, L"webBrowser1");
			this->webBrowser1->MinimumSize = System::Drawing::Size(27, 25);
			this->webBrowser1->Name = L"webBrowser1";
			this->webBrowser1->WebBrowserShortcutsEnabled = false;
			// 
			// tabPage1
			// 
			this->tabPage1->BackColor = System::Drawing::SystemColors::Control;
			this->tabPage1->Controls->Add(this->if_title);
			this->tabPage1->Controls->Add(this->panel9);
			resources->ApplyResources(this->tabPage1, L"tabPage1");
			this->tabPage1->Name = L"tabPage1";
			this->toolTip1->SetToolTip(this->tabPage1, resources->GetString(L"tabPage1.ToolTip"));
			this->tabPage1->UseVisualStyleBackColor = true;
			this->tabPage1->Leave += gcnew System::EventHandler(this, &Form1::tabPage1_Leave);
			// 
			// if_title
			// 
			this->if_title->BackColor = System::Drawing::SystemColors::Info;
			resources->ApplyResources(this->if_title, L"if_title");
			this->if_title->ForeColor = System::Drawing::SystemColors::InfoText;
			this->if_title->Name = L"if_title";
			// 
			// panel9
			// 
			this->panel9->BackColor = System::Drawing::Color::CornflowerBlue;
			this->panel9->Controls->Add(this->panel12);
			this->panel9->Controls->Add(this->panel10);
			resources->ApplyResources(this->panel9, L"panel9");
			this->panel9->Name = L"panel9";
			// 
			// panel12
			// 
			this->panel12->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel12->Controls->Add(this->labelUserCSS);
			this->panel12->Controls->Add(this->CSSfilename);
			this->panel12->Controls->Add(this->BrowseCSS);
			this->panel12->Controls->Add(this->EnableUserCSSCheck);
			resources->ApplyResources(this->panel12, L"panel12");
			this->panel12->Name = L"panel12";
			// 
			// labelUserCSS
			// 
			resources->ApplyResources(this->labelUserCSS, L"labelUserCSS");
			this->labelUserCSS->Name = L"labelUserCSS";
			// 
			// CSSfilename
			// 
			resources->ApplyResources(this->CSSfilename, L"CSSfilename");
			this->CSSfilename->Name = L"CSSfilename";
			// 
			// BrowseCSS
			// 
			resources->ApplyResources(this->BrowseCSS, L"BrowseCSS");
			this->BrowseCSS->Name = L"BrowseCSS";
			this->BrowseCSS->UseVisualStyleBackColor = true;
			this->BrowseCSS->Click += gcnew System::EventHandler(this, &Form1::BrowseCSS_Click);
			// 
			// EnableUserCSSCheck
			// 
			resources->ApplyResources(this->EnableUserCSSCheck, L"EnableUserCSSCheck");
			this->EnableUserCSSCheck->Name = L"EnableUserCSSCheck";
			this->EnableUserCSSCheck->UseVisualStyleBackColor = true;
			this->EnableUserCSSCheck->Click += gcnew System::EventHandler(this, &Form1::EnableUserCSSCheck_CheckedChanged);
			// 
			// panel10
			// 
			this->panel10->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel10->Controls->Add(this->button4);
			this->panel10->Controls->Add(this->auto_inc_sub_check);
			this->panel10->Controls->Add(this->button3);
			this->panel10->Controls->Add(this->button2);
			this->panel10->Controls->Add(this->listBox1);
			this->panel10->Controls->Add(this->treeView1);
			resources->ApplyResources(this->panel10, L"panel10");
			this->panel10->Name = L"panel10";
			// 
			// button4
			// 
			resources->ApplyResources(this->button4, L"button4");
			this->button4->Name = L"button4";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// auto_inc_sub_check
			// 
			resources->ApplyResources(this->auto_inc_sub_check, L"auto_inc_sub_check");
			this->auto_inc_sub_check->Name = L"auto_inc_sub_check";
			this->auto_inc_sub_check->UseVisualStyleBackColor = true;
			this->auto_inc_sub_check->Click += gcnew System::EventHandler(this, &Form1::checkBox1_Click);
			// 
			// button3
			// 
			resources->ApplyResources(this->button3, L"button3");
			this->button3->Name = L"button3";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// button2
			// 
			resources->ApplyResources(this->button2, L"button2");
			this->button2->Name = L"button2";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			resources->ApplyResources(this->listBox1, L"listBox1");
			this->listBox1->Name = L"listBox1";
			this->listBox1->DoubleClick += gcnew System::EventHandler(this, &Form1::button3_Click);
			this->listBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::listBox1_MouseMove);
			// 
			// treeView1
			// 
			this->treeView1->BackColor = System::Drawing::SystemColors::Window;
			this->treeView1->ForeColor = System::Drawing::SystemColors::ControlText;
			this->treeView1->HideSelection = false;
			resources->ApplyResources(this->treeView1, L"treeView1");
			this->treeView1->ImageList = this->imageList1;
			this->treeView1->ItemHeight = 32;
			this->treeView1->Name = L"treeView1";
			this->treeView1->ShowNodeToolTips = true;
			this->treeView1->DoubleClick += gcnew System::EventHandler(this, &Form1::button2_Click);
			this->treeView1->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &Form1::treeView1_AfterSelect);
			// 
			// topleft
			// 
			resources->ApplyResources(this->topleft, L"topleft");
			this->topleft->BackColor = System::Drawing::Color::Transparent;
			this->topleft->FlatAppearance->BorderColor = System::Drawing::SystemColors::Info;
			this->topleft->FlatAppearance->CheckedBackColor = System::Drawing::Color::White;
			this->topleft->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->topleft->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Red;
			this->topleft->Name = L"topleft";
			this->toolTip1->SetToolTip(this->topleft, resources->GetString(L"topleft.ToolTip"));
			this->topleft->UseVisualStyleBackColor = false;
			// 
			// centerright
			// 
			resources->ApplyResources(this->centerright, L"centerright");
			this->centerright->BackColor = System::Drawing::Color::Transparent;
			this->centerright->FlatAppearance->BorderColor = System::Drawing::SystemColors::Info;
			this->centerright->FlatAppearance->CheckedBackColor = System::Drawing::Color::White;
			this->centerright->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->centerright->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Red;
			this->centerright->Name = L"centerright";
			this->toolTip1->SetToolTip(this->centerright, resources->GetString(L"centerright.ToolTip"));
			this->centerright->UseVisualStyleBackColor = false;
			// 
			// topcenter
			// 
			resources->ApplyResources(this->topcenter, L"topcenter");
			this->topcenter->BackColor = System::Drawing::Color::Transparent;
			this->topcenter->FlatAppearance->BorderColor = System::Drawing::SystemColors::Info;
			this->topcenter->FlatAppearance->CheckedBackColor = System::Drawing::Color::White;
			this->topcenter->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->topcenter->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Red;
			this->topcenter->Name = L"topcenter";
			this->toolTip1->SetToolTip(this->topcenter, resources->GetString(L"topcenter.ToolTip"));
			this->topcenter->UseVisualStyleBackColor = false;
			// 
			// topright
			// 
			resources->ApplyResources(this->topright, L"topright");
			this->topright->BackColor = System::Drawing::Color::Transparent;
			this->topright->FlatAppearance->BorderColor = System::Drawing::SystemColors::Info;
			this->topright->FlatAppearance->CheckedBackColor = System::Drawing::Color::White;
			this->topright->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->topright->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Red;
			this->topright->Name = L"topright";
			this->toolTip1->SetToolTip(this->topright, resources->GetString(L"topright.ToolTip"));
			this->topright->UseVisualStyleBackColor = false;
			// 
			// bottomright
			// 
			resources->ApplyResources(this->bottomright, L"bottomright");
			this->bottomright->BackColor = System::Drawing::Color::Transparent;
			this->bottomright->FlatAppearance->BorderColor = System::Drawing::SystemColors::Info;
			this->bottomright->FlatAppearance->CheckedBackColor = System::Drawing::Color::White;
			this->bottomright->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->bottomright->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Red;
			this->bottomright->Name = L"bottomright";
			this->toolTip1->SetToolTip(this->bottomright, resources->GetString(L"bottomright.ToolTip"));
			this->bottomright->UseVisualStyleBackColor = false;
			// 
			// centerleft
			// 
			resources->ApplyResources(this->centerleft, L"centerleft");
			this->centerleft->BackColor = System::Drawing::Color::Transparent;
			this->centerleft->FlatAppearance->BorderColor = System::Drawing::SystemColors::Info;
			this->centerleft->FlatAppearance->CheckedBackColor = System::Drawing::Color::White;
			this->centerleft->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->centerleft->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Red;
			this->centerleft->Name = L"centerleft";
			this->toolTip1->SetToolTip(this->centerleft, resources->GetString(L"centerleft.ToolTip"));
			this->centerleft->UseVisualStyleBackColor = false;
			// 
			// bottomleft
			// 
			resources->ApplyResources(this->bottomleft, L"bottomleft");
			this->bottomleft->BackColor = System::Drawing::Color::Transparent;
			this->bottomleft->FlatAppearance->BorderColor = System::Drawing::SystemColors::Info;
			this->bottomleft->FlatAppearance->CheckedBackColor = System::Drawing::Color::White;
			this->bottomleft->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->bottomleft->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Red;
			this->bottomleft->Name = L"bottomleft";
			this->toolTip1->SetToolTip(this->bottomleft, resources->GetString(L"bottomleft.ToolTip"));
			this->bottomleft->UseVisualStyleBackColor = false;
			// 
			// bottomcenter
			// 
			resources->ApplyResources(this->bottomcenter, L"bottomcenter");
			this->bottomcenter->BackColor = System::Drawing::Color::Transparent;
			this->bottomcenter->FlatAppearance->BorderColor = System::Drawing::SystemColors::Info;
			this->bottomcenter->FlatAppearance->CheckedBackColor = System::Drawing::Color::White;
			this->bottomcenter->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->bottomcenter->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Red;
			this->bottomcenter->Name = L"bottomcenter";
			this->toolTip1->SetToolTip(this->bottomcenter, resources->GetString(L"bottomcenter.ToolTip"));
			this->bottomcenter->UseVisualStyleBackColor = false;
			// 
			// color_picker_panel
			// 
			this->color_picker_panel->BackColor = System::Drawing::Color::Transparent;
			this->color_picker_panel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			resources->ApplyResources(this->color_picker_panel, L"color_picker_panel");
			this->color_picker_panel->Name = L"color_picker_panel";
			this->toolTip1->SetToolTip(this->color_picker_panel, resources->GetString(L"color_picker_panel.ToolTip"));
			this->color_picker_panel->Click += gcnew System::EventHandler(this, &Form1::bodyColourToolStripMenuItem_Click);
			// 
			// header_font_label
			// 
			this->header_font_label->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			resources->ApplyResources(this->header_font_label, L"header_font_label");
			this->header_font_label->Name = L"header_font_label";
			this->toolTip1->SetToolTip(this->header_font_label, resources->GetString(L"header_font_label.ToolTip"));
			this->header_font_label->Click += gcnew System::EventHandler(this, &Form1::headingFontToolStripMenuItem_Click);
			// 
			// caption_font_label
			// 
			this->caption_font_label->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			resources->ApplyResources(this->caption_font_label, L"caption_font_label");
			this->caption_font_label->Name = L"caption_font_label";
			this->toolTip1->SetToolTip(this->caption_font_label, resources->GetString(L"caption_font_label.ToolTip"));
			this->caption_font_label->Click += gcnew System::EventHandler(this, &Form1::bodyFontToolStripMenuItem_Click);
			// 
			// middle
			// 
			resources->ApplyResources(this->middle, L"middle");
			this->middle->BackColor = System::Drawing::Color::Transparent;
			this->middle->FlatAppearance->BorderColor = System::Drawing::SystemColors::Info;
			this->middle->FlatAppearance->CheckedBackColor = System::Drawing::Color::White;
			this->middle->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->middle->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Red;
			this->middle->Name = L"middle";
			this->middle->UseVisualStyleBackColor = false;
			// 
			// build_website
			// 
			resources->ApplyResources(this->build_website, L"build_website");
			this->build_website->Name = L"build_website";
			this->build_website->UseVisualStyleBackColor = true;
			this->build_website->Click += gcnew System::EventHandler(this, &Form1::build_website_Click);
			// 
			// tabPage3
			// 
			this->tabPage3->BackColor = System::Drawing::Color::LightBlue;
			resources->ApplyResources(this->tabPage3, L"tabPage3");
			this->tabPage3->Controls->Add(this->caption_font_panel);
			this->tabPage3->Controls->Add(this->panel11);
			this->tabPage3->Controls->Add(this->header_font_panel);
			this->tabPage3->Controls->Add(this->bs_title);
			this->tabPage3->Controls->Add(this->panel8);
			this->tabPage3->Controls->Add(this->panel6);
			this->tabPage3->Controls->Add(this->panel4);
			this->tabPage3->Controls->Add(this->panel3);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// caption_font_panel
			// 
			this->caption_font_panel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->caption_font_panel->Controls->Add(this->enable_caption_check);
			this->caption_font_panel->Controls->Add(this->caption_font_label);
			resources->ApplyResources(this->caption_font_panel, L"caption_font_panel");
			this->caption_font_panel->Name = L"caption_font_panel";
			// 
			// enable_caption_check
			// 
			resources->ApplyResources(this->enable_caption_check, L"enable_caption_check");
			this->enable_caption_check->Checked = true;
			this->enable_caption_check->CheckState = System::Windows::Forms::CheckState::Checked;
			this->enable_caption_check->Name = L"enable_caption_check";
			this->enable_caption_check->UseVisualStyleBackColor = true;
			this->enable_caption_check->CheckedChanged += gcnew System::EventHandler(this, &Form1::enable_caption_check_CheckedChanged);
			// 
			// panel11
			// 
			this->panel11->BackColor = System::Drawing::Color::LightBlue;
			this->panel11->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel11->Controls->Add(this->xml_only);
			this->panel11->Controls->Add(this->xhtml_only);
			this->panel11->Controls->Add(this->xml_plus_html);
			resources->ApplyResources(this->panel11, L"panel11");
			this->panel11->Name = L"panel11";
			// 
			// xml_only
			// 
			resources->ApplyResources(this->xml_only, L"xml_only");
			this->xml_only->Name = L"xml_only";
			this->xml_only->TabStop = true;
			this->xml_only->UseVisualStyleBackColor = true;
			this->xml_only->CheckedChanged += gcnew System::EventHandler(this, &Form1::xml_plus_html_Clicked);
			// 
			// xhtml_only
			// 
			resources->ApplyResources(this->xhtml_only, L"xhtml_only");
			this->xhtml_only->Name = L"xhtml_only";
			this->xhtml_only->TabStop = true;
			this->xhtml_only->UseVisualStyleBackColor = true;
			this->xhtml_only->CheckedChanged += gcnew System::EventHandler(this, &Form1::xml_plus_html_Clicked);
			// 
			// xml_plus_html
			// 
			resources->ApplyResources(this->xml_plus_html, L"xml_plus_html");
			this->xml_plus_html->Checked = true;
			this->xml_plus_html->Name = L"xml_plus_html";
			this->xml_plus_html->TabStop = true;
			this->xml_plus_html->UseVisualStyleBackColor = true;
			this->xml_plus_html->CheckedChanged += gcnew System::EventHandler(this, &Form1::xml_plus_html_Clicked);
			// 
			// header_font_panel
			// 
			this->header_font_panel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->header_font_panel->Controls->Add(this->enable_header_check);
			this->header_font_panel->Controls->Add(this->header_font_label);
			resources->ApplyResources(this->header_font_panel, L"header_font_panel");
			this->header_font_panel->Name = L"header_font_panel";
			// 
			// enable_header_check
			// 
			resources->ApplyResources(this->enable_header_check, L"enable_header_check");
			this->enable_header_check->Checked = true;
			this->enable_header_check->CheckState = System::Windows::Forms::CheckState::Checked;
			this->enable_header_check->Name = L"enable_header_check";
			this->enable_header_check->UseVisualStyleBackColor = true;
			this->enable_header_check->CheckedChanged += gcnew System::EventHandler(this, &Form1::enable_header_check_CheckedChanged);
			// 
			// bs_title
			// 
			this->bs_title->BackColor = System::Drawing::SystemColors::Info;
			this->bs_title->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			resources->ApplyResources(this->bs_title, L"bs_title");
			this->bs_title->ForeColor = System::Drawing::SystemColors::InfoText;
			this->bs_title->Name = L"bs_title";
			// 
			// panel8
			// 
			this->panel8->BackColor = System::Drawing::Color::LightBlue;
			this->panel8->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel8->Controls->Add(this->numericUpDown4);
			this->panel8->Controls->Add(this->label10);
			this->panel8->Controls->Add(this->enable_multipage_check);
			resources->ApplyResources(this->panel8, L"panel8");
			this->panel8->Name = L"panel8";
			// 
			// numericUpDown4
			// 
			resources->ApplyResources(this->numericUpDown4, L"numericUpDown4");
			this->numericUpDown4->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->numericUpDown4->Name = L"numericUpDown4";
			this->numericUpDown4->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {16, 0, 0, 0});
			// 
			// label10
			// 
			resources->ApplyResources(this->label10, L"label10");
			this->label10->Name = L"label10";
			// 
			// enable_multipage_check
			// 
			resources->ApplyResources(this->enable_multipage_check, L"enable_multipage_check");
			this->enable_multipage_check->Name = L"enable_multipage_check";
			this->enable_multipage_check->UseVisualStyleBackColor = true;
			this->enable_multipage_check->CheckedChanged += gcnew System::EventHandler(this, &Form1::enable_multipage_check_CheckedChanged);
			// 
			// panel6
			// 
			this->panel6->BackColor = System::Drawing::Color::LightBlue;
			this->panel6->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel6->Controls->Add(this->custom_size);
			this->panel6->Controls->Add(this->default_size);
			this->panel6->Controls->Add(this->thumbnail_label);
			this->panel6->Controls->Add(this->numericUpDown1);
			resources->ApplyResources(this->panel6, L"panel6");
			this->panel6->Name = L"panel6";
			// 
			// custom_size
			// 
			resources->ApplyResources(this->custom_size, L"custom_size");
			this->custom_size->Name = L"custom_size";
			this->custom_size->TabStop = true;
			this->custom_size->UseVisualStyleBackColor = true;
			this->custom_size->CheckedChanged += gcnew System::EventHandler(this, &Form1::custom_size_CheckedChanged);
			// 
			// default_size
			// 
			resources->ApplyResources(this->default_size, L"default_size");
			this->default_size->Name = L"default_size";
			this->default_size->TabStop = true;
			this->default_size->UseVisualStyleBackColor = true;
			this->default_size->CheckedChanged += gcnew System::EventHandler(this, &Form1::default_size_CheckedChanged);
			// 
			// thumbnail_label
			// 
			resources->ApplyResources(this->thumbnail_label, L"thumbnail_label");
			this->thumbnail_label->Name = L"thumbnail_label";
			// 
			// numericUpDown1
			// 
			resources->ApplyResources(this->numericUpDown1, L"numericUpDown1");
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {100, 0, 0, 0});
			// 
			// panel4
			// 
			this->panel4->BackColor = System::Drawing::Color::LightBlue;
			this->panel4->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel4->Controls->Add(this->label3);
			this->panel4->Controls->Add(this->project_name);
			this->panel4->Controls->Add(this->label2);
			this->panel4->Controls->Add(this->webpage_title_text);
			resources->ApplyResources(this->panel4, L"panel4");
			this->panel4->Name = L"panel4";
			// 
			// label3
			// 
			resources->ApplyResources(this->label3, L"label3");
			this->label3->Name = L"label3";
			// 
			// project_name
			// 
			resources->ApplyResources(this->project_name, L"project_name");
			this->project_name->Name = L"project_name";
			this->project_name->TextChanged += gcnew System::EventHandler(this, &Form1::project_name_TextChanged);
			// 
			// label2
			// 
			resources->ApplyResources(this->label2, L"label2");
			this->label2->Name = L"label2";
			// 
			// webpage_title_text
			// 
			resources->ApplyResources(this->webpage_title_text, L"webpage_title_text");
			this->webpage_title_text->Name = L"webpage_title_text";
			this->webpage_title_text->TextChanged += gcnew System::EventHandler(this, &Form1::textBox2_TextChanged);
			// 
			// panel3
			// 
			this->panel3->BackColor = System::Drawing::Color::LightBlue;
			this->panel3->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel3->Controls->Add(this->label1);
			this->panel3->Controls->Add(this->button5);
			this->panel3->Controls->Add(this->textBox1);
			resources->ApplyResources(this->panel3, L"panel3");
			this->panel3->Name = L"panel3";
			// 
			// label1
			// 
			resources->ApplyResources(this->label1, L"label1");
			this->label1->Name = L"label1";
			// 
			// button5
			// 
			resources->ApplyResources(this->button5, L"button5");
			this->button5->Name = L"button5";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &Form1::button5_Click);
			// 
			// textBox1
			// 
			resources->ApplyResources(this->textBox1, L"textBox1");
			this->textBox1->Name = L"textBox1";
			// 
			// tabControl1
			// 
			this->tabControl1->AccessibleRole = System::Windows::Forms::AccessibleRole::PropertyPage;
			resources->ApplyResources(this->tabControl1, L"tabControl1");
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Controls->Add(this->tabPage4);
			this->tabControl1->Controls->Add(this->tabPage5);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->ImageList = this->imageList1;
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			// 
			// tabPage4
			// 
			this->tabPage4->BackColor = System::Drawing::Color::Bisque;
			this->tabPage4->Controls->Add(this->bs2_title);
			this->tabPage4->Controls->Add(this->panel2);
			this->tabPage4->Controls->Add(this->panel1);
			resources->ApplyResources(this->tabPage4, L"tabPage4");
			this->tabPage4->Name = L"tabPage4";
			this->tabPage4->UseVisualStyleBackColor = true;
			this->tabPage4->Leave += gcnew System::EventHandler(this, &Form1::tabPage4_Leave);
			// 
			// bs2_title
			// 
			this->bs2_title->BackColor = System::Drawing::SystemColors::Info;
			this->bs2_title->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			resources->ApplyResources(this->bs2_title, L"bs2_title");
			this->bs2_title->ForeColor = System::Drawing::SystemColors::InfoText;
			this->bs2_title->Name = L"bs2_title";
			// 
			// panel2
			// 
			this->panel2->BackColor = System::Drawing::Color::Bisque;
			this->panel2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel2->Controls->Add(this->button7);
			this->panel2->Controls->Add(this->label5);
			this->panel2->Controls->Add(this->textBox5);
			this->panel2->Controls->Add(this->EnableBannerImageCheck);
			resources->ApplyResources(this->panel2, L"panel2");
			this->panel2->Name = L"panel2";
			// 
			// button7
			// 
			resources->ApplyResources(this->button7, L"button7");
			this->button7->Name = L"button7";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &Form1::button7_Click);
			// 
			// label5
			// 
			resources->ApplyResources(this->label5, L"label5");
			this->label5->Name = L"label5";
			// 
			// textBox5
			// 
			resources->ApplyResources(this->textBox5, L"textBox5");
			this->textBox5->Name = L"textBox5";
			// 
			// EnableBannerImageCheck
			// 
			resources->ApplyResources(this->EnableBannerImageCheck, L"EnableBannerImageCheck");
			this->EnableBannerImageCheck->Name = L"EnableBannerImageCheck";
			this->EnableBannerImageCheck->UseVisualStyleBackColor = true;
			this->EnableBannerImageCheck->CheckedChanged += gcnew System::EventHandler(this, &Form1::EnableBannerImage_CheckedChanged);
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::Bisque;
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel1->Controls->Add(this->background_color_label);
			this->panel1->Controls->Add(this->color_picker_panel);
			this->panel1->Controls->Add(this->button6);
			this->panel1->Controls->Add(this->no_tiling);
			this->panel1->Controls->Add(this->groupBox2);
			this->panel1->Controls->Add(this->label4);
			this->panel1->Controls->Add(this->textBox4);
			this->panel1->Controls->Add(this->EnableBackgroundImageCheck);
			this->panel1->Controls->Add(this->v_h_tiling);
			this->panel1->Controls->Add(this->groupBox1);
			this->panel1->Controls->Add(this->horizontal_tiling);
			this->panel1->Controls->Add(this->vertical_tiling);
			resources->ApplyResources(this->panel1, L"panel1");
			this->panel1->Name = L"panel1";
			// 
			// background_color_label
			// 
			resources->ApplyResources(this->background_color_label, L"background_color_label");
			this->background_color_label->BackColor = System::Drawing::Color::Transparent;
			this->background_color_label->Name = L"background_color_label";
			// 
			// button6
			// 
			resources->ApplyResources(this->button6, L"button6");
			this->button6->Name = L"button6";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &Form1::button6_Click);
			// 
			// no_tiling
			// 
			resources->ApplyResources(this->no_tiling, L"no_tiling");
			this->no_tiling->Name = L"no_tiling";
			this->no_tiling->TabStop = true;
			this->no_tiling->UseVisualStyleBackColor = true;
			this->no_tiling->Click += gcnew System::EventHandler(this, &Form1::no_tiling_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->left);
			this->groupBox2->Controls->Add(this->h_center);
			this->groupBox2->Controls->Add(this->right);
			resources->ApplyResources(this->groupBox2, L"groupBox2");
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->TabStop = false;
			// 
			// left
			// 
			resources->ApplyResources(this->left, L"left");
			this->left->Name = L"left";
			this->left->TabStop = true;
			this->left->UseVisualStyleBackColor = true;
			// 
			// h_center
			// 
			resources->ApplyResources(this->h_center, L"h_center");
			this->h_center->Name = L"h_center";
			this->h_center->TabStop = true;
			this->h_center->UseVisualStyleBackColor = true;
			// 
			// right
			// 
			resources->ApplyResources(this->right, L"right");
			this->right->Name = L"right";
			this->right->TabStop = true;
			this->right->UseVisualStyleBackColor = true;
			// 
			// label4
			// 
			resources->ApplyResources(this->label4, L"label4");
			this->label4->Name = L"label4";
			// 
			// textBox4
			// 
			resources->ApplyResources(this->textBox4, L"textBox4");
			this->textBox4->Name = L"textBox4";
			// 
			// EnableBackgroundImageCheck
			// 
			resources->ApplyResources(this->EnableBackgroundImageCheck, L"EnableBackgroundImageCheck");
			this->EnableBackgroundImageCheck->Name = L"EnableBackgroundImageCheck";
			this->EnableBackgroundImageCheck->UseVisualStyleBackColor = true;
			this->EnableBackgroundImageCheck->CheckedChanged += gcnew System::EventHandler(this, &Form1::EnableBackgroundImage_CheckedChanged);
			// 
			// v_h_tiling
			// 
			resources->ApplyResources(this->v_h_tiling, L"v_h_tiling");
			this->v_h_tiling->Name = L"v_h_tiling";
			this->v_h_tiling->TabStop = true;
			this->v_h_tiling->UseVisualStyleBackColor = true;
			this->v_h_tiling->Click += gcnew System::EventHandler(this, &Form1::v_h_tiling_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->bottom);
			this->groupBox1->Controls->Add(this->v_center);
			this->groupBox1->Controls->Add(this->top);
			resources->ApplyResources(this->groupBox1, L"groupBox1");
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->TabStop = false;
			// 
			// bottom
			// 
			resources->ApplyResources(this->bottom, L"bottom");
			this->bottom->Name = L"bottom";
			this->bottom->TabStop = true;
			this->bottom->UseVisualStyleBackColor = true;
			// 
			// v_center
			// 
			resources->ApplyResources(this->v_center, L"v_center");
			this->v_center->Name = L"v_center";
			this->v_center->TabStop = true;
			this->v_center->UseVisualStyleBackColor = true;
			// 
			// top
			// 
			resources->ApplyResources(this->top, L"top");
			this->top->Name = L"top";
			this->top->TabStop = true;
			this->top->UseVisualStyleBackColor = true;
			// 
			// horizontal_tiling
			// 
			resources->ApplyResources(this->horizontal_tiling, L"horizontal_tiling");
			this->horizontal_tiling->Name = L"horizontal_tiling";
			this->horizontal_tiling->TabStop = true;
			this->horizontal_tiling->UseVisualStyleBackColor = true;
			this->horizontal_tiling->Click += gcnew System::EventHandler(this, &Form1::horizontal_tiling_Click);
			// 
			// vertical_tiling
			// 
			resources->ApplyResources(this->vertical_tiling, L"vertical_tiling");
			this->vertical_tiling->Name = L"vertical_tiling";
			this->vertical_tiling->TabStop = true;
			this->vertical_tiling->UseVisualStyleBackColor = true;
			this->vertical_tiling->Click += gcnew System::EventHandler(this, &Form1::vertical_tiling_Click);
			// 
			// tabPage5
			// 
			this->tabPage5->BackColor = System::Drawing::Color::Thistle;
			this->tabPage5->Controls->Add(this->wms_title);
			this->tabPage5->Controls->Add(this->panel5);
			resources->ApplyResources(this->tabPage5, L"tabPage5");
			this->tabPage5->Name = L"tabPage5";
			this->tabPage5->Leave += gcnew System::EventHandler(this, &Form1::tabPage5_Leave);
			// 
			// wms_title
			// 
			this->wms_title->BackColor = System::Drawing::SystemColors::Info;
			this->wms_title->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			resources->ApplyResources(this->wms_title, L"wms_title");
			this->wms_title->ForeColor = System::Drawing::SystemColors::InfoText;
			this->wms_title->Name = L"wms_title";
			// 
			// panel5
			// 
			this->panel5->BackColor = System::Drawing::Color::Thistle;
			this->panel5->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel5->Controls->Add(this->panel7);
			this->panel5->Controls->Add(this->label9);
			this->panel5->Controls->Add(this->WaterMarkScale);
			this->panel5->Controls->Add(this->label8);
			this->panel5->Controls->Add(this->WaterMarkOpacity);
			this->panel5->Controls->Add(this->label7);
			this->panel5->Controls->Add(this->enable_watermark_check);
			this->panel5->Controls->Add(this->label6);
			this->panel5->Controls->Add(this->button8);
			this->panel5->Controls->Add(this->WaterMarkImageName);
			resources->ApplyResources(this->panel5, L"panel5");
			this->panel5->Name = L"panel5";
			// 
			// panel7
			// 
			resources->ApplyResources(this->panel7, L"panel7");
			this->panel7->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel7->Controls->Add(this->topleft);
			this->panel7->Controls->Add(this->centerright);
			this->panel7->Controls->Add(this->topcenter);
			this->panel7->Controls->Add(this->middle);
			this->panel7->Controls->Add(this->topright);
			this->panel7->Controls->Add(this->bottomright);
			this->panel7->Controls->Add(this->centerleft);
			this->panel7->Controls->Add(this->bottomleft);
			this->panel7->Controls->Add(this->bottomcenter);
			this->panel7->Name = L"panel7";
			// 
			// label9
			// 
			resources->ApplyResources(this->label9, L"label9");
			this->label9->Name = L"label9";
			// 
			// WaterMarkScale
			// 
			resources->ApplyResources(this->WaterMarkScale, L"WaterMarkScale");
			this->WaterMarkScale->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 131072});
			this->WaterMarkScale->Name = L"WaterMarkScale";
			this->WaterMarkScale->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {2, 0, 0, 65536});
			// 
			// label8
			// 
			resources->ApplyResources(this->label8, L"label8");
			this->label8->Name = L"label8";
			// 
			// WaterMarkOpacity
			// 
			resources->ApplyResources(this->WaterMarkOpacity, L"WaterMarkOpacity");
			this->WaterMarkOpacity->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 131072});
			this->WaterMarkOpacity->Name = L"WaterMarkOpacity";
			this->WaterMarkOpacity->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {2, 0, 0, 65536});
			// 
			// label7
			// 
			resources->ApplyResources(this->label7, L"label7");
			this->label7->Name = L"label7";
			// 
			// enable_watermark_check
			// 
			resources->ApplyResources(this->enable_watermark_check, L"enable_watermark_check");
			this->enable_watermark_check->Name = L"enable_watermark_check";
			this->enable_watermark_check->UseVisualStyleBackColor = true;
			this->enable_watermark_check->CheckedChanged += gcnew System::EventHandler(this, &Form1::enable_watermark_check_CheckedChanged);
			// 
			// label6
			// 
			resources->ApplyResources(this->label6, L"label6");
			this->label6->Name = L"label6";
			// 
			// button8
			// 
			resources->ApplyResources(this->button8, L"button8");
			this->button8->Name = L"button8";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &Form1::button8_Click);
			// 
			// WaterMarkImageName
			// 
			resources->ApplyResources(this->WaterMarkImageName, L"WaterMarkImageName");
			this->WaterMarkImageName->Name = L"WaterMarkImageName";
			// 
			// fontDialog2
			// 
			this->fontDialog2->Font = (gcnew System::Drawing::Font(L"Tahoma", 10));
			this->fontDialog2->ShowApply = true;
			this->fontDialog2->ShowColor = true;
			this->fontDialog2->Apply += gcnew System::EventHandler(this, &Form1::fontDialog2_Apply);
			// 
			// button_view_website
			// 
			resources->ApplyResources(this->button_view_website, L"button_view_website");
			this->button_view_website->Name = L"button_view_website";
			this->button_view_website->UseVisualStyleBackColor = true;
			this->button_view_website->Click += gcnew System::EventHandler(this, &Form1::button_view_website_Click);
			// 
			// folderBrowserDialog2
			// 
			this->folderBrowserDialog2->ShowNewFolderButton = false;
			// 
			// Form1
			// 
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->button_view_website);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->build_website);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->menuStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MainMenuStrip = this->menuStrip1;
			this->MaximizeBox = false;
			this->Name = L"Form1";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->tabPage2->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->panel9->ResumeLayout(false);
			this->panel12->ResumeLayout(false);
			this->panel12->PerformLayout();
			this->panel10->ResumeLayout(false);
			this->panel10->PerformLayout();
			this->tabPage3->ResumeLayout(false);
			this->caption_font_panel->ResumeLayout(false);
			this->caption_font_panel->PerformLayout();
			this->panel11->ResumeLayout(false);
			this->panel11->PerformLayout();
			this->header_font_panel->ResumeLayout(false);
			this->header_font_panel->PerformLayout();
			this->panel8->ResumeLayout(false);
			this->panel8->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown4))->EndInit();
			this->panel6->ResumeLayout(false);
			this->panel6->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->EndInit();
			this->panel4->ResumeLayout(false);
			this->panel4->PerformLayout();
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			this->tabControl1->ResumeLayout(false);
			this->tabPage4->ResumeLayout(false);
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->tabPage5->ResumeLayout(false);
			this->panel5->ResumeLayout(false);
			this->panel5->PerformLayout();
			this->panel7->ResumeLayout(false);
			this->panel7->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->WaterMarkScale))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->WaterMarkOpacity))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Boolean SetParameters(CLProxy^ parameters);
private: bool PassFoldersToParameter(CLProxy^ cl);
private: System::Void finalise_input_folders_tab();
private: System::Void finalise_background_tab();
private: System::Void finalise_watermark_tab();
private: System::Void finalise_settings_tab();


private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void headingFontToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) ;
private: System::Void bodyFontToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) ;
private: System::Void bodyColourToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e); 
private: System::Void backgroundImageToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) ;
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e);
private: System::Void LoadPreview();
private: System::Void LoadInitialFolder();
private: System::Void treeView1_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e);
private: System::Void treeView1_MyComputer() ;
private: System::Void treeView1_folders() ;
private: System::Void listBox1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
private: System::Void checkBox1_Click(System::Object^  sender, System::EventArgs^  e) ;
private: System::Void includeSubfoldersToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void tabPage2_Enter(System::Object^  sender, System::EventArgs^  e);
private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void bannerImageToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void fontDialog1_Apply(System::Object^  sender, System::EventArgs^  e);
private: System::Void fontDialog2_Apply(System::Object^  sender, System::EventArgs^  e);
private: System::Void restoreDefaultsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void aboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void EnableBackgroundImage_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void v_h_tiling_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void no_tiling_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void horizontal_tiling_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void vertical_tiling_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void tabPage4_Leave(System::Object^  sender, System::EventArgs^  e);
private: System::Void tabPage5_Leave(System::Object^  sender, System::EventArgs^  e);
private: System::Void EnableBannerImage_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void enable_watermark_check_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void default_size_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void custom_size_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void button8_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void enable_multipage_check_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void xml_plus_html_Clicked(System::Object^  sender, System::EventArgs^  e);
private: System::Void enable_header_check_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void enable_caption_check_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void project_name_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void build_website_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void EnableUserCSSCheck_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void BrowseCSS_Click(System::Object^  sender, System::EventArgs^  e); 
private: System::Void tabPage1_Leave(System::Object^  sender, System::EventArgs^  e);
private: System::Void button_view_website_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void addImageFolderToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);

};
}