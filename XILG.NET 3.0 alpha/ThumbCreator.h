// ThumbCreator.h: interface for the ThumbCreator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THUMBCREATOR_H__A7329427_62F5_452C_A717_89508B87970A__INCLUDED_)
#define AFX_THUMBCREATOR_H__A7329427_62F5_452C_A717_89508B87970A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PictureHandler.h"
#include "CommandLine.h"
#include "ImageFileList.h"

class ThumbCreator : public PictureHandler
{
public:
	void MakeAndSaveThumbs(const CommandLine& cl, const ImageFileList& ifl);
	void MakeAndSaveThumbsSlowly(const CommandLine &cl, const ImageFileList &ifl, unsigned int index);
	ThumbCreator();
	virtual ~ThumbCreator();
private:
	std::wstring image_src;
	std::wstring image_dst;
};

#endif // !defined(AFX_THUMBCREATOR_H__A7329427_62F5_452C_A717_89508B87970A__INCLUDED_)
