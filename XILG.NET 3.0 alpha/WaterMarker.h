#pragma once
#include "CommandLine.h"

class WaterMarker
{
public:
	WaterMarker(void);
	~WaterMarker(void);
	void Save(const std::wstring& image_dst, const CommandLine &cl, Gdiplus::Bitmap& i, CLSID encoderClsid);
	Gdiplus::REAL Alpha() const;	

private:
	// Functions
	void SaveWaterMarkedImage(	const CommandLine& cl, 
								Gdiplus::REAL x, 
								Gdiplus::REAL y, 
								const std::wstring& image_dst, 
								const std::wstring& file_buffer);

	void InitialiseColorMatrix(void);
	void WaterMarkAlpha(Gdiplus::REAL value);
	Gdiplus::REAL WaterMarkAlpha() const;

	void PositionWaterMark(	Gdiplus::RectF& wm_pos, 
							Gdiplus::REAL x, 
							Gdiplus::REAL y, 
							Gdiplus::REAL tx, 
							Gdiplus::REAL ty, 
							const CommandLine& cl);

	Gdiplus::REAL ScaleWatermark(	Gdiplus::REAL main_image_x, 
									Gdiplus::REAL main_image_y, 
									Gdiplus::REAL water_x, 
									Gdiplus::REAL water_y, 
									const CommandLine& cl);
	
	// Data
	Gdiplus::ColorMatrix colorMatrix;
	Gdiplus::ImageAttributes imageAtt;
	CLSID encoder;
	Gdiplus::REAL alpha;

};
