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


////////////////
class ImagePaths  
{
public:
	ImagePaths();
	virtual ~ImagePaths();

	void SetOriginalFolder(const std::wstring& foldername);
	void SetLargeImageFolder(const std::wstring& foldername);
	void SetThumbnailImageFolder(const std::wstring& foldername);

	void SetOriginalFolders(const std::list<std::wstring>& folders);

	const std::wstring& GetOriginalFolder() const;
	const std::wstring& GetLargeImageFolder() const;
	const std::wstring& GetThumbnailImageFolder() const;

	const std::list<std::wstring>& GetOriginalFolders() const;

private:
	std::wstring original_image_folder;
	std::wstring large_image_folder;
	std::wstring thumbnail_image_folder;

	std::list<std::wstring> input_folders;
};

class ImageNames
{
public:
	ImageNames();
	virtual ~ImageNames();

	void SetOriginalName(const std::wstring& filename);
	void SetLargeImageName(const std::wstring& filename);
	void SetThumbnailImageName(const std::wstring& filename);
	void SetOriginalPath(const std::wstring& filename);

	const std::wstring& GetOriginalName();
	const std::wstring& GetLargeImageName();
	const std::wstring& GetThumbnailImageName();
	const std::wstring& GetOriginalPath();

private:
	std::wstring original_name;
	std::wstring large_image_name;
	std::wstring thumbnail_image_name;
	std::wstring original_path;
};


#endif // !defined(AFX_IMAGEPATHS_H__1851B97D_51BC_4CEB_AC2D_FC0494C8D808__INCLUDED_)
