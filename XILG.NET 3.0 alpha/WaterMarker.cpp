#include "stdafx.h"
#include "WaterMarker.h"

WaterMarker::WaterMarker(void)
{
	InitialiseColorMatrix();
	// Create an ImageAttributes object and set its color matrix.
}

WaterMarker::~WaterMarker(void)
{
}

void WaterMarker::Save(const std::wstring& image_dst, const CommandLine &cl, Gdiplus::Bitmap& i, CLSID encoderClsid)
{
	if (cl.Verbose())
		std::wcout << L" ... watermarking";

	/////////////////////////////////////////////////////////////////////
	std::wstring fb; 
	MakeTempFileName(fb);
	encoder = encoderClsid;

	WaterMarkAlpha(cl.WatermarkAlpha());
	imageAtt.SetColorMatrix(&colorMatrix,Gdiplus::ColorMatrixFlagsDefault,Gdiplus::ColorAdjustTypeBitmap);

	// Write out the temporary file as a JPEG
	i.Save(fb.c_str(),&encoder, NULL);
	
	Gdiplus::REAL x = (Gdiplus::REAL)i.GetWidth();
	Gdiplus::REAL y = (Gdiplus::REAL)i.GetHeight();
	SaveWaterMarkedImage(cl,x,y,image_dst,fb);

	DeleteFile(fb.c_str());
}

void WaterMarker::SaveWaterMarkedImage(const CommandLine& cl, 
									   Gdiplus::REAL x, 
									   Gdiplus::REAL y, 
									   const std::wstring& image_dst, 
									   const std::wstring& file_buffer)
{
	// Open our watermark image
	Gdiplus::Image im(cl.WaterMark().c_str());

	// Read in our temporary file again
	Gdiplus::Bitmap i_wm(file_buffer.c_str());
	Gdiplus::Graphics gfo(&i_wm);

	Gdiplus::REAL tx = (Gdiplus::REAL)im.GetWidth();
	Gdiplus::REAL ty = (Gdiplus::REAL)im.GetHeight();

	// Calculate size and position of watermark image on 
	// the original image

	Gdiplus::RectF srcrect(0,0,tx,ty);
	Gdiplus::RectF myrect;
	PositionWaterMark(myrect,x,y,tx,ty,cl);

	gfo.DrawImage(&im,myrect,srcrect,Gdiplus::UnitPixel,&imageAtt);

	// write out watermarked file to our image destination
	i_wm.Save(image_dst.c_str(),&encoder, NULL);
}


void WaterMarker::PositionWaterMark(Gdiplus::RectF& wm_pos, 
									Gdiplus::REAL x, 
									Gdiplus::REAL y, 
									Gdiplus::REAL tx, 
									Gdiplus::REAL ty, 
									const CommandLine& cl)
{
	Gdiplus::REAL factor		= ScaleWatermark(x,y,tx,ty,cl);
	Gdiplus::REAL x_factor		= tx*factor;
	Gdiplus::REAL y_factor		= ty*factor;
	Gdiplus::REAL indent		= (x_factor > y_factor) ? (x_factor/5)*(1-(2*x_factor/x)) : (y_factor/5)*(1-(2*y_factor/y));
	Gdiplus::REAL pos_top		= y_factor + indent;
	Gdiplus::REAL pos_bottom	= y - y_factor - indent;
	Gdiplus::REAL pos_left		= x_factor + indent;
	Gdiplus::REAL pos_right		= x - x_factor - indent;
	Gdiplus::REAL pos_v_center	= y/2;
	Gdiplus::REAL pos_h_center	= x/2;
	
	switch (cl.WatermarkPosition())
	{
		case center:
		{
			wm_pos.Offset(pos_h_center,pos_v_center);
			break;
		}
		case tc:
		{
			wm_pos.Offset(pos_h_center,pos_top);
			break;
		}
		case lc:
		{
			wm_pos.Offset(pos_left,pos_v_center);
			break;
		}
		case cr:
		{
			wm_pos.Offset(pos_right,pos_v_center);
			break;
		}
		case bc:
		{
			wm_pos.Offset(pos_h_center,pos_bottom);
			break;
		}
		case bl:
		{
			wm_pos.Offset(pos_left,pos_bottom);
			break;
		}
		case tr:
		{
			wm_pos.Offset(pos_right,pos_top);
			break;
		}
		case tl:
		{
			wm_pos.Offset(pos_left,pos_top);
			break;
		}
		case br:
		default:
		{
			wm_pos.Offset(pos_right,pos_bottom);
			break;
		}
	}
	wm_pos.Inflate(x_factor,y_factor);
}


Gdiplus::REAL WaterMarker::ScaleWatermark(	Gdiplus::REAL main_image_x, 
											Gdiplus::REAL main_image_y, 
											Gdiplus::REAL water_x, 
											Gdiplus::REAL water_y, 
											const CommandLine& cl)
{
	float wm_scale = 1/cl.WatermarkScale();
	Gdiplus::REAL factor = 0.0f;
	Gdiplus::REAL temp = 0.0f;

	Gdiplus::REAL x_ratio = main_image_x/water_x;
	Gdiplus::REAL y_ratio = main_image_y/water_y;


	if (x_ratio < y_ratio)
	{
		temp = main_image_x/wm_scale;
		factor = temp/water_x;
	}
	else
	{
		temp = main_image_y/wm_scale;
		factor = temp/water_y;
	}
	return factor/2; // because the inflate method expands in all four directions !!!

}

void WaterMarker::InitialiseColorMatrix(void)
{
	/*
	// Note the values in column 4.
	////////////////////////////////////////////////////////////////////
	colorMatrix = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f, 0.2f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.2f, 0.0f,
					0.0f, 0.0f, 0.0f, 0.2f, 0.0f,
					0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
	*/
	// Create an ImageAttributes object and set its color matrix.

	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			if (x == y)
				colorMatrix.m[x][y] = 1.0f;
			else
				colorMatrix.m[x][y] = 0.0f;
		}
	}
	WaterMarkAlpha(0.2f);	// nice default alpha
}

Gdiplus::REAL WaterMarker::WaterMarkAlpha() const
{
	return alpha;
}

void WaterMarker::WaterMarkAlpha(Gdiplus::REAL value)
{
	alpha = value;
	colorMatrix.m[1][3] = alpha; 
	colorMatrix.m[2][3] = alpha; 
	colorMatrix.m[3][3] = alpha; 
}

