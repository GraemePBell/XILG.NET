#pragma once

ref class XilgProgressEvent
{
public:
	XilgProgressEvent(void);
	System::Void MaxWebFiles(int mwp) { max_web_files = mwp; }
	System::Void MinPics(int mp) { min_pics = mp; }
	System::Void MaxPics(int mp) { max_pics = mp; }
	System::Void IncPPC() { progress_picture_copy++; }
	System::Void IncPTC() { progress_thumb_copy++; }
	System::Void IncPWC() { progress_web_creation++ ;}
	int GetPPC() { return progress_picture_copy; }
	int GetPTC() { return progress_thumb_copy; }
	int GetPWC() { return progress_web_creation; }

private:
	int max_pics;
	int min_pics;
	int max_web_files;

	int progress_picture_copy;
	int progress_thumb_copy;
	int progress_web_creation;
};
