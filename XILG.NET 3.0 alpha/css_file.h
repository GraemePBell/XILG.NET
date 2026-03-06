// css_file.h: interface for the css_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSS_FILE_H__DA82169E_0E92_47E7_B131_A24F5D00B6B6__INCLUDED_)
#define AFX_CSS_FILE_H__DA82169E_0E92_47E7_B131_A24F5D00B6B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include "CommandLine.h"

class css_file  
{
public:
	css_file();
	virtual ~css_file();

	void build(const CommandLine& cl);
	void BiggestThumbSize(std::pair<size_t, size_t >& bts);

private:

	size_t  biggest_thumb_x;
	size_t  biggest_thumb_y;
	void save(path &filename);
	std::wofstream css_out;
	std::wstring css;
	path css_filename;
};

#endif // !defined(AFX_CSS_FILE_H__DA82169E_0E92_47E7_B131_A24F5D00B6B6__INCLUDED_)
