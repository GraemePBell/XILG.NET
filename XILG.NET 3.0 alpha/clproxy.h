// CLProxy.h: Proxy interface for the CommandLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(CLPROXY__INCLUDED_)
#define CLPROXY__INCLUDED_

//#pragma warning(disable:4786)
#include "stdafx.h"


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

public ref class CLProxy  
{
public:
	CLProxy(){ input_paths = gcnew Collections::Generic::List<String^>; };
	virtual ~CLProxy() {} ;
// data
	bool default_css;
	bool output_path_status;
	bool input_path_status;
	bool create_path;
	bool internal_css;
	bool only_html;
	bool no_html;
	bool no_caption;
	bool no_title;
	bool recurse;
	bool verbose;
	bool diagnostic;

	int thumb_height;
	int thumb_width;

	unsigned int pics_per_page;
	unsigned int number_of_pages;
	
	unsigned int banner_height;

	float wm_alpha;
	float wm_scale;

	position pos;

	String^ input_path;
	String^ output_path;
	String^ project_name;
	String^ page_title;
	String^ height_string;
	String^ width_string;
	String^ nohtml_string;
	String^ onlyhtml_string;
	String^ water_mark;
	String^ wm_pos;
	String^ banner;
	String^ usercss;
	
	// CSS stuff
	String^ html_color;
	String^ html_background_color;
	String^ html_background_image;
	String^ html_background_image_position;
	String^ html_background_image_repeat;

	// header
	String^ h1color;
	String^ h1size;
	String^ h1font;
	String^ h1style;
	String^ h1weight;
	String^ h1underline;
	String^ h1strike;


	// anchor
	String^ acolor;
	String^ asize;
	String^ afont;
	String^ astyle;
	String^ aweight;
	String^ aunderline;
	String^ astrike;

	array<String^>^ cmd_params;
	array<String^>^ switch_table;
/*
	Collections::Generic::Dictionary<String^,String^>^ user_params;
*/
	Collections::Generic::List<String^>^ input_paths;

};



#endif // !defined(CLPROXY__INCLUDED_)
