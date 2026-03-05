#include "stdafx.h"
#include "build_css.h"


build_css::build_css(void)
{
	nlf.push_back(0x000D);
	nlf.push_back(0x000A);
}

build_css::~build_css(void)
{
}

void build_css::thumbsize_x(int x)
{
	biggest_thumb_x = x;
}

void build_css::thumbsize_y(int y)
{
	biggest_thumb_y = y;
}

std::wstring& build_css::create_selector(std::wstring& selector)
{
	transform(selector.begin(),selector.end(),selector.begin(),tolower);
	selector += L" {}";	
	selector += nlf;
	return selector;
}

std::wstring& build_css::add_selector(std::wstring& rule, const std::wstring& newselector)
{
	std::wstring ns = newselector;
	
	transform(ns.begin(),ns.end(),ns.begin(),tolower);
	
	std::wstring s2 = L" {";
	std::wstring::iterator pos;

	pos = std::search(rule.begin(),rule.end(),s2.begin(),s2.end());
	if (pos != rule.end())
	{
		temp = L", " + ns;
		rule.insert(pos,temp.begin(),temp.end());                 
	}

	return rule;
}

std::wstring& build_css::insert_prop_dec(std::wstring& rule,const std::wstring& prop,const std::wstring& dec)
{
	std::wstring prop1 = prop;
	std::wstring dec1 = dec;

	transform(prop1.begin(),prop1.end(),prop1.begin(),tolower);

	if (prop1 != L"font-family")
		transform(dec1.begin(),dec1.end(),dec1.begin(),tolower);

	std::wstring s1 = L" ";
	std::wstring s2 = L"; }";
	std::wstring s3 = L"{}";
	std::wstring s4 = L"url(";
	std::wstring s5 = L")";
	std::wstring quote = empty;
	std::wstring::iterator pos;

	pos = std::search(dec1.begin(),dec1.end(),s4.begin(),s4.end());
	if (pos != dec1.end())
	{
		// its a url()
		// safer to quote it as a special case
		dec1.insert(pos+s4.length(),1,L'\'');
		pos = std::search(dec1.begin(),dec1.end(),s5.begin(),s5.end());
		dec1.insert(pos,1,'\'');
	}

	// First property or not?
	pos = std::search(rule.begin(),rule.end(),s3.begin(),s3.end());
	if (pos != rule.end())
	{
		pos = std::search(rule.begin(),rule.end(),s3.begin(),s3.end());
		if (pos != rule.end())
		{
			temp = s1 + prop1 + L":" + quote + dec1 + quote + L"; ";
			rule.insert(pos+1,temp.begin(),temp.end());                 
		}
	}
	else
	{
		pos = std::search(rule.begin(),rule.end(),s2.begin(),s2.end());
		if (pos != rule.end())
		{
			temp = s1 + prop1 + L":" + quote + dec1 + quote + L";";
			rule.insert(pos+1,temp.begin(),temp.end());                 
		}
	}
	return rule;
}



std::wstring& build_css::html(std::wstring& st, const CommandLine &cl)
{	
	temp = L"html";
	st = create_selector(temp);
	
	// There's always a color and a background-color
	st = insert_prop_dec(st,L"color",cl.HtmlColor());
	st = insert_prop_dec(st,L"background-color",cl.HtmlBackgroundColor());
	st = insert_prop_dec(st,L"margin-right",L"5%");

	// but not always a background image
	if (cl.HtmlBackgroundImage() != empty)
	{
		std::wstring bi = L"images/";
		bi += PathFindFileName(cl.HtmlBackgroundImage().c_str());

		st = insert_prop_dec(st,L"background-image",L"url(" + bi +L")");

		std::wstring rep = cl.HtmlBackgroundImageRepeat();
		if (rep != empty)
		{
			st = insert_prop_dec(st,L"background-repeat",rep);
		}

		std::wstring pos = cl.HtmlBackgroundImagePosition();
		if (pos != empty)
		{
			st = insert_prop_dec(st,L"background-position",pos);
		}
	}
	return st;
}

std::wstring& build_css::h1(std::wstring &st, const CommandLine &cl)
{
	temp = L"h1";
	bool strike = (cl.H1Strike() != empty);
	bool under = (cl.H1Underline()!=empty);

	std::wstring td = L"none";
	if (strike || under)
	{
		if (strike)
		{
			td = cl.H1Strike();
			if (under)
			{
				td += L" ";
				td += cl.H1Underline();
			}
		}
		else
		{
			td = cl.H1Underline();
		}
	}

	st = create_selector(temp);
	st = insert_prop_dec(st,L"text-align",L"center");
	st = insert_prop_dec(st,L"color",cl.H1Color());
	st = insert_prop_dec(st,L"font-family",cl.H1Font());
	st = insert_prop_dec(st,L"font-weight",cl.H1Weight());
	st = insert_prop_dec(st,L"font-style",cl.H1Style());
	st = insert_prop_dec(st,L"font-size",cl.H1Size());
	st = insert_prop_dec(st,L"text-decoration",td);

	return st;
}

std::wstring& build_css::div_banner(std::wstring &st, const CommandLine &cl)
{
	std::wstring bi = L"images/";
	bi += PathFindFileName(cl.BannerImage().c_str());

	wchar_t buf1[0x10];
	_itow_s(cl.BannerHeight(),buf1,0x10,10);
	std::wstring height = buf1;
	height += L"px";

	temp = L"div.banner";
	st = create_selector(temp);
	st = insert_prop_dec(st,L"font-size",L"1pt");
	st = insert_prop_dec(st,L"background-image",L"url(" + bi + L")"  );
	st = insert_prop_dec(st,L"background-repeat",L"no-repeat");
	st = insert_prop_dec(st,L"background-position",L"center");
	st = insert_prop_dec(st,L"height",height);

	return st;
}

