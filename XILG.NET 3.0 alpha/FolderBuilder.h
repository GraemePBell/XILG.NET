// FolderBuilder.h: interface for the FolderBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FOLDERBUILDER_H__513AA549_46A7_4914_BA2D_1BB98A054966__INCLUDED_)
#define AFX_FOLDERBUILDER_H__513AA549_46A7_4914_BA2D_1BB98A054966__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CommandLine.h"
#include "ImageFileList.h"

class FolderBuilder  
{
public:
	void build(const CommandLine& cl, const ImageFileList& ifl);
	FolderBuilder();
	virtual ~FolderBuilder();
private:
	bool failed;
	std::wstring dir_name;
	std::wstring big_name;
	std::wstring wee_name;
};



#endif // !defined(AFX_FOLDERBUILDER_H__513AA549_46A7_4914_BA2D_1BB98A054966__INCLUDED_)
