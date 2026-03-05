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

    Gdiplus::Status status = Gdiplus::GdiplusStartup(&gdiplus_token,&gdiplusStartupInput,0);
	biggest_height = 0;
	biggest_width = 0;
}

PictureHandler::~PictureHandler()
{
	Gdiplus::GdiplusShutdown(gdiplus_token);
}

std::pair<int,int> PictureHandler::BiggestImageDimensions() const
{
	std::pair<int,int> bid(biggest_width,biggest_height);
	return bid;
}

int PictureHandler::GetEncoderClsid(const std::wstring& format, CLSID* pClsid)
{
   UINT  num = 0;          // number of image encoders
   UINT  size = 0;         // size of the image encoder array in bytes

   Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

   Gdiplus::GetImageEncodersSize(&num, &size);
   if(size == 0)
      return -1;  // Failure

   pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
   if(pImageCodecInfo == NULL)
      return -1;  // Failure

   Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);

   for(UINT j = 0; j < num; ++j)
   {
      if( wcscmp(pImageCodecInfo[j].MimeType, format.c_str()) == 0 )
      {
         *pClsid = pImageCodecInfo[j].Clsid;
         free(pImageCodecInfo);
         return j;  // Success
      }    
   }

   free(pImageCodecInfo);
   return -1;  // Failure
}

void PictureHandler::BiggestHeight(int h)
{
	biggest_height = h;
}

int PictureHandler::BiggestHeight()
{
	return biggest_height;
}

void PictureHandler::BiggestWidth(int w)
{
	biggest_width = w;
}

int PictureHandler::BiggestWidth()
{
	return biggest_width;
}