std::wstring& build_css::h2(std::wstring &st, const CommandLine &cl)
{
	UNREFERENCED_PARAMETER(cl);
	temp = L"h2";
	st = create_selector(temp);
	st = insert_prop_dec(st,L"text-align",L"center");
	st = insert_prop_dec(st,L"color",L"black");
	st = insert_prop_dec(st,L"font-family",L"serif");

	return st;
}

std::wstring& build_css::p(std::wstring &st, const CommandLine &cl)
{
	temp = L"p";
	st = create_selector(temp);
	st = insert_prop_dec(st,L"text-align",L"center");
	st = insert_prop_dec(st,L"color",cl.HtmlColor());
	st = insert_prop_dec(st,L"font-family",cl.AFont());

	return st;
}

std::wstring& build_css::p_boilerplate(std::wstring &st, const CommandLine &cl)
{
	UNREFERENCED_PARAMETER(cl);
	temp = L"p.boilerplate";
	st = create_selector(temp);
	st = insert_prop_dec(st,L"font-size",L"xx-small");
	st = insert_prop_dec(st,L"color",L"gray");

	return st;
}

std::wstring& build_css::div_float(std::wstring &st, const CommandLine &cl)
{
	UNREFERENCED_PARAMETER(cl);
	wchar_t buf1[0xF];
	wchar_t buf2[0xF];

	_itow_s(biggest_thumb_x,buf1,0xF,10);
	_itow_s(biggest_thumb_y,buf2,0xF,10);

	std::wstring width = buf1;
	std::wstring height = buf2;
	width += L"px";
	height += L"px";
	
	temp = L"div.float";
	st = create_selector(temp);
	st = insert_prop_dec(st,L"float",L"left");
	st = insert_prop_dec(st,L"margin",L"5px");
	st = insert_prop_dec(st,L"width",width);
	st = insert_prop_dec(st,L"height",height);

	return st;
}

std::wstring& build_css::div_container(std::wstring &st, const CommandLine &cl)
{
	UNREFERENCED_PARAMETER(cl);
	temp = L"div.container";
	st = create_selector(temp);
	st = insert_prop_dec(st,L"text-align",L"center");
	st = insert_prop_dec(st,L"margin-left",L"15%");
	st = insert_prop_dec(st,L"margin-right",L"5%");

	return st;
}

std::wstring& build_css::div_spacer(std::wstring &st, const CommandLine &cl)
{
	UNREFERENCED_PARAMETER(cl);
	temp = L"div.spacer";
	st = create_selector(temp);
	st = insert_prop_dec(st,L"clear",L"both");

	return st;
}

std::wstring& build_css::anchor(std::wstring &st, const CommandLine &cl)
{
	temp = L"a";
	bool strike = (cl.AStrike() != empty);
	bool under = (cl.AUnderline()!=empty);

	std::wstring td = L"none";
	if (strike || under)
	{
		if (strike)
		{
			td = cl.AStrike();
			if (under)
			{
				td += L" ";
				td += cl.AUnderline();
			}
		}
		else
		{
			td = cl.AUnderline();
		}
	}

	st = create_selector(temp);
	st = insert_prop_dec(st,L"font-size",cl.ASize());
	st = insert_prop_dec(st,L"font-weight",cl.AWeight());
	st = insert_prop_dec(st,L"font-style",cl.AStyle());
	st = insert_prop_dec(st,L"font-family",cl.AFont());
	st = insert_prop_dec(st,L"text-decoration",td);

	return st;
}

std::wstring& build_css::anchor_link(std::wstring &st, const CommandLine &cl)
{
	temp = L"a:link";
	st = create_selector(temp);
	st = insert_prop_dec(st,L"color",cl.AColor());

	return st;
}

std::wstring& build_css::anchor_active(std::wstring &st, const CommandLine &cl)
{
	UNREFERENCED_PARAMETER(cl);
	temp = L"a:active";
	st = create_selector(temp);
	st = insert_prop_dec(st,L"color",L"red");

	return st;
}

std::wstring& build_css::anchor_visited(std::wstring &st, const CommandLine &cl)
{
	UNREFERENCED_PARAMETER(cl);
	temp = L"a:visited";
	st = create_selector(temp);
	st = insert_prop_dec(st,L"color",L"purple");

	return st;
}

std::wstring& build_css::anchor_hover(std::wstring &st, const CommandLine &cl)
{
	UNREFERENCED_PARAMETER(cl);
	temp = L"a:hover";
	st = create_selector(temp);
	st = insert_prop_dec(st,L"color",L"red");

	return st;
}

std::wstring& build_css::dot_center(std::wstring &st, const CommandLine &cl)
{
	UNREFERENCED_PARAMETER(cl);
	temp = L".center";
	st = create_selector(temp);
	st = insert_prop_dec(st,L"text-align",L"center");

	return st;
}

std::wstring& build_css::dot_link(std::wstring &st, const CommandLine &cl)
{
	UNREFERENCED_PARAMETER(cl);
	temp = L".link";
	st = create_selector(temp);
	st = insert_prop_dec(st,L"width",L"50%");
	st = insert_prop_dec(st,L"margin-left",L"25%");
	st = insert_prop_dec(st,L"margin-right",L"25%");
	return st;
}
