// PictureHandler.h: interface for the PictureHandler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PICTUREHANDLER_H__7F0B89F1_BA13_4233_A99B_B7F6E6ACBBCA__INCLUDED_)
#define AFX_PICTUREHANDLER_H__7F0B89F1_BA13_4233_A99B_B7F6E6ACBBCA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class PictureHandler  
{
public:
	PictureHandler();
	virtual ~PictureHandler();
	std::pair<size_t, size_t> BiggestImageDimensions() const;
protected:
	void BiggestWidth(size_t w);
	void BiggestHeight(size_t h);
	size_t BiggestWidth();
	size_t BiggestHeight();
	int GetEncoderClsid(const std::wstring& format, CLSID* pClsid);

private:
	size_t biggest_height;
	size_t biggest_width;
	
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplus_token;
};

#endif // !defined(AFX_PICTUREHANDLER_H__7F0B89F1_BA13_4233_A99B_B7F6E6ACBBCA__INCLUDED_)
