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

	void SetOrgPaths(const std::list<std::wstring>& orgpaths);
	void SetOrgPath(const std::wstring& orgpath);
	void SetBigPath(const std::wstring& bigpath);
	void SetThumbPath(const std::wstring& thumbpath);
	
	const std::list<std::wstring>& GetOrgPaths() const; 
	const std::wstring& GetOrgPath() const; 
	const std::wstring& GetBigPath() const;
	const std::wstring& GetThumbPath() const;

	void GatherImageNames();
	const std::list<ImageNames>& RetrieveImageNames() const; 
	const int NumberOfImages() const;

private:
	void CreateSafeListOfImageTypes();
	void CreateUnsafeArrayOfImageTypes();
	void Recurse();
	void AddSubPaths(std::list<std::wstring>& paths);
	void RecurseFolders(const std::wstring& folder);

	bool list_status;
	bool recurse;
	ImagePaths i_paths;
	std::list <ImageNames> i_names;
	std::list <std::wstring> suffix_list;
	wchar_t* suffixes[MAX_PATH];
	int numfiles;

	std::list<std::wstring> recursed_paths;
	std::list<std::wstring> pathnames;
};

#endif // !defined(AFX_IMAGEFILELIST_H__ED02F578_7DE2_45A4_91B9_7CB8AD2FC9BE__INCLUDED_)
