#pragma once
#include "CommandLine.h"

class build_css
{
public:
	build_css(void);
	~build_css(void);
	
	void thumbsize_x(int x);
	void thumbsize_y(int y);

	std::wstring& html(std::wstring& st, const CommandLine& cl);
	std::wstring& h1(std::wstring &st, const CommandLine &cl);
	std::wstring& h2(std::wstring &st, const CommandLine &cl);
	std::wstring& p(std::wstring &st, const CommandLine &cl);
	std::wstring& p_boilerplate(std::wstring &st, const CommandLine &cl);
	std::wstring& div_banner(std::wstring &st, const CommandLine &cl);
	std::wstring& div_float(std::wstring &st, const CommandLine &cl);
	std::wstring& div_container(std::wstring &st, const CommandLine &cl);
	std::wstring& div_spacer(std::wstring &st, const CommandLine &cl);
	std::wstring& anchor(std::wstring &st, const CommandLine &cl);
	std::wstring& anchor_link(std::wstring &st, const CommandLine &cl);
	std::wstring& anchor_active(std::wstring &st, const CommandLine &cl);
	std::wstring& anchor_visited(std::wstring &st, const CommandLine &cl);
	std::wstring& anchor_hover(std::wstring &st, const CommandLine &cl);
	std::wstring& dot_center(std::wstring &st, const CommandLine &cl);
	std::wstring& dot_link(std::wstring &st, const CommandLine &cl);

protected:
	std::wstring& create_selector(std::wstring& selector);
	std::wstring& add_selector(std::wstring& group, const std::wstring& newselector);
	std::wstring& insert_prop_dec(std::wstring& rule,const std::wstring& prop,const std::wstring& dec);
private:
	std::wstring nlf;
	std::wstring temp;
	int biggest_thumb_x;
	int biggest_thumb_y;
};
