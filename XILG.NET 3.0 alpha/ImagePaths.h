// ImagePaths.h: interface for the ImagePaths class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEPATHS_H__1851B97D_51BC_4CEB_AC2D_FC0494C8D808__INCLUDED_)
#define AFX_IMAGEPATHS_H__1851B97D_51BC_4CEB_AC2D_FC0494C8D808__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#pragma warning(disable:4786)

#include <string>
#include <filesystem>

////////////////
class ImagePaths  
{
public:
	ImagePaths();
	virtual ~ImagePaths();

	void SetOriginalFolder(const path& foldername);
	void SetLargeImageFolder(const path& foldername);
	void SetThumbnailImageFolder(const path& foldername);

	void SetOriginalFolders(const std::list<path>& folders);

	const path& GetOriginalFolder() const;
	const path& GetLargeImageFolder() const;
	const path& GetThumbnailImageFolder() const;

	const std::list<path>& GetOriginalFolders() const;

private:
	path original_image_folder;
	path large_image_folder;
	path thumbnail_image_folder;

	std::list<path> input_folders;
};

class ImageNames
{
public:
	ImageNames();
	virtual ~ImageNames();

	void SetOriginalName(const path& filename);
	void SetLargeImageName(const path& filename);
	void SetThumbnailImageName(const path& filename);
	void SetOriginalPath(const path& filename);

	const path& GetOriginalName();
	const path& GetLargeImageName();
	const path& GetThumbnailImageName();
	const path& GetOriginalPath();

private:
	path original_name;
	path large_image_name;
	path thumbnail_image_name;
	path original_path;
};


#endif // !defined(AFX_IMAGEPATHS_H__1851B97D_51BC_4CEB_AC2D_FC0494C8D808__INCLUDED_)
