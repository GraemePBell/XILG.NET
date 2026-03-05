// ThumbCreator.cpp: implementation of the ThumbCreator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ThumbCreator.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ThumbCreator::ThumbCreator()
{
}

ThumbCreator::~ThumbCreator()
{
}


void ThumbCreator::MakeAndSaveThumbs(const CommandLine &cl, const ImageFileList &ifl)
{
	if (!cl.Verbose())
		std::wcout << L"Making Thumbnails";
	
	unsigned int file_count = 0;
	DWORD bufsize = MAX_PATH;
	wchar_t buf[MAX_PATH];
	CLSID   encoderClsid;
	int xres;
	int yres;
		
	typedef std::list<ImageNames>::iterator IN_iter;

	std::list<ImageNames> i_names = ifl.RetrieveImageNames();

	IN_iter first = i_names.begin();

	std::list<ImageNames>::size_type max_items = i_names.size();

	// Get the CLSID of the JPEG encoder.
	GetEncoderClsid(L"image/jpeg", &encoderClsid);

 	for (file_count = 0; file_count < max_items; file_count++)
	{
		image_src = (*first).GetOriginalPath() + (*first).GetOriginalName();
		image_dst = ifl.GetThumbPath() + (*first).GetThumbnailImageName();
	
		GetFullPathName(image_dst.c_str(),bufsize,buf,0);
		image_dst = buf;

		if (cl.Verbose())
			std::wcout << L"Making Thumbnail of " << image_src << L" in " << image_dst;
		else
			std::wcout << L".";

		Gdiplus::Bitmap i(image_src.c_str());
		if (i.GetHeight() < i.GetWidth())
		{
			xres = cl.ThumbWidth();
			yres = (int)((float)i.GetHeight() * ((float)(cl.ThumbWidth()/(float)i.GetWidth())));
		}
		else
		{
			yres = cl.ThumbWidth();
			xres = (int)((float)i.GetWidth() * ((float)(cl.ThumbWidth()/(float)i.GetHeight())));
		}
		
		/////////////////////////////////////////
		// SET LARGEST THUMBNAIL DIMENSIONS - useful for CSS Later
		/////////////////////////////////////////
		if (xres > BiggestWidth())
			BiggestWidth(xres);
		if (yres > BiggestHeight())
			BiggestHeight(yres);
		/////////////////////////////////////
		// Make and save the actual thumbnail
		/////////////////////////////////////
		Gdiplus::Image* pThumbnail = i.GetThumbnailImage(xres, yres, NULL, NULL);
		pThumbnail->Save(image_dst.c_str(),&encoderClsid, NULL);

		if (cl.Verbose())
			std::wcout << L" ... done" << std::endl;
		delete pThumbnail;
		first++;
	}
	if (!cl.Verbose())
		std::wcout << std::endl;
}

void ThumbCreator::MakeAndSaveThumbsSlowly(const CommandLine &cl, const ImageFileList &ifl, unsigned int index)
{
	unsigned int file_count = 0;
	DWORD bufsize = MAX_PATH;
	wchar_t buf[MAX_PATH];
	CLSID   encoderClsid;
	int xres;
	int yres;
		
	typedef std::list<ImageNames>::iterator IN_iter;

	std::list<ImageNames> i_names = ifl.RetrieveImageNames();

	IN_iter first = i_names.begin();

	// Get the CLSID of the JPEG encoder.
	GetEncoderClsid(L"image/jpeg", &encoderClsid);

 	for (file_count = 0; file_count < index; file_count++)
	{
		first++;
	}

	image_src = (*first).GetOriginalPath() + (*first).GetOriginalName();
	image_dst = ifl.GetThumbPath() + (*first).GetThumbnailImageName();

	GetFullPathName(image_dst.c_str(),bufsize,buf,0);
	image_dst = buf;

	Gdiplus::Bitmap i(image_src.c_str());
	if (i.GetHeight() < i.GetWidth())
	{
		xres = cl.ThumbWidth();
		yres = (int)((float)i.GetHeight() * ((float)(cl.ThumbWidth()/(float)i.GetWidth())));
	}
	else
	{
		yres = cl.ThumbWidth();
		xres = (int)((float)i.GetWidth() * ((float)(cl.ThumbWidth()/(float)i.GetHeight())));
	}
	
	/////////////////////////////////////////
	// SET LARGEST THUMBNAIL DIMENSIONS - useful for CSS Later
	/////////////////////////////////////////
	if (xres > BiggestWidth())
		BiggestWidth(xres);
	if (yres > BiggestHeight())
		BiggestHeight(yres);
	/////////////////////////////////////
	// Make and save the actual thumbnail
	/////////////////////////////////////
	Gdiplus::Image* pThumbnail = i.GetThumbnailImage(xres, yres, NULL, NULL);
	pThumbnail->Save(image_dst.c_str(),&encoderClsid, NULL);

	delete pThumbnail;
}
