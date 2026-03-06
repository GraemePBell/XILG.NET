// CommandLine.cpp: implementation of the CommandLine class.
//
//////////////////////////////////////////////////////////////////////
//#pragma warning(disable:4786)
#include "stdafx.h"
#include "CommandLine.h"


//////////////////////////////////////////////////////////////////////
// CommandLine Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CommandLine::CommandLine()
{
	InputStatus(false);
	OutputStatus(false);

	BuildSwitchTable();

	// Do the command thing
	ParseCommandLine();
}

CommandLine::CommandLine(const std::wstring& app_name)
{
	application_name = app_name;
	InputStatus(false);
	OutputStatus(false);

	BuildSwitchTable();

	Defaults();
}

CommandLine::~CommandLine()
{
}


void CommandLine::BuildSwitchTable()
{
	switch_table.push_back(switch_diagnostic);	// verbose error messages
	switch_table.push_back(switch_i);			// input path
	switch_table.push_back(switch_o);			// output path
	switch_table.push_back(switch_p);			// project title
	switch_table.push_back(switch_t);			// page title 
	switch_table.push_back(switch_h);			// thumbnail height
	switch_table.push_back(switch_w);			// thumbnail width
	switch_table.push_back(switch_ic);			// internal css
	switch_table.push_back(switch_css);			// user css
	switch_table.push_back(switch_nc);			// don't create new folders - may cause failure
	switch_table.push_back(switch_nohtml);		// only create XML, XSL & CSS
	switch_table.push_back(switch_onlyhtml);	// delete XML & XSL intermediates
	switch_table.push_back(switch_query);		// show help screen
	switch_table.push_back(switch_nocaption);	// no captions under the images
	switch_table.push_back(switch_notitle);		// no title 
	switch_table.push_back(switch_watermark);	// watermark the large image
	switch_table.push_back(switch_wmpos);		// where to put the watermark
	switch_table.push_back(switch_wmalpha);		// how transparent the watermark is
	switch_table.push_back(switch_wmscale);		// how big the watermark is
	switch_table.push_back(switch_hcolor);		// html text color
	switch_table.push_back(switch_hbcolor);		// html background color
	switch_table.push_back(switch_hbimage);		// html background image
	switch_table.push_back(switch_hbimpos);		// html background image position
	switch_table.push_back(switch_hbimrep);		// html background image repeat
	switch_table.push_back(switch_banner);		// banner
	switch_table.push_back(switch_mipp);		// maximum images per page
	switch_table.push_back(switch_recurse);		// recurse subdirectories
	switch_table.push_back(switch_verbose);		// verbose output during processing
	switch_table.push_back(switch_h1color);		// h1 text color
	switch_table.push_back(switch_h1size);		// h1 size
	switch_table.push_back(switch_h1font);		// h1 font
	switch_table.push_back(switch_h1style);		// h1 style
	switch_table.push_back(switch_h1weight);	// h1 weight
	switch_table.push_back(switch_h1underline);	// h1 underline
	switch_table.push_back(switch_h1strike);	// h1 strikeout
	switch_table.push_back(switch_acolor);		// a color
	switch_table.push_back(switch_asize);		// a size
	switch_table.push_back(switch_afont);		// a font
	switch_table.push_back(switch_astyle);		// a style
	switch_table.push_back(switch_aweight);		// a weight
	switch_table.push_back(switch_aunderline);	// a underline
	switch_table.push_back(switch_astrike);		// a strikeout
}


