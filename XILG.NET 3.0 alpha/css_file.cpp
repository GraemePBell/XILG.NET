// css_file.cpp: implementation of the css_file class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "css_file.h"
#include "build_css.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

css_file::css_file()
{
		wchar_t BOM = 0xFEFF;
		css = BOM;
}

css_file::~css_file(){}


void css_file::build(const CommandLine& cl)
{
	css_filename = cl.OutputPath() + cl.ProjectName() + L".css";
	std::wstring user_css = cl.UserCSS();
	
	if (user_css == empty)
	{
		std::wcout << L"\nCreating CSS file";
		build_css buildcss;

		buildcss.thumbsize_x(biggest_thumb_x + 50);
		if (cl.NoCaption())
			buildcss.thumbsize_y(biggest_thumb_y + 50);
		else
			buildcss.thumbsize_y(biggest_thumb_y + 100);

		std::wstring res_string;
		std::wstring front_wrapper = L"";
		std::wstring back_wrapper = L"";

		
		if (cl.InternalCSS())
		{
			front_wrapper += L"<stylesheet-wrapper>\n";
			back_wrapper += L"</stylesheet-wrapper>";
		}
		css += front_wrapper; 
		
		css	+= buildcss.html(res_string,cl);
		if (cl.BannerImage() != empty)
			css	+= buildcss.div_banner(res_string,cl);
		css	+= buildcss.h1(res_string,cl);
		css	+= buildcss.h2(res_string,cl);
		css	+= buildcss.p(res_string,cl);
		css	+= buildcss.p_boilerplate(res_string,cl);
		css += buildcss.div_float(res_string,cl);
		css += buildcss.div_container(res_string,cl);
		css += buildcss.div_spacer(res_string,cl);
		css += buildcss.anchor(res_string,cl);
		css += buildcss.anchor_link(res_string,cl);
		css += buildcss.anchor_active(res_string,cl);
		css += buildcss.anchor_visited(res_string,cl);
		css += buildcss.anchor_hover(res_string,cl);
		css += buildcss.dot_center(res_string,cl);
		css += buildcss.dot_link(res_string,cl);

		css	+= back_wrapper;
	
		save(css_filename);
	}
	else
	{
		CopyFile(user_css.c_str(),css_filename.c_str(),false);
	}
}

void css_file::save(std::wstring &filename)
{
	HANDLE hFile; 
	std::wstring xilgerr;
 
	hFile = CreateFile(filename.c_str(),GENERIC_WRITE,FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

	if (hFile == INVALID_HANDLE_VALUE) 
	{ 
		xilgerr = L"Could not create file: ";
		xilgerr += filename;
		std::wstring xilgerr_line = stringer(__LINE__);
		std::wstring xilgerr_file = widen(__FILE__);
		throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
	}
	DWORD BytesToWrite = css.length() * sizeof(wchar_t);
	DWORD BytesWritten;
	
	BOOL success = WriteFile(hFile,css.c_str(),BytesToWrite,&BytesWritten,NULL);

	if (!success)
	{
		DWORD err = GetLastError();
		wchar_t buffer[0x10];
		_itow_s(err,buffer,0x10,10);

		xilgerr = L" WriteFile failed!: ";
		xilgerr += filename;
		xilgerr += L"\nGetLastError returned: ";
		xilgerr += buffer;
		
		CloseHandle(hFile);

		std::wstring xilgerr_line = stringer(__LINE__);
		std::wstring xilgerr_file = widen(__FILE__);
		throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
	}

	CloseHandle(hFile);

}

void css_file::BiggestThumbSize(std::pair<int,int>& bts)
{
	biggest_thumb_x = bts.first;
	biggest_thumb_y = bts.second;
}

