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


const path& MakeTempFileName(path& buffer)
{
	std::wstring xilgerr;
	wchar_t path_buffer[MAX_PATH];
	wchar_t filename_buffer[MAX_PATH];

	// Get the temp path.
    int check_buf = GetTempPath(MAX_PATH, path_buffer); 
    if ((check_buf > MAX_PATH) || (check_buf == 0))
	{
		DWORD GLE = GetLastError();
		xilgerr = std::format(L"GetTempPath failed with error {}", GLE);

		std::wstring xilgerr_line = stringer(__LINE__);
		std::wstring xilgerr_file = widen(__FILE__);
		throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
	}
    // Create a temporary file. 
    check_buf = GetTempFileName(path_buffer,L"xlg",0,filename_buffer);
    if (check_buf == 0)
    {
		DWORD GLE = GetLastError();
		xilgerr = std::format(L"GetTempPath failed with error {}", GLE);
		std::wstring xilgerr_line = stringer(__LINE__);
		std::wstring xilgerr_file = widen(__FILE__);
		throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
    }
	
	buffer = filename_buffer;
	return buffer;
}

