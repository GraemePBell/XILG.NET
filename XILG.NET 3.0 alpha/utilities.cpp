#include "stdafx.h"
#include "CommandLine.h"

//////////////////////////////////////////////////////////////////////
// xilg_error Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

xilg_error::xilg_error(std::wstring& mess)
{
	emess = mess;
}

xilg_error::xilg_error(std::wstring& mess, std::wstring& file, std::wstring& line)
{
	emess = mess;
	if (::diagnostic)
	{
		emess += L"\n";
		emess += L"in file: "; 
		emess += PathFindFileName(file.c_str());
		emess += L"\n";
		emess += L"at line: "; 
		emess += line;
	}
}

xilg_error::xilg_error(wchar_t* mess)
{
	emess = mess;
}

xilg_error::~xilg_error()
{
}

std::wstring& xilg_error::message()
{
	return emess;
}

//////////// UTILITY FUNCTIONS //////////////
std::wstring& AddBackSlash(std::wstring& w)
{
	std::wstring::size_type max_items = w.length();
	if (w[max_items-1] != L'\\')
		w += L"\\";
	return w;
}


std::list<std::wstring>& AddBackSlashes(std::list<std::wstring>& w)
{
	for_each(w.begin(),w.end(),AddBackSlash);
	return w;
}


std::wstring& StripExtension(std::wstring& w)
{
	std::basic_string <wchar_t>::size_type index;

	index = w.find_last_of(L".");
	w.erase(index);
	return w;
}

std::wstring& AddExtension(std::wstring& w, const std::wstring& ext)
{
	std::wstring temp = w;
	temp += L".";
	temp += ext;
	w = temp;
	return w;
}

std::wstring& ReplaceExtension(std::wstring& w, const std::wstring& ext)
{
	std::wstring temp = w;
	temp = StripExtension(temp);
	temp = AddExtension(temp,ext);
	w = temp;
	return w;
}

/////////////////////////////////////////////////////////////////////


std::wstring& MakeTempFileName(std::wstring& buffer)
{
	std::wstring xilgerr;
	wchar_t path_buffer[MAX_PATH];
	wchar_t filename_buffer[MAX_PATH];
	wchar_t error_buffer[0x10];

	// Get the temp path.
    int check_buf = GetTempPath(MAX_PATH, path_buffer); 
    if ((check_buf > MAX_PATH) || (check_buf == 0))
	{
		DWORD GLE = GetLastError();
		_itow_s(GLE,error_buffer,0x10,10);
		xilgerr = L"GetTempPath failed with error "; 
		xilgerr += error_buffer;
		std::wstring xilgerr_line = stringer(__LINE__);
		std::wstring xilgerr_file = widen(__FILE__);
		throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
	}
    // Create a temporary file. 
    check_buf = GetTempFileName(path_buffer,L"xlg",0,filename_buffer);
    if (check_buf == 0)
    {
		DWORD GLE = GetLastError();
		_itow_s(GLE,error_buffer,0x10,10);
        xilgerr = L"GetTempFileName failed with error ";
		xilgerr += error_buffer;
		std::wstring xilgerr_line = stringer(__LINE__);
		std::wstring xilgerr_file = widen(__FILE__);
		throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
    }
	
	buffer = filename_buffer;
	return buffer;
}

