#include "StdAfx.h"
#include "progress_dialog.h"


namespace XILGNET30alpha {

System::Void progress_dialog::LoadParameters(CLProxy^ clp)
{
	params = clp;
}

System::Void progress_dialog::ProxyToCommand(CommandLine& cl)
{
	pin_ptr<const wchar_t> p;

	p = PtrToStringChars(params->acolor);
	cl.AColor(p);

	p = PtrToStringChars(params->afont);
	cl.AFont(p);

	p = PtrToStringChars(params->asize);
	cl.ASize(p);

	p = PtrToStringChars(params->astyle);	
	cl.AStyle(p);

	p = PtrToStringChars(params->aweight);
	cl.AWeight(p);

	p = PtrToStringChars(params->astrike);
	cl.AStrike(p);

	p = PtrToStringChars(params->aunderline);
	cl.AUnderline(p);

	cl.PathCreate(params->create_path);
	cl.InternalCSS(params->internal_css);

	p = PtrToStringChars(params->h1color);
	cl.H1Color(p);

	p = PtrToStringChars(params->h1font);
	cl.H1Font(p);

	p = PtrToStringChars(params->h1size);
	cl.H1Size(p);
	
	p = PtrToStringChars(params->h1style);
	cl.H1Style(p);
	
	p = PtrToStringChars(params->h1weight);
	cl.H1Weight(p);

	p = PtrToStringChars(params->h1strike);
	cl.H1Strike(p);

	p = PtrToStringChars(params->h1underline);
	cl.H1Underline(p);

	p = PtrToStringChars(params->html_background_color);
	cl.HtmlBackgroundColor(p);

	cl.NoHTML(params->no_html);
	cl.OnlyHTML(params->only_html);
	cl.NoCaption(params->no_caption);
	cl.Recurse(params->recurse);
	
	p = PtrToStringChars(params->banner);
	cl.BannerImage(p);

	cl.BannerHeight(params->banner_height);

	p = PtrToStringChars(params->usercss);
	cl.UserCSS(p);

	p = PtrToStringChars(params->html_background_image_position);
	cl.HtmlBackgroundImagePosition(p);

	p = PtrToStringChars(params->html_background_image_repeat);
	cl.HtmlBackgroundImageRepeat(p);

	p = PtrToStringChars(params->html_background_image);
	cl.HtmlBackgroundImage(p);

	cl.ImagesPerPage(params->pics_per_page);

	p = PtrToStringChars(params->page_title);
	cl.PageTitle(p);

	p = PtrToStringChars(params->water_mark);
	cl.WaterMark(p);
	cl.WatermarkAlpha(params->wm_alpha);
	cl.WatermarkPosition(params->pos);
	cl.WatermarkScale(params->wm_scale);

	int count = params->input_paths->Count;
	for (int x = 0; x < count; x++)
	{
		p = PtrToStringChars(params->input_paths[x]);
		cl.InputPath(p);
	}

	p = PtrToStringChars(params->project_name);
	cl.ProjectName(p);

	String^ op = params->output_path + L"\\" + params->project_name;
	p = PtrToStringChars(op);
	cl.OutputPath(p);

	cl.Verbose(false);
}

System::Void progress_dialog::progress_dialog_Load(System::Object^  sender, System::EventArgs^  e) 
{

	backgroundWorker1->RunWorkerAsync();

}


System::Void progress_dialog::backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) 
{
	CommandLine cl(L"XILG");
	ProxyToCommand(cl);

	try
	{
		ImageFileList ifl;
		ifl.SetPathInfo(cl);
		ifl.GatherImageNames();

		int numpics = ifl.NumberOfImages();

		FolderBuilder fb;
		fb.build(cl,ifl);

		if (backgroundWorker1->CancellationPending)
			return;

		ImageCopier ic;
		
		if (params->html_background_image!= String::Empty)
			ic.BackgroundCopy(cl,ifl);

		if (params->banner!=String::Empty)
			ic.BannerCopy(cl,ifl);

		if (backgroundWorker1->CancellationPending)
			return;

		for (int count1 = 0; count1 < numpics; count1++)
		{
			ic.copy_one_at_a_time(cl,ifl,count1);
			backgroundWorker1->ReportProgress((int)((100.0f/(float)numpics)*count1));

			if (backgroundWorker1->CancellationPending)
				return;

		}
		backgroundWorker1->ReportProgress(100);
		backgroundWorker1->ReportProgress(0);



        ThumbCreator tc;
/*
		tc.MakeAndSaveThumbs(cl,ifl);
*/
		for (int count1 = 0; count1 < numpics; count1++)
		{
			tc.MakeAndSaveThumbsSlowly(cl,ifl,count1);
			backgroundWorker1->ReportProgress((int)((100.0f/(float)numpics)*count1));

			if (backgroundWorker1->CancellationPending)
				return;

		}
		backgroundWorker1->ReportProgress(100);
		backgroundWorker1->ReportProgress(0);

		std::pair<int,int> bts = tc.BiggestImageDimensions();
		
		basic_xmlfile* bmx = new xml_image_list;
		bmx->build(cl,ifl);
		delete bmx;

		if (backgroundWorker1->CancellationPending)
			return;


		backgroundWorker1->ReportProgress(25);

		bmx = new xsl_image_list;
		bmx->build(cl,ifl);
		delete bmx;

		if (backgroundWorker1->CancellationPending)
			return;


		backgroundWorker1->ReportProgress(50);

		css_file cf;
		cf.BiggestThumbSize(bts);
		cf.build(cl);

		if (backgroundWorker1->CancellationPending)
			return;


		backgroundWorker1->ReportProgress(75);

		if (!cl.NoHTML())
		{
			bmx = new WebPageBuilder();
			bmx->build(cl,ifl);
			delete bmx;

			if (backgroundWorker1->CancellationPending)
				return;


		}

		backgroundWorker1->ReportProgress(100);

	}
	catch (xilg_error e)
	{
		String^ Error = L"Error";
		Error += gcnew String(e.message().c_str());
		MessageBox::Show(Error,
							L"XILG has encountered a problem",
							MessageBoxButtons::OK, 
							MessageBoxIcon::Exclamation);
	}
	catch (Exception^ e)
	{
		MessageBox::Show(e->Message,
							L"XILG has encountered a problem",
							MessageBoxButtons::OK, 
							MessageBoxIcon::Exclamation);
	}
	catch(...)
	{
		String^ Error = L"Error: Unexpected problem!";
		MessageBox::Show(Error,	L"XILG has found a problem",
							MessageBoxButtons::OK, 
							MessageBoxIcon::Exclamation);
	}
}

System::Void progress_dialog::backgroundWorker1_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) 
{
//	progress_dialog::Close();
	this->Text = L"Finished!";
	cancel_build->Text = "Close";
}

System::Void progress_dialog::cancel_build_Click(System::Object^  sender, System::EventArgs^  e) 
{
	if (backgroundWorker1->IsBusy)
		backgroundWorker1->CancelAsync();

	progress_dialog::Close();
}

System::Void progress_dialog::backgroundWorker1_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e) 
{
	if (progress_picture_copy->Value < 100)
	{
		progress_picture_copy->Value = e->ProgressPercentage;
		return;
	}
	if (progress_thumbnail_creation->Value < 100)
	{
		progress_thumbnail_creation->Value = e->ProgressPercentage;
		return;
	}
	if (progress_site_building->Value < 100)
	{
		progress_site_building->Value = e->ProgressPercentage;
		return;
	}
}


} // END OF NAMESPACE


