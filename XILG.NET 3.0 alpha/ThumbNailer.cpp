// ThumbNailer.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
//#pragma warning(disable:4786)
#include "ThumbNailer.h"
#include "CommandLine.h"
#include "ImageFileList.h"
#include "WriteXMLFile.h"
#include "css_file.h"
#include "FolderBuilder.h"
#include "ImageCopier.h"
#include "Thumbcreator.h"
#include "PictureHandler.h"

// Nasty global for detailed error messages
bool diagnostic = false;

int main(int argc, char* argv[])
{
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	try
	{
		std::wcout << L"ThumbNailer : XILG for the command line. Version 1.00 alpha." << std::endl; 
		////////////////////////////////////////////////////////////
		// Do we enable diagnostics??
		// Must be seperate from CommandLine handling
		// to allow debug info from the CommandLine class
		std::wstring cmd_line = GetCommandLine();
		if (cmd_line.find(switch_diagnostic) != std::wstring::npos)
			diagnostic = true;
		/////////////////////////////////////////////////////////////

		CommandLine cl;

		if (cl.NoHTML() && cl.OnlyHTML())
		{
			std::wstring xilgerr = L"You specified -nohtml & -onlyhtml!\n";
			throw(xilg_error(xilgerr));
		}

		ImageFileList ifl;
		ifl.SetPathInfo(cl);
		ifl.GatherImageNames();

		FolderBuilder fb;
		fb.build(cl,ifl);

		test_hr(CoInitialize(NULL)); 

		ImageCopier ic;
		ic.copy(cl,ifl);

        ThumbCreator tc;
		tc.MakeAndSaveThumbs(cl,ifl);
		std::pair<int,int> bts = tc.BiggestImageDimensions();
		
		basic_xmlfile* bmx = new xml_image_list;
		bmx->build(cl,ifl);
		delete bmx;

		bmx = new xsl_image_list;
		bmx->build(cl,ifl);
		delete bmx;

		css_file cf;
		cf.BiggestThumbSize(bts);
		cf.build(cl);

		if (!cl.NoHTML())
		{
			bmx = new WebPageBuilder();
			bmx->build(cl,ifl);
			delete bmx;
		}
	}
	catch (_com_error &e)
	{
		std::wcerr << L"Error:\n"
		           << L"Code = " << e.Error() << std::endl
		           << L"Code meaning = " << e.ErrorMessage() << std::endl
		           << L"Source = " << (wchar_t*)e.Source() << std::endl
		           << L"Error Description " << (wchar_t*)e.Description() << std::endl;
	}
	catch (xilg_error e)
	{
		std::wcerr << L"Error: " << e.message() << std::endl << std::endl;
		if (!::diagnostic)
			ShowCMDOptions();
	}
	catch (help)
	{
		ShowCMDOptions();
	}
	catch(...)
	{
		ShowCMDOptions();
		std::wcerr  << std::endl << L"Unknown error!";
	}
	CoUninitialize();
	return 0;
}


void ShowCMDOptions(void)
{
	std::wcout 	<< std::endl
		<< L"Usage:" << std::endl
		<< L"\tThumbNailer -i <images path> -o <output folder> [options]" << std::endl << std::endl
		<< L"Options:" 
		<< L"\n\t-?\t\t\tDisplay this message"
		<< L"\n\t-i <path>\t\tPath to images folder"
		<< L"\n\t-s <path>\t\tLook in subfolders too"
		<< L"\n\t-o <path>\t\tOutput folder"
		<< L"\n\t-p <name>\t\tProject name"
		<< L"\n\t-t <title>\t\tWeb page title"
		<< L"\n\t-h <integer>\t\tMaximum thumbnail height"
		<< L"\n\t-w <integer>\t\tMaximum thumbnail width"
		<< L"\n\t-mipp <integer>\t\tMaximum images per page (multiple pages)"
		<< L"\n\t-ic\t\t\tWeb page uses an internal CSS stylesheet"
		<< L"\n\t-verbose\t\tDetailed output during processing"
		<< L"\n\t-diagnostic\t\tExtra debug info on errors"
		<< L"\n\t-css <filename>\t\tUser specified external CSS stylesheet"
		<< L"\n\t-nc\t\t\tDo not create new folders - may cause failure!"
		<< L"\n\t-nohtml\t\t\tDo not generate HTML"
		<< L"\n\t-onlyhtml\t\tremove XML & XSL intermediate files"
		<< L"\n\t-nocaption\t\tDo not add a caption under the image"
		<< L"\n\n\t-watermark <image>\tWatermark the large image with <image>"
		<< L"\n\t-wmalpha 0.n\t\tWatermark opacity 0.1 - 1.0. Default 0.2"
		<< L"\n\t-wmscale 0.n\t\tWatermark relative size 0.1 - 1.0. Default 0.2"
		<< L"\n\t-wmpos <tl|tc|tr|cr|centre|cl|bl|bc|br>\n\t\t\t\tPosition the watermark. Default \"br\""
		<< L"\n\n\t-hcolor <CSS color>\tColour of the web page text. Default \"black\""
		<< L"\n\t-hbcolor <CSS color> \tBackground page colour. Default \"silver\""
		<< L"\n\t-hbimage <filename>\tBackground image for the webpage"
		<< L"\n\t-hbimpos <CSS position>\tCSS Position for background image"
		<< L"\n\t-hbimrep <CSS repeat>\tCSS How the background repeats"
		<< L"\n"
		<< L"\n\t-h1color <CSS color>\tColour of the headline text"
		<< L"\n\t-h1size <CSS size>\tSize of the headline font"
		<< L"\n\t-h1font <\"font\">\tName of the headline font"
		<< L"\n\t-h1weight <CSS weight>\tWeight the headline font"
		<< L"\n\t-h1style <CSS style>\tStyle of the headline font"
		<< L"\n"
		<< L"\n\t-acolor <CSS color>\tColour of the caption text"
		<< L"\n\t-asize <CSS size>\tSize of the caption font"
		<< L"\n\t-afont <\"font\">\t\tName of the caption font"
		<< L"\n\t-aweight <CSS weight>\tWeight of the caption font"
		<< L"\n\t-astyle <CSS style>\tStyle of the caption font"
		<< std::endl;
}