void CommandLine::ParseCommandLine()
{
	Defaults();

	std::wstring cmd_line = GetCommandLine();
//delete	std::wstring::size_type spos = 0;
	std::vector<std::wstring>::iterator vi;

	arguments = CommandLineToArgvW(cmd_line.c_str(), &arg_count);

	int count =0 ;

	for (count = 0; count < arg_count; count++)
	{
		cmd_params.push_back(arguments[count]);
	}

	GlobalFree(arguments);

	if (arg_count ==1 )
		throw (help());


	for(vi = switch_table.begin(); vi < switch_table.end() ; vi++)
	{
		for (count = 0; count < arg_count; count++)
		{
			std::wstring user_parameter = cmd_params[count];
			if (*vi == user_parameter)
			{
				if (IsParamUnary(user_parameter))
				{
					user_params[*vi] = b_true;
				}
				else
				{
					if (count+1 < arg_count)
					{
						std::wstring next_user_parameter = cmd_params[count+1];

						if (!IsValidSwitch(next_user_parameter))
						{
							if(*vi == switch_i)
							{
								// Doing this here enables multiple input paths
								InputPath(next_user_parameter);
							}
							user_params[*vi] = cmd_params[count+1];
						}
						else
						{
							std::wstring xilgerr = L"Bad Parameter - not expecting " + cmd_params[count+1] + L" here!\n";
							std::wstring xilgerr_line = stringer(__LINE__);
							std::wstring xilgerr_file = widen(__FILE__);
							throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
						}
					}
					else
					{
						std::wstring xilgerr = L"Bad Parameter - expecting a value after: " + user_parameter + L"\n";
						std::wstring xilgerr_line = stringer(__LINE__);
						std::wstring xilgerr_file = widen(__FILE__);
						throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
					}
				}
			}
		}
	}

	ValidateEssentialParameters();
	SetNonEssentialParameters();
}

bool CommandLine::IsParamUnary(std::wstring param)
{

	bool is_unary = false;

	if(param == switch_ic)
		is_unary = true;
	if(param == switch_nc)
		is_unary = true;
	if(param == switch_nohtml)
		is_unary = true;
	if(param == switch_onlyhtml)
		is_unary = true;
	if(param == switch_query)
		is_unary = true;
	if(param == switch_nocaption)
		is_unary = true;
	if(param == switch_notitle)
		is_unary = true;
	if(param == switch_recurse)
		is_unary = true;
	if(param == switch_verbose)
		is_unary = true;
	if(param == switch_diagnostic)
		is_unary = true;


	return is_unary;
}

bool CommandLine::IsValidSwitch(std::wstring param)
{
	std::vector<std::wstring>::iterator vi;
	bool is_valid = false;

	for(vi = switch_table.begin(); vi < switch_table.end() ; vi++)
	{
		if (*vi == param)
			is_valid = true;
	}
	
	return is_valid;
}

void CommandLine::ValidateEssentialParameters()
{
	
	if (user_params[switch_i] == empty)
	{
		std::wstring xilgerr = L"No input folders specified!";
		std::wstring xilgerr_line = stringer(__LINE__);
		std::wstring xilgerr_file = widen(__FILE__);
		throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
	}
	if (user_params[switch_o] != empty)
	{
		// not empty - really need to do better validation here
		OutputPath(user_params[switch_o]);
		OutputStatus(true);
	}	
}

