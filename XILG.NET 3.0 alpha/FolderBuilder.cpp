// FolderBuilder.cpp: implementation of the FolderBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FolderBuilder.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FolderBuilder::FolderBuilder()
{
	failed = true;
}

FolderBuilder::~FolderBuilder()
{
	if (failed)
	{
		if (PathIsDirectory(big_name.c_str()))
		{		
			RemoveDirectory(big_name.c_str());
		}
		if (PathIsDirectory(wee_name.c_str()))
		{		
			RemoveDirectory(wee_name.c_str());
		}
	}
}

void FolderBuilder::build(const CommandLine& cl, const ImageFileList& ifl)
{
	if (!cl.PathCreate())
		return;
	
	int success = 0;
	std::wstring xilgerr;
	
	dir_name = cl.OutputPath();
	big_name = ifl.GetBigPath();
	wee_name = ifl.GetThumbPath();
		
	if (!PathIsDirectory(dir_name.c_str()))
	{		
		success = CreateDirectory(dir_name.c_str(),NULL);
		if (!success)
		{
			xilgerr = L"Failed to create folder " + dir_name.wstring();
			std::wstring xilgerr_line = stringer(__LINE__);
			std::wstring xilgerr_file = widen(__FILE__);
			throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
		}
	}
	if (!PathIsDirectory(big_name.c_str()))
	{		
		success = CreateDirectory(big_name.c_str(),NULL);
		if (!success)
		{
			xilgerr = L"Failed to create folder " + big_name.wstring();
			std::wstring xilgerr_line = stringer(__LINE__);
			std::wstring xilgerr_file = widen(__FILE__);
			throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
		}
	}
	if (!PathIsDirectory(wee_name.c_str()))
	{		
		success = CreateDirectory(wee_name.c_str(),NULL);
		if (!success)
		{
			xilgerr = L"Failed to create folder " + wee_name.wstring();
			std::wstring xilgerr_line = stringer(__LINE__);
			std::wstring xilgerr_file = widen(__FILE__);
			throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
		}
	}
	failed = false;
}
