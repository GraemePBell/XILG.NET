#pragma once
#include "CommandLine.h"
////////////////////////////////
// utilities.h
////////////////////////////////////////////////////////////////////////
// useful little functions that don't need to be in classes elsewhere
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
// MACROS - YUCK! - For detailed errors
////////////////////////////////////////
#define widen3(x) ( std::wstring( x ) )
#define widen2(x) widen3( L ## x )
#define widen(x) widen2( x )
#define stringer2(x) widen( #x )
#define stringer(x) stringer2( x )
////////////////////////////////////////

// utility functions
const path& MakeTempFileName(path& filename_buffer);
//std::wstring& AddBackSlash(std::wstring& w);
//std::wstring& StripExtension(std::wstring& w);
//std::wstring& AddExtension(std::wstring& w, const std::wstring& ext);
//std::wstring& ReplaceExtension(std::wstring& w, const std::wstring& ext);

//std::list<std::wstring>& AddBackSlashes(std::list<std::wstring>& w);

class xilg_error
{
public:
	xilg_error(std::wstring& mess);
	xilg_error(std::wstring& mess,std::wstring& file, std::wstring& line);
	xilg_error(wchar_t* mess);
	virtual ~xilg_error();
	std::wstring& message();

private:
	std::wstring emess;
};

extern bool diagnostic;