void CommandLine::SetNonEssentialParameters()
{
	std::wstring temp;
	
	temp = user_params[switch_query];
	if (temp == b_true)
	{
		throw(help());
	}	
	temp = user_params[switch_p];
	if (temp != empty)
	{
		ProjectName(temp);
	}	
	temp = user_params[switch_t];
	if (temp != empty)
	{
		PageTitle(temp);
	}	
	temp = user_params[switch_h];
	if (temp != empty)
	{
		ThumbHeight(temp);
	}	
	temp = user_params[switch_w];
	if (temp != empty)
	{
		ThumbWidth(temp);
	}	
	temp = user_params[switch_ic];
	if (temp == b_true)
	{
		InternalCSS(true);
	}
	temp = user_params[switch_css];
	if (temp != empty)
	{
		if (PathFileExists(temp.c_str()))
		{
			UserCSS(temp);
		}
		else
		{
			std::wstring xilgerr = L"Bad user specified CSS file!";
			std::wstring xilgerr_line = stringer(__LINE__);
			std::wstring xilgerr_file = widen(__FILE__);
			throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
		}
	}
	temp = user_params[switch_nc];
	if (temp == b_true)
	{
		PathCreate(false);
	}	
	temp = user_params[switch_nohtml];
	if (temp == b_true)
	{
		NoHTML(true);
	}	
	temp = user_params[switch_onlyhtml];
	if (temp == b_true)
	{
		OnlyHTML(true);
	}	
	temp = user_params[switch_nocaption];
	if (temp == b_true)
	{
		NoCaption(true);
	}	
	temp = user_params[switch_notitle];
	if (temp == b_true)
	{
		NoTitle(true);
	}	
	temp = user_params[switch_watermark];
	if (temp != empty)
	{
		SetWM(temp);
	}
	temp = user_params[switch_hcolor];
	if (temp != empty)
	{
		HtmlColor(temp);
	}
	temp = user_params[switch_hbcolor];
	if (temp != empty)
	{
		HtmlBackgroundColor(temp);
	}
	temp = user_params[switch_hbimage];
	if (temp != empty)
	{
		HtmlBackgroundImage(temp);
	}
	temp = user_params[switch_banner];
	if (temp != empty)
	{
		if (PathFileExists(temp.c_str()))
		{
			BannerImage(temp);
		}
		else
		{
			std::wstring xilgerr = L"Banner image file not found";
			std::wstring xilgerr_line = stringer(__LINE__);
			std::wstring xilgerr_file = widen(__FILE__);
			throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
		}
	}
	temp = user_params[switch_mipp];
	if (temp != empty)
	{
		ImagesPerPage(temp);
	}
	temp = user_params[switch_recurse];
	if (temp == b_true)
	{
		Recurse(true);
	}
	temp = user_params[switch_verbose];
	if (temp == b_true)
	{
		Verbose(true);
	}
	temp = user_params[switch_diagnostic];
	if (temp == b_true)
	{
		Diagnostic(true);
	}
	temp = user_params[switch_h1color];
	if (temp != empty)
	{
		H1Color(temp);
	}
	temp = user_params[switch_h1size];
	if (temp != empty)
	{
		H1Size(temp);
	}
	temp = user_params[switch_h1font];
	if (temp != empty)
	{
		H1Font(temp);
	}
	temp = user_params[switch_h1style];
	if (temp != empty)
	{
		H1Style(temp);
	}
	temp = user_params[switch_h1weight];
	if (temp != empty)
	{
		H1Weight(temp);
	}
	temp = user_params[switch_h1underline];
	if (temp != empty)
	{
		H1Underline(temp);
	}
	temp = user_params[switch_h1strike];
	if (temp != empty)
	{
		H1Strike(temp);
	}
	temp = user_params[switch_acolor];
	if (temp != empty)
	{
		AColor(temp);
	}
	temp = user_params[switch_asize];
	if (temp != empty)
	{
		ASize(temp);
	}
	temp = user_params[switch_afont];
	if (temp != empty)
	{
		AFont(temp);
	}
	temp = user_params[switch_astyle];
	if (temp != empty)
	{
		AStyle(temp);
	}
	temp = user_params[switch_aweight];
	if (temp != empty)
	{
		AWeight(temp);
	}
	temp = user_params[switch_aunderline];
	if (temp != empty)
	{
		AUnderline(temp);
	}
	temp = user_params[switch_astrike];
	if (temp != empty)
	{
		AStrike(temp);
	}
}

