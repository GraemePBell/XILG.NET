// ImageCopier.h: interface for the ImageCopier class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGECOPIER_H__6FDCCE9C_8FD2_456B_A7FF_256935B68963__INCLUDED_)
#define AFX_IMAGECOPIER_H__6FDCCE9C_8FD2_456B_A7FF_256935B68963__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "PictureHandler.h"
#include "CommandLine.h"
#include "ImageFileList.h"
#include "WaterMarker.h"

class ImageCopier : public PictureHandler 
{
public:
	const int Ticker() const;
	void copy(const CommandLine& cl, const ImageFileList& ifl);
	void copy_one_at_a_time(const CommandLine &cl, const ImageFileList &ifl, unsigned int index);
	void BackgroundCopy(const CommandLine &cl, const ImageFileList &ifl);
	void BannerCopy(const CommandLine &cl, const ImageFileList &ifl);
	ImageCopier();
	virtual ~ImageCopier();
private:
	path image_src;
	path image_dst;
	CLSID encoderClsid;
	WaterMarker* wm;
	int tick;
};


#endif // !defined(AFX_IMAGECOPIER_H__6FDCCE9C_8FD2_456B_A7FF_256935B68963__INCLUDED_)
