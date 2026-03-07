// ImageFileList.cpp: implementation of the ImageFileList class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"

#include <wctype.h>

//#pragma warning(disable:4786)
#include "ImageFileList.h"
#include "ImagePaths.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ImageFileList::ImageFileList()
{
	list_status = false;
	numfiles= 0;

	CreateSafeListOfImageTypes();
}

ImageFileList::~ImageFileList(){}



void ImageFileList::GatherImageNames()
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	pathnames = GetOrgPaths();
	
	if (recurse)
		AddSubPaths(pathnames);
	
	pathnames.sort();
	pathnames.unique();
	
	size_t number_of_paths = pathnames.size();
	
	for (const auto& pname : pathnames)
	{
		bool finished_find = false;
		path wildcarded = pname.wstring() + L"/*.*";
		wildcarded = wildcarded.make_preferred();

		hFind = FindFirstFile(wildcarded.c_str(), &FindFileData);
		if (hFind == INVALID_HANDLE_VALUE) 
		{
			DWORD GLE = GetLastError();
			std::wstring buf = std::format(L" {}!\n",GLE);
			std::wstring xilgerr = L"FindFirstFile returned INVALID_HANDLE_VALUE\n";
			xilgerr += L"GetLastError returns: ";
			xilgerr += buf;
			std::wstring xilgerr_line = stringer(__LINE__);
			std::wstring xilgerr_file = widen(__FILE__);
			throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
		} 

		while (!finished_find)
		{
			if (!FindNextFile(hFind, &FindFileData)) 
			{
				DWORD error = GetLastError();
				if (error == ERROR_NO_MORE_FILES) 
				{ 
					if (!numfiles == number_of_paths)
					{
						std::wstring xilgerr = L"No images found in the input folders!"; 
						std::wstring xilgerr_line = stringer(__LINE__);
						std::wstring xilgerr_file = widen(__FILE__);
						throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
					}
					finished_find = true; 
				}
				else
				{
					DWORD GLE = GetLastError();
					std::wstring buf = std::format(L" {}!\n", GLE);
					std::wstring xilgerr = L"FindNextFile failed\n";
					xilgerr += L"GetLastError returns: ";
					xilgerr += buf;

					FindClose(hFind);
					std::wstring xilgerr_line = stringer(__LINE__);
					std::wstring xilgerr_file = widen(__FILE__);
					throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
				}
			}
			
			if (!finished_find)
			{
				std::wstring buf1 = FindFileData.cFileName;
				std::transform(
					buf1.begin(), buf1.end(),
					buf1.begin(),
					[](wchar_t c) { return towlower(c); }
				);

				auto tmp = PathFindSuffixArray(buf1.c_str(), suffixes, static_cast<int>(suffix_list.size()));
				
				if (tmp)
				{
					std::wstring li_name;
					std::wstring th_name;

					li_name = L"l_" + std::wstring(FindFileData.cFileName);
					th_name = L"t_" + std::wstring(FindFileData.cFileName);

					ImageNames temp;
					temp.SetOriginalName(FindFileData.cFileName);
					temp.SetOriginalPath(pname);

					temp.SetLargeImageName(li_name);
					temp.SetThumbnailImageName(th_name);

					i_names.push_back(temp);
					numfiles++;
				}
			}
		}
		FindClose(hFind);
	}

	if (!numfiles)
	{
		std::wstring xilgerr = L"No images found in the input folders!";
		std::wstring xilgerr_line = stringer(__LINE__);
		std::wstring xilgerr_file = widen(__FILE__);
		throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
	}
	list_status = true;
}

void ImageFileList::SetPathInfo(const CommandLine& cl)
{
	recurse = cl.Recurse();
	///////////////////////////////////////////////
	i_paths.SetOriginalFolders(cl.InputPaths());
	///////////////////////////////////////////////

	i_paths.SetLargeImageFolder(cl.OutputPath() / L"images");
	i_paths.SetThumbnailImageFolder(cl.OutputPath() / L"thumbs");
}

void ImageFileList::SetOrgPath(const path &orgpath)
{
	i_paths.SetOriginalFolder(orgpath);
}

//////////////////////////////////////////////////////////////////////
void ImageFileList::SetOrgPaths(const std::list<path> &orgpath)
{
	i_paths.SetOriginalFolders(orgpath);
}
///////////////////////////////////////////////////////////////////////

void ImageFileList::SetBigPath(const path &bigpath)
{
	i_paths.SetLargeImageFolder(bigpath);
}

void ImageFileList::SetThumbPath(const path &thumbpath)
{
	i_paths.SetThumbnailImageFolder(thumbpath);
}

const path& ImageFileList::GetOrgPath() const
{
	return i_paths.GetOriginalFolder();
}

const std::list<path>& ImageFileList::GetOrgPaths() const
{
	return i_paths.GetOriginalFolders();
}


const path& ImageFileList::GetBigPath() const
{
	return i_paths.GetLargeImageFolder();
}

const path& ImageFileList::GetThumbPath() const
{
	return i_paths.GetThumbnailImageFolder();
}


void ImageFileList::CreateUnsafeArrayOfImageTypes()
{
	typedef std::list<path>::iterator sl_iter;

	sl_iter first = suffix_list.begin();
	std::list<std::wstring>::size_type max_items = suffix_list.size();

	for (unsigned int count = 0; count < max_items; count++ )
	{
		suffixes[count] = const_cast<wchar_t*>(first->c_str());
		first++;
	}
}

void ImageFileList::CreateSafeListOfImageTypes()
{
	suffix_list.emplace_back(L"jpeg");
	suffix_list.emplace_back(L"jpg");
	suffix_list.emplace_back(L"gif");
	suffix_list.emplace_back(L"tif");
	suffix_list.emplace_back(L"tiff");
	suffix_list.emplace_back(L"png");
	suffix_list.emplace_back(L"bmp");

	CreateUnsafeArrayOfImageTypes();
}



void ImageFileList::OutPutToScreen()
{
	for (auto& img : i_names)
	{
		std::wcout << GetOrgPath() << img.GetOriginalName() << std::endl;
		std::wcout << GetBigPath() << img.GetLargeImageName() << std::endl;
		std::wcout << GetThumbPath() << img.GetThumbnailImageName() << std::endl << std::endl;
	}
}

const std::list<ImageNames>& ImageFileList::RetrieveImageNames() const
{
	return i_names;
}

void ImageFileList::AddSubPaths(std::list<path>& paths)
{
	for(auto& iter : paths)
	{
		RecurseFolders(iter);
	}
	pathnames.splice(pathnames.end(),recursed_paths);
}

void ImageFileList::RecurseFolders(const path& folder)
{
	HANDLE file_handle;
	WIN32_FIND_DATA find_data;
	path filename = folder;
	filename += L"/*.*";

	file_handle = FindFirstFile(filename.c_str(),&find_data);

	while ( file_handle != INVALID_HANDLE_VALUE )
	{
		if( find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
		{

			path fullname = find_data.cFileName;
			if (fullname != L"." && fullname != L"..")
			{
				path newfolder = folder;
				newfolder /= fullname;

				recursed_paths.push_back(newfolder);
				RecurseFolders(newfolder);
			}
		}
		// loop thru remaining entries in the dir
		if (!FindNextFile( file_handle, &find_data ))
				  break;
	}
	// clean up and restore directory
	FindClose( file_handle );
}

const int ImageFileList::NumberOfImages() const
{
	return numfiles;
}