void CommandLine::Defaults()
{
	ProjectName(L"Thumbnails");
	PageTitle(L"My Thumbnail Pictures");
	PathCreate(true);
	DefaultCSS(true);
	InternalCSS(false);
	// InputPath(L".");
	InputStatus(false);
	OutputPath(L"My Thumbnail Page");
	OutputStatus(true);
	ThumbHeight(75);
	ThumbWidth(100);
	OnlyHTML(false);
	NoHTML(false);
	WaterMark(empty);
	WatermarkPosition(position::br);
	WatermarkAlpha(0.2f);
	WatermarkScale(0.2f);
	NoCaption(false);
	NoTitle(false);
	HtmlColor(L"black");
	HtmlBackgroundColor(L"silver");
	HtmlBackgroundImage(empty);
	HtmlBackgroundImagePosition(empty);
	HtmlBackgroundImageRepeat(empty);
	BannerImage(empty);
	ImagesPerPage(0);
	NumberOfPages(1);
	Recurse(false);
	Verbose(false);
	Diagnostic(::diagnostic);
	UserCSS(empty);
	H1Font(L"serif");
	H1Size(L"xx-large");
	H1Color(HtmlColor());
	H1Style(L"normal");
	H1Weight(L"bold");
	H1Underline(empty);
	H1Strike(empty);
	AFont(L"serif");
	ASize(L"medium");
	AColor(L"blue");
	AStyle(L"normal");
	AWeight(L"normal");
	AUnderline(empty);
	AStrike(empty);

}


const path& CommandLine::ProjectName() const
{
	return project_name;
}

void CommandLine::ProjectName(const path& p_name)
{
	project_name = p_name;
//	replace(project_name.begin(),project_name.end(),L' ',L'_');
}

void CommandLine::PageTitle(const path& p_name)
{
	page_title = p_name;
}

void CommandLine::InputPath(const path& i_path)
{
	if (PathIsDirectory(i_path.c_str()))
	{
		input_path = i_path;
		InsertInputPath(input_path);
		InputStatus(true);
	}
	else
	{
		std::wstring xilgerr = L"Bad input folder -- \"";
		xilgerr += i_path;
		xilgerr += L"\" is not a valid folder!"; 
		std::wstring xilgerr_line = stringer(__LINE__);
		std::wstring xilgerr_file = widen(__FILE__);
		throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
	}
}

const path& CommandLine::InputPath() const
{
	return input_paths.front();
}


void CommandLine::OutputPath(const path& o_path)
{
	output_path = o_path;
	OutputStatus(true);
}

const path& CommandLine::OutputPath() const
{
	return output_path;
}


const path& CommandLine::PageTitle() const
{
	return page_title;
}


void CommandLine::OutputStatus(bool status)
{
	output_path_status = status;
}

bool CommandLine::OutputStatus() const
{
	return output_path_status;
}


bool CommandLine::InputStatus() const
{
	return input_path_status;
}

void CommandLine::InputStatus(bool status)
{
	input_path_status = status;
}


void CommandLine::PathCreate(bool status)
{
	create_path = status;
}

const bool CommandLine::PathCreate() const
{
	return create_path;
}

const std::wstring& CommandLine::NotPathCreate_Bool_String() const
{
	if (create_path)
		return b_false;
	else
		return b_true;
}


void CommandLine::DefaultCSS(bool status)
{
	default_css = status;
}

const bool CommandLine::DefaultCSS() const
{
	return default_css;
}


void CommandLine::InternalCSS(bool status)
{
	internal_css = status;
}

const bool CommandLine::InternalCSS() const
{
	return internal_css;
}


void CommandLine::NoCaption(bool nc)
{
	no_caption = nc;
}

bool CommandLine::NoCaption() const
{
	return no_caption;
}

void CommandLine::NoTitle(bool nt)
{
	no_title = nt;
}

bool CommandLine::NoTitle() const
{
	return no_title;
}

void CommandLine::NoHTML(bool status)
{
	no_html = status;
}

bool CommandLine::NoHTML() const
{
	return no_html;
}

const std::wstring& CommandLine::NoHTML_Bool_String() const
{
	return nohtml_string;
}


void CommandLine::OnlyHTML(bool status)
{
	only_html = status;
}

bool CommandLine::OnlyHTML() const
{
	return only_html;
}

const std::wstring& CommandLine::OnlyHTML_Bool_String() const
{
	return onlyhtml_string;
}


