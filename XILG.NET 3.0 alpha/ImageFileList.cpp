// ImageFileList.cpp: implementation of the ImageFileList class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"
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
	std::list<std::wstring>::iterator first;
	pathnames = GetOrgPaths();
	
	if (recurse)
		AddSubPaths(pathnames);
	
	pathnames.sort();
	pathnames.unique();
	
	first = pathnames.begin();

	std::wstring pathname;// = GetOrgPath();
	
	unsigned int number_of_paths = pathnames.size();
	
	for (unsigned int counter = 0; counter < number_of_paths; counter++)
	{
		bool finished_find = false;
		// (*first) += L"*.*"
		pathname = (*first);
		pathname += L"*.*";
		
		hFind = FindFirstFile(pathname.c_str(), &FindFileData);
		if (hFind == INVALID_HANDLE_VALUE) 
		{
			DWORD GLE = GetLastError();
			wchar_t buf[0x10];
			_itow_s(GLE,buf,0x10,10);

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
					if (!numfiles && counter == number_of_paths)
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
					wchar_t buf[0x10];
					_itow_s(GLE,buf,0x10,10);
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
				std::transform(buf1.begin(),buf1.end(),buf1.begin(),tolower);
				const wchar_t* tmp = PathFindSuffixArray(buf1.c_str(), suffixes, suffix_list.size());
				
				if (tmp)
				{
					std::wstring li_name;
					std::wstring th_name;

					li_name = L"l_" + std::wstring(FindFileData.cFileName);
					th_name = L"t_" + std::wstring(FindFileData.cFileName);

					ImageNames temp;
					temp.SetOriginalName(FindFileData.cFileName);
					temp.SetOriginalPath((*first));

					temp.SetLargeImageName(li_name);
					temp.SetThumbnailImageName(th_name);

					i_names.push_back(temp);
					numfiles++;
				}
			}
		}
		FindClose(hFind);
		first++;
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

	i_paths.SetLargeImageFolder(cl.OutputPath()+L"images");
	i_paths.SetThumbnailImageFolder(cl.OutputPath()+L"thumbs");
}

//void ImageFileList::SetOrgPath(const std::wstring &orgpath)
//{
////	i_paths.SetOriginalFolder(orgpath);
//}

//////////////////////////////////////////////////////////////////////
void ImageFileList::SetOrgPaths(const std::list<std::wstring> &orgpath)
{
	i_paths.SetOriginalFolders(orgpath);
}
///////////////////////////////////////////////////////////////////////

void ImageFileList::SetBigPath(const std::wstring &bigpath)
{
	i_paths.SetLargeImageFolder(bigpath);
}

void ImageFileList::SetThumbPath(const std::wstring &thumbpath)
{
	i_paths.SetThumbnailImageFolder(thumbpath);
}

const std::wstring& ImageFileList::GetOrgPath() const
{
	return i_paths.GetOriginalFolder();
}

const std::list<std::wstring>& ImageFileList::GetOrgPaths() const
{
	return i_paths.GetOriginalFolders();
}


const std::wstring& ImageFileList::GetBigPath() const
{
	return i_paths.GetLargeImageFolder();
}

const std::wstring& ImageFileList::GetThumbPath() const
{
	return i_paths.GetThumbnailImageFolder();
}


void ImageFileList::CreateUnsafeArrayOfImageTypes()
{
	typedef std::list<std::wstring>::iterator sl_iter;

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
	suffix_list.push_back(L"jpeg");
	suffix_list.push_back(L"jpg");
	suffix_list.push_back(L"gif");
	suffix_list.push_back(L"tif");
	suffix_list.push_back(L"tiff");
	suffix_list.push_back(L"png");
	suffix_list.push_back(L"bmp");

	CreateUnsafeArrayOfImageTypes();
}



void ImageFileList::OutPutToScreen()
{
	typedef std::list<ImageNames>::iterator IN_iter;
	
	IN_iter first = i_names.begin();
	std::list<ImageNames>::size_type max_items = i_names.size();

	for (unsigned int count = 0; count < max_items; count++)
	{
		std::wcout << GetOrgPath() << (*first).GetOriginalName() << std::endl;
		std::wcout << GetBigPath() << (*first).GetLargeImageName() << std::endl;
		std::wcout << GetThumbPath() << (*first).GetThumbnailImageName() << std::endl << std::endl;
		first++;
	}
}

const std::list<ImageNames>& ImageFileList::RetrieveImageNames() const
{
	return i_names;
}

void ImageFileList::AddSubPaths(std::list<std::wstring>& paths)
{
	std::list<std::wstring>::iterator iter;
	
	for(iter = paths.begin(); iter != paths.end(); iter++)
	{
		std::wstring dirname = (*iter);
		RecurseFolders(dirname);
	}
	pathnames.splice(pathnames.end(),recursed_paths);
}

void ImageFileList::RecurseFolders(const std::wstring& folder)
{
	HANDLE file_handle;
	WIN32_FIND_DATA find_data;
	std::wstring filename = folder;
	AddBackSlash(filename);
	filename += L"*.*";

	file_handle = FindFirstFile(filename.c_str(),&find_data);

	while ( file_handle != INVALID_HANDLE_VALUE )
	{
		if( find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
		{

			std::wstring fullname = find_data.cFileName;
			if (fullname != L"." && fullname != L"..")
			{
				std::wstring newfolder = folder;
				AddBackSlash(newfolder);
				newfolder += fullname;
				AddBackSlash(newfolder);
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