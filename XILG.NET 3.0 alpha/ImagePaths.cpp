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

void ImagePaths::SetOriginalFolder(const path& foldername)
{
	original_image_folder = foldername;
}

void ImagePaths::SetOriginalFolders(const std::list<path>& foldernames)
{
	input_folders = foldernames;
}

void ImagePaths::SetLargeImageFolder(const path& foldername)
{
	large_image_folder = foldername;
}

void ImagePaths::SetThumbnailImageFolder(const path& foldername)
{
	thumbnail_image_folder = foldername;
}

const path& ImagePaths::GetOriginalFolder() const
{
	return original_image_folder;
}

const std::list<path>& ImagePaths::GetOriginalFolders() const
{
	return input_folders;
}

const path& ImagePaths::GetLargeImageFolder() const
{
	return large_image_folder;
}

const path& ImagePaths::GetThumbnailImageFolder() const
{
	return thumbnail_image_folder;
}


///////////////////////////////////////////////////////////////////////////////

ImageNames::ImageNames() { }
ImageNames::~ImageNames() { }

void ImageNames::SetOriginalName(const path& filename)
{
	original_name = filename;
}

void ImageNames::SetOriginalPath(const path& filename)
{
	original_path = filename;
}


void ImageNames::SetLargeImageName(const path& filename)
{
	large_image_name = filename;
	large_image_name.replace_extension(L".jpg");
}

void ImageNames::SetThumbnailImageName(const path& filename)
{
	thumbnail_image_name = filename;
	thumbnail_image_name.replace_extension(L".jpg");
}

const path& ImageNames::GetOriginalName()
{
	return original_name;
}

const path& ImageNames::GetOriginalPath()
{
	return original_path;
}


const path& ImageNames::GetLargeImageName()
{
	return large_image_name;
}

const path& ImageNames::GetThumbnailImageName()
{
	return thumbnail_image_name;
}

