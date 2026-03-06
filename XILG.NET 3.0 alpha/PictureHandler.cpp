// PictureHandler.cpp: implementation of the PictureHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PictureHandler.h"
#include <gdiplus.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PictureHandler::PictureHandler()
{
    Gdiplus::GdiplusStartupInput startupInput;
    startupInput.GdiplusVersion = 1;
    startupInput.DebugEventCallback = nullptr;
    startupInput.SuppressBackgroundThread = FALSE;
    startupInput.SuppressExternalCodecs = FALSE;

    [[maybe_unused]] Gdiplus::Status status = Gdiplus::GdiplusStartup(&gdiplus_token,&gdiplusStartupInput,0);
	biggest_height = 0;
	biggest_width = 0;
}

PictureHandler::~PictureHandler()
{
	Gdiplus::GdiplusShutdown(gdiplus_token);
}

std::pair<size_t, size_t> PictureHandler::BiggestImageDimensions() const
{
	std::pair<size_t, size_t> bid(biggest_width,biggest_height);
	return bid;
}

int PictureHandler::GetEncoderClsid(const std::wstring& format, CLSID* pClsid)
{
   UINT  num = 0;          // number of image encoders
   UINT  size = 0;         // size of the image encoder array in bytes


   Gdiplus::GetImageEncodersSize(&num, &size);

   std::unique_ptr<BYTE[]> buffer(new BYTE[size]);
   Gdiplus::ImageCodecInfo* pImageCodecInfo = reinterpret_cast<Gdiplus::ImageCodecInfo*>(buffer.get());

   GetImageEncoders(num, size, pImageCodecInfo);

   for(UINT j = 0; j < num; ++j)
   {
      if( wcsncmp(pImageCodecInfo[j].MimeType, format.c_str(),size) == 0 )
      {
         *pClsid = pImageCodecInfo[j].Clsid;
         return j;  // Success
      }    
   }

   return -1;  // Failure
}

void PictureHandler::BiggestHeight(size_t h)
{
	biggest_height = h;
}

size_t PictureHandler::BiggestHeight()
{
	return biggest_height;
}

void PictureHandler::BiggestWidth(size_t w)
{
	biggest_width = w;
}

size_t PictureHandler::BiggestWidth()
{
	return biggest_width;
}