const std::wstring& CommandLine::DefaultCSS_Bool_String() const
{
	if (default_css)
		return b_true;
	else
		return b_false;
}
const std::wstring& CommandLine::InternalCSS_Bool_String() const
{
	if (internal_css)
		return b_true;
	else
		return b_false;
}


void CommandLine::WatermarkPosition(const position p)
{
	pos = p;
}

position CommandLine::WatermarkPosition(void) const
{
	return pos;
}


size_t CommandLine::ThumbWidth() const
{
	return thumb_width;
}

size_t CommandLine::ThumbHeight() const
{
	return thumb_height;
}

void CommandLine::ThumbHeight(int h)
{
	std::wstringstream wss;

	thumb_height = h;

	wss << h;
	height_string = wss.str();
	wss.flush();
}

void CommandLine::ThumbWidth(int w)
{
	std::wstringstream wss;

	thumb_width = w;
	
	wss << w;
	width_string = wss.str();
	wss.flush();
}

void CommandLine::ThumbHeight(const std::wstring& h)
{
	int temp = _wtoi(h.c_str());
	if (temp)
		thumb_height = temp;
	else
	{
		std::wstring xilgerr = L"Incorrect value for thumbnail height";
		std::wstring xilgerr_line = stringer(__LINE__);
		std::wstring xilgerr_file = widen(__FILE__);
		throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
	}
}

void CommandLine::ThumbWidth(const std::wstring& w)
{
	int temp = _wtoi(w.c_str());
	if (temp)
		thumb_width = temp;
	else
	{
		std::wstring xilgerr = L"Incorrect value for thumbnail width";
		std::wstring xilgerr_line = stringer(__LINE__);
		std::wstring xilgerr_file = widen(__FILE__);
		throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
	}
}

const std::wstring& CommandLine::ThumbHeightString() const
{
	return height_string;
}

const std::wstring& CommandLine::ThumbWidthString() const
{
	return width_string;
}



const path& CommandLine::WaterMark() const
{
	return water_mark;
}

void CommandLine::WaterMark(const path& wm)
{
	water_mark = wm;
}

void CommandLine::ParseWmPos(const std::wstring& wmpos)
{
	bool valid = false;
	std::wstring wmp = wmpos;
	std::transform(wmp.begin(),wmp.end(),wmp.begin(),tolower);
	
	if (wmp == L"tl")
	{
		WatermarkPosition(position::tl);
		valid = true;
	}
	if (wmp == L"tc")
	{
		WatermarkPosition(position::tc);
		valid = true;
	}
	if (wmp == L"tr")
	{
		WatermarkPosition(position::tr);
		valid = true;
	}
	if (wmp == L"cl")
	{
		WatermarkPosition(position::lc);
		valid = true;
	}
	if (wmp == L"center" || wmp == L"centre")
	{
		WatermarkPosition(position::center);
		valid = true;
	}
	if (wmp == L"cr")
	{
		WatermarkPosition(position::cr);
		valid = true;
	}
	if (wmp == L"bl")
	{
		WatermarkPosition(position::bl);
		valid = true;
	}
	if (wmp == L"bc")
	{
		WatermarkPosition(position::bc);
		valid = true;
	}
	if (wmp == L"br")
	{
		WatermarkPosition(position::br);
		valid = true;
	}
	if (!valid)
	{
		std::wstring xilgerr = L"Incorrect watermark position!";
		std::wstring xilgerr_line = stringer(__LINE__);
		std::wstring xilgerr_file = widen(__FILE__);
		throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
	}
}

void CommandLine::WatermarkAlpha(const float wma)
{
	wm_alpha = wma;
}

const float CommandLine::WatermarkAlpha() const
{
	return wm_alpha;
}

void CommandLine::WatermarkScale(const float wms)
{
	wm_scale = wms;
}

const float CommandLine::WatermarkScale() const
{
	return wm_scale;
}

