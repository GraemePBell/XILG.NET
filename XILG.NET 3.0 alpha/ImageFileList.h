// ImageFileList.h: interface for the ImageFileList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEFILELIST_H__ED02F578_7DE2_45A4_91B9_7CB8AD2FC9BE__INCLUDED_)
#define AFX_IMAGEFILELIST_H__ED02F578_7DE2_45A4_91B9_7CB8AD2FC9BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include "ImagePaths.h"
#include "CommandLine.h"

class ImageFileList  
{
public:
	void OutPutToScreen();
	ImageFileList();
	virtual ~ImageFileList();
	
	void SetPathInfo(const CommandLine& cl);

	void SetOrgPaths(const std::list<path>& orgpaths);
	void SetOrgPath(const path& orgpath);
	void SetBigPath(const path& bigpath);
	void SetThumbPath(const path& thumbpath);
	
	const std::list<path>& GetOrgPaths() const; 
	const path& GetOrgPath() const; 
	const path& GetBigPath() const;
	const path& GetThumbPath() const;

	void GatherImageNames();
	const std::list<ImageNames>& RetrieveImageNames() const; 
	const int NumberOfImages() const;

private:
	void CreateSafeListOfImageTypes();
	void CreateUnsafeArrayOfImageTypes();
	// void Recurse();
	void AddSubPaths(std::list<path>& paths);
	void RecurseFolders(const path& folder);

	bool list_status;
	bool recurse;
	ImagePaths i_paths;
	std::list <ImageNames> i_names;
	std::list <path> suffix_list;
	wchar_t* suffixes[MAX_PATH];
	int numfiles;

	std::list<path> recursed_paths;
	std::list<path> pathnames;
};

#endif // !defined(AFX_IMAGEFILELIST_H__ED02F578_7DE2_45A4_91B9_7CB8AD2FC9BE__INCLUDED_)
