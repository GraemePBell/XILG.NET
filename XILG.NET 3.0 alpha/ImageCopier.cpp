// ImageCopier.cpp: implementation of the ImageCopier class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ImageCopier.h"
#include "WaterMarker.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ImageCopier::ImageCopier()
{
	// Get the CLSID of the JPEG encoder.
	GetEncoderClsid(L"image/jpeg", &encoderClsid);
	tick = 0;
}

ImageCopier::~ImageCopier()
{

}

const int ImageCopier::Ticker() const
{
	return tick;
}

void ImageCopier::copy(const CommandLine &cl, const ImageFileList &ifl)
{
	if (!cl.Verbose())
		std::wcout << L"\nCopying";

	unsigned int file_count = 0;
	DWORD bufsize = MAX_PATH;
	wchar_t buf[MAX_PATH];
	bool watermark = (cl.WaterMark() != L"");
	bool background = (cl.HtmlBackgroundImage() != L"");
	bool banner = (cl.BannerImage() != L"");
		
	std::list<ImageNames> i_names = ifl.RetrieveImageNames();
	std::list<ImageNames>::iterator  first = i_names.begin();
	std::list<ImageNames>::size_type max_items = i_names.size();

	if (watermark)
	{
		wm = new WaterMarker;
	}
	if (background)
	{
		BackgroundCopy(cl,ifl);
	}
	if (banner)
	{
		BannerCopy(cl,ifl);
	}

 	
	for (file_count = 0; file_count < max_items; file_count++)
	{
		image_src = (*first).GetOriginalPath() / (*first).GetOriginalName();
		image_dst = ifl.GetBigPath() / (*first).GetLargeImageName();
	
		GetFullPathName(image_dst.c_str(),bufsize,buf,0);
		image_dst = buf;
		image_dst.replace_extension(L".jpg");

		if (cl.Verbose())
			std::wcout << L"Copying " << image_src << L" to " << image_dst;

		Gdiplus::Bitmap i(image_src.c_str());

		if (watermark)
		{
			CLSID encoder = encoderClsid;
			wm->Save(image_dst,cl,i,encoder);
		}
		else
		{
			i.Save(image_dst.c_str(),&encoderClsid, NULL);
		}
		if (cl.Verbose())
			std::wcout << L" ... done" << std::endl;
		else
			std::wcout << L".";
		first++;
	}

	if (watermark)
	{
		delete wm;
	}
	if (!cl.Verbose())
		std::wcout << std::endl;
}


void ImageCopier::copy_one_at_a_time(const CommandLine &cl, const ImageFileList &ifl, unsigned int index)
{
	unsigned int file_count = 0;
	DWORD bufsize = MAX_PATH;
	wchar_t buf[MAX_PATH];

	bool watermark = (cl.WaterMark() != L"");
		
	std::list<ImageNames> i_names = ifl.RetrieveImageNames();
	std::list<ImageNames>::iterator  first = i_names.begin();
	// std::list<ImageNames>::size_type max_items = i_names.size();

	if (watermark)
	{
		wm = new WaterMarker;
	}

	for (file_count = 0; file_count < index; file_count++)
	{
		first++;
	}

	image_src = (*first).GetOriginalPath() / (*first).GetOriginalName();
	image_dst = ifl.GetBigPath() / (*first).GetLargeImageName();
	
	GetFullPathName(image_dst.c_str(),bufsize,buf,0);
	image_dst = buf;
	image_dst.replace_extension(L".jpg");

	Gdiplus::Bitmap i(image_src.c_str());

	if (watermark)
	{
		CLSID encoder = encoderClsid;
		wm->Save(image_dst,cl,i,encoder);
	}
	else
	{
		i.Save(image_dst.c_str(),&encoderClsid, NULL);
	}
}



void ImageCopier::BackgroundCopy(const CommandLine &cl, const ImageFileList &ifl)
{
	path src = cl.HtmlBackgroundImage();
	path temp = PathFindFileName(src.c_str());
	path dest = ifl.GetBigPath() / temp;

	if (!CopyFile(src.c_str(),dest.c_str(),false))
	{
		std::wstring xilgerr = L"Failed to copy background image to destination folder";
		std::wstring xilgerr_line = stringer(__LINE__);
		std::wstring xilgerr_file = widen(__FILE__);
		throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
	}
	else
	{
		const_cast<CommandLine&>(cl).HtmlBackgroundImage(dest);
	}
}

void ImageCopier::BannerCopy(const CommandLine &cl, const ImageFileList &ifl)
{
	path src = cl.BannerImage();
	path temp = PathFindFileName(src.c_str());
	path dest = ifl.GetBigPath() / temp;

	if (!CopyFile(src.c_str(),dest.c_str(),false))
	{
		std::wstring xilgerr = L"Failed to copy background image to destination folder";
		std::wstring xilgerr_line = stringer(__LINE__);
		std::wstring xilgerr_file = widen(__FILE__);
		throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
	}
	else
	{
		Gdiplus::Image i(dest.c_str());
		unsigned int banner_height = i.GetHeight();

		const_cast<CommandLine&>(cl).BannerHeight(banner_height);
		const_cast<CommandLine&>(cl).BannerImage(dest);
	}
}