void CommandLine::SetWM(const path& wsr)
{
	if (PathFileExists(wsr.c_str()))
	{
		WaterMark(wsr);
	}
	else
	{
		std::wstring xilgerr = L"Watermark file not found!";
		std::wstring xilgerr_line = stringer(__LINE__);
		std::wstring xilgerr_file = widen(__FILE__);
		throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
	}

	std::wstring temp;

	temp = user_params[switch_wmpos];
	if (temp != empty)
	{
			ParseWmPos(temp);
	}

	temp = user_params[switch_wmalpha];
	if (temp != empty)
	{
		float alpha = (float)_wtof(temp.c_str());
		if ((alpha >= 0.0f) && (alpha <= 1.0f))
			WatermarkAlpha(alpha);
		else
		{
			std::wstring xilgerr = L"wmalpha must be in the range 0.0 to 1.0 (default 0.2)";
			std::wstring xilgerr_line = stringer(__LINE__);
			std::wstring xilgerr_file = widen(__FILE__);
			throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
		}
	}	

	temp = user_params[switch_wmscale];
	if (temp != empty)
	{
		float scale = (float)_wtof(temp.c_str());
		if ((scale > 0.0f) && (scale <= 1.0f))
			WatermarkScale(scale);
		else
		{
			std::wstring xilgerr = L"wmscale must be > 0 and <= 1.0 (default: 0.2)";
			std::wstring xilgerr_line = stringer(__LINE__);
			std::wstring xilgerr_file = widen(__FILE__);
			throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
		}
	}	
}

const std::wstring& CommandLine::HtmlColor(void) const
{
	return html_color;
}

void CommandLine::HtmlColor(const std::wstring &color)
{
	// Oh good grief - monster validation required
	// accept in octal, decimal, hex, or standard names
	// at least it's a string
	// farm it off to another function - because it'll be useful
	html_color = color;
}

const std::wstring& CommandLine::HtmlBackgroundColor() const
{
	return html_background_color;
}

void CommandLine::HtmlBackgroundColor(const std::wstring &color)
{
	// More grief - monster validation required
	// accept in octal, decimal, hex, or standard names
	// at least it's a string
	// farm it off to another function - because it'll be useful
	html_background_color = color;
}


const std::wstring& CommandLine::HtmlBackgroundImage(void) const
{
	return html_background_image;
}

void CommandLine::HtmlBackgroundImage(const std::wstring &image)
{
	if (image != empty)
	{
		if (PathFileExists(image.c_str()))
		{
			html_background_image = image;

			// only deal with these if we need to :)
			if (application_name != L"XILG")
			{
				std::wstring temp = user_params[switch_hbimpos];
				if (temp != empty)
				{
					HtmlBackgroundImagePosition(temp);
				}
				temp = user_params[switch_hbimrep];
				if (temp != empty)
				{
					HtmlBackgroundImageRepeat(temp);
				}
			}
		}
		else
		{
			std::wstring xilgerr = L"Background image file not found";
			std::wstring xilgerr_line = stringer(__LINE__);
			std::wstring xilgerr_file = widen(__FILE__);
			throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
		}
	}
}


const std::wstring& CommandLine::HtmlBackgroundImageRepeat(void) const
{
	return html_background_image_repeat;
}

void CommandLine::HtmlBackgroundImageRepeat(const std::wstring &repeat)
{
	// simple Validation - can be done upstream
	html_background_image_repeat = repeat;
}

const std::wstring& CommandLine::HtmlBackgroundImagePosition(void) const
{
	return html_background_image_position;
}

void CommandLine::HtmlBackgroundImagePosition(const std::wstring &pos)
{
	// simple Validation - can be done upstream
	html_background_image_position = pos;
}

const path& CommandLine::BannerImage(void) const
{
	return banner;
}

void CommandLine::BannerImage(const path &banner_path)
{
	banner = banner_path;
}

const size_t CommandLine::BannerHeight(void) const
{
	return banner_height;
}

void CommandLine::BannerHeight(const size_t h)
{
	banner_height = h;
}

const size_t CommandLine::ImagesPerPage(void) const
{
	return pics_per_page;
}

