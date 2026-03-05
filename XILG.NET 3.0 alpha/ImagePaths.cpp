// ImagePaths.cpp: implementation of the ImagePaths class.
//
//////////////////////////////////////////////////////////////////////
//#pragma warning(disable:4786)

#include "stdafx.h"
#include "ImagePaths.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ImagePaths::ImagePaths()
{

}

ImagePaths::~ImagePaths()
{

}

void ImagePaths::SetOriginalFolder(const std::wstring& foldername)
{
	std::wstring temp(foldername);
	original_image_folder = AddBackSlash(temp);
}

void ImagePaths::SetOriginalFolders(const std::list<std::wstring>& foldernames)
{
	std::list<std::wstring> temp(foldernames);
	input_folders = AddBackSlashes(temp);
}

void ImagePaths::SetLargeImageFolder(const std::wstring& foldername)
{
	std::wstring temp(foldername);
	large_image_folder = AddBackSlash(temp);
}

void ImagePaths::SetThumbnailImageFolder(const std::wstring& foldername)
{
	std::wstring temp(foldername);
	thumbnail_image_folder = AddBackSlash(temp);
}

const std::wstring& ImagePaths::GetOriginalFolder() const
{
	return original_image_folder;
}

const std::list<std::wstring>& ImagePaths::GetOriginalFolders() const
{
	return input_folders;
}

const std::wstring& ImagePaths::GetLargeImageFolder() const
{
	return large_image_folder;
}

const std::wstring& ImagePaths::GetThumbnailImageFolder() const
{
	return thumbnail_image_folder;
}


///////////////////////////////////////////////////////////////////////////////

ImageNames::ImageNames() { }
ImageNames::~ImageNames() { }

void ImageNames::SetOriginalName(const std::wstring& filename)
{
	original_name = filename;
}

void ImageNames::SetOriginalPath(const std::wstring& filename)
{
	original_path = filename;
}


void ImageNames::SetLargeImageName(const std::wstring& filename)
{
	large_image_name = filename;
	ReplaceExtension(large_image_name,std::wstring(L"jpg"));

}

void ImageNames::SetThumbnailImageName(const std::wstring& filename)
{
	thumbnail_image_name = filename;
	ReplaceExtension(thumbnail_image_name,std::wstring(L"jpg"));
}

const std::wstring& ImageNames::GetOriginalName()
{
	return original_name;
}

const std::wstring& ImageNames::GetOriginalPath()
{
	return original_path;
}


const std::wstring& ImageNames::GetLargeImageName()
{
	return large_image_name;
}

const std::wstring& ImageNames::GetThumbnailImageName()
{
	return thumbnail_image_name;
}