void CommandLine::ImagesPerPage(const size_t h)
{
	pics_per_page = h;
}

void CommandLine::ImagesPerPage(const std::wstring& mipp)
{
	size_t temp = _wtoi(mipp.c_str());
	if (temp)
		pics_per_page = temp;
	else
	{
		std::wstring xilgerr = L"Incorrect value for number of pages";
		std::wstring xilgerr_line = stringer(__LINE__);
		std::wstring xilgerr_file = widen(__FILE__);
		throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
	}
}

const size_t CommandLine::NumberOfPages(void) const
{
	return number_of_pages;
}

void CommandLine::NumberOfPages(const size_t h)
{
	number_of_pages = h;
}

void CommandLine::InsertInputPath(const path &i_path)
{
	input_paths.push_back(i_path);
	input_paths.unique();
}

const size_t CommandLine::NumberOfInputPaths() const
{
	return input_paths.size();
}

const std::list<path>& CommandLine::InputPaths() const
{
	return input_paths;
}

void CommandLine::Recurse(bool r)
{
	recurse = r;
}

const bool CommandLine::Recurse() const
{
	return recurse;
}

void CommandLine::Verbose(bool v)
{
	verbose = v;
}

const bool CommandLine::Verbose() const
{
	return verbose;
}

void CommandLine::Diagnostic(bool d)
{
	::diagnostic = d;
	diagnostic = d;
}

const bool CommandLine::Diagnostic() const
{
	return diagnostic;
}

void CommandLine::UserCSS(const path& csspath)
{
	usercss = csspath;
}

const path& CommandLine::UserCSS(void) const
{
	return usercss;
}

const std::wstring& CommandLine::H1Color() const
{
	return h1color;
}

const std::wstring& CommandLine::H1Size() const
{
	return h1size;
}

const std::wstring& CommandLine::H1Font() const
{
	return h1font;
}

const std::wstring& CommandLine::H1Style() const
{
	return h1style;
}

const std::wstring& CommandLine::H1Weight() const
{
	return h1weight;
}

const std::wstring& CommandLine::H1Underline() const
{
	return h1underline;
}

const std::wstring& CommandLine::H1Strike() const
{
	return h1strike;
}

void CommandLine::H1Color(const std::wstring& color)
{
	h1color = color;
}

void CommandLine::H1Font(const std::wstring &font)
{
	h1font = font;
}

void CommandLine::H1Size(const std::wstring &size)
{
	h1size = size;
}

void CommandLine::H1Weight(const std::wstring &weight)
{
	h1weight = weight;
}

void CommandLine::H1Style(const std::wstring &style)
{
	h1style = style;
}


void CommandLine::H1Underline(const std::wstring &ul)
{
	h1underline = ul;
}

void CommandLine::H1Strike(const std::wstring &st)
{
	h1strike = st;
}


const std::wstring& CommandLine::AColor() const
{
	return acolor;
}

const std::wstring& CommandLine::ASize() const
{
	return asize;
}

const std::wstring& CommandLine::AFont() const
{
	return afont;
}

const std::wstring& CommandLine::AStyle() const
{
	return astyle;
}

const std::wstring& CommandLine::AWeight() const
{
	return aweight;
}

const std::wstring& CommandLine::AUnderline() const
{
	return aunderline;
}

const std::wstring& CommandLine::AStrike() const
{
	return astrike;
}

void CommandLine::AColor(const std::wstring& color)
{
	acolor = color;
}

void CommandLine::AFont(const std::wstring &font)
{
	afont = font;
}

void CommandLine::ASize(const std::wstring &size)
{
	asize = size;
}

void CommandLine::AWeight(const std::wstring &weight)
{
	aweight = weight;
}

void CommandLine::AStyle(const std::wstring &style)
{
	astyle = style;
}

void CommandLine::AUnderline(const std::wstring &ul)
{
	aunderline = ul;
}

void CommandLine::AStrike(const std::wstring &st)
{
	astrike = st;
}
