// CommandLine.h: interface for the CommandLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMANDLINE_H__00A40212_F8FC_46F6_A41E_6BC5E203D777__INCLUDED_)
#define AFX_COMMANDLINE_H__00A40212_F8FC_46F6_A41E_6BC5E203D777__INCLUDED_

//#pragma warning(disable:4786)
#include "stdafx.h"


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
enum position { center, cr, tc, lc, bc, br, bl, tr, tl };

class CommandLine  
{
public:
	CommandLine();
	CommandLine(const std::wstring& app_name);
	virtual ~CommandLine();

	///////////////////// GET FUNCTIONS //////////////////////////////
	
	const std::wstring& OutputPath() const;
	const std::wstring& InputPath() const;
	const std::wstring& ProjectName() const;
	const std::wstring& PageTitle() const;
	const std::wstring& WaterMark() const;

	int ThumbHeight() const;
	int ThumbWidth() const;
	const std::wstring& ThumbHeightString() const;
	const std::wstring& ThumbWidthString() const;

	const bool PathCreate() const;
	const bool DefaultCSS() const;
	const bool InternalCSS() const;

	bool InputStatus() const; 
	bool OutputStatus() const;
	bool NoHTML() const;
	bool OnlyHTML() const;
	bool NoCaption() const;
	bool NoTitle() const;
	const bool Recurse() const;
	const bool Verbose() const;
	const bool Diagnostic() const;
	position WatermarkPosition() const;
	const float WatermarkAlpha() const;
	const float WatermarkScale() const;
	
	const std::wstring& HtmlColor() const;
	const std::wstring& HtmlBackgroundColor() const;
	const std::wstring& HtmlBackgroundImage() const;
	const std::wstring& HtmlBackgroundImageRepeat() const;
	const std::wstring& HtmlBackgroundImagePosition() const;

	const std::wstring& BannerImage() const;
	const size_t BannerHeight() const;

	const size_t ImagesPerPage() const;
	const size_t NumberOfPages() const;

	const size_t NumberOfInputPaths() const; 
	const std::list<std::wstring>& InputPaths() const;

	const std::wstring& UserCSS() const;

	// header
	const std::wstring& H1Color() const;
	const std::wstring& H1Size() const;
	const std::wstring& H1Font() const;
	const std::wstring& H1Style() const;
	const std::wstring& H1Weight() const;
	const std::wstring& H1Underline() const;
	const std::wstring& H1Strike() const;

	// anchor
	const std::wstring& AColor() const;
	const std::wstring& ASize() const;
	const std::wstring& AFont() const;
	const std::wstring& AStyle() const;
	const std::wstring& AWeight() const;
	const std::wstring& AUnderline() const;
	const std::wstring& AStrike() const;

	////////////////////////////// SET FUNCTIONS ////////////////////////////////////
	
	void OutputPath(const std::wstring o_path);
	void InputPath(const std::wstring i_path);
	void ProjectName(const std::wstring p_name);
	void PageTitle(const std::wstring p_title);

	void WatermarkPosition(const position p);
	void WaterMark(const std::wstring& wm);
	void WatermarkAlpha(const float wma);
	void WatermarkScale(const float wms);

	void PathCreate(bool status);
	void DefaultCSS(bool status);
	void InternalCSS(bool status);
	void NoHTML(bool status);
	void OnlyHTML(bool status);
	void ThumbWidth(int w);
	void ThumbHeight(int h);
	void NoCaption(bool nc);
	void NoTitle(bool nt);
	void Recurse(bool r);
	void Verbose(bool v);
	void Diagnostic(bool d);

	void ThumbHeight(const std::wstring& h);
	void ThumbWidth(const std::wstring& h);
	void SetWM(const std::wstring& wsr);
	void ParseWmPos(const std::wstring& wmp);

	void BannerImage(const std::wstring& banner_path);
	void BannerHeight(const size_t h);

	void ImagesPerPage(const size_t h);
	void NumberOfPages(const size_t h);

	void HtmlColor(const std::wstring& color);
	void HtmlBackgroundColor(const std::wstring& color);
	void HtmlBackgroundImage(const std::wstring& image);
	void HtmlBackgroundImagePosition(const std::wstring& pos);
	void HtmlBackgroundImageRepeat(const std::wstring& repeat);

	// header
	void H1Color(const std::wstring& color);
	void H1Size(const std::wstring& size);
	void H1Font(const std::wstring& font);
	void H1Style(const std::wstring& style);
	void H1Weight(const std::wstring& weight);
	void H1Underline(const std::wstring& ul);
	void H1Strike(const std::wstring& st);

	// anchor
	void AColor(const std::wstring& color);
	void ASize(const std::wstring& size);
	void AFont(const std::wstring& font);
	void AStyle(const std::wstring& style);
	void AWeight(const std::wstring& weight);
	void AUnderline(const std::wstring& ul);
	void AStrike(const std::wstring& st);


	void ImagesPerPage(const std::wstring& mipp);

	void InsertInputPath(const std::wstring& i_path);

	void UserCSS(const std::wstring& csspath);

private:
//functions
	void BuildSwitchTable();
	void ParseCommandLine();
	void Defaults();
	void SetNonEssentialParameters();
	void ValidateEssentialParameters();

	void InputStatus(bool status);
	void OutputStatus(bool status);

	bool IsParamUnary(std::wstring param);
	bool IsValidSwitch(std::wstring param);

	const std::wstring& NotPathCreate_Bool_String() const;
	const std::wstring& DefaultCSS_Bool_String() const;
	const std::wstring& InternalCSS_Bool_String() const;
	const std::wstring& NoHTML_Bool_String() const;
	const std::wstring& OnlyHTML_Bool_String() const;

// data
	std::wstring application_name;
	LPWSTR* arguments;
	int arg_count;

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

	size_t thumb_height;
	size_t thumb_width;

	size_t pics_per_page;
	size_t number_of_pages;
	
	unsigned int banner_height;

	float wm_alpha;
	float wm_scale;

	position pos;

	std::wstring input_path;
	std::wstring output_path;
	std::wstring project_name;
	std::wstring page_title;
	std::wstring height_string;
	std::wstring width_string;
	std::wstring nohtml_string;
	std::wstring onlyhtml_string;
	std::wstring water_mark;
	std::wstring wm_pos;
	std::wstring banner;
	std::wstring usercss;
	
	// CSS stuff
	std::wstring html_color;
	std::wstring html_background_color;
	std::wstring html_background_image;
	std::wstring html_background_image_position;
	std::wstring html_background_image_repeat;

	// header
	std::wstring h1color;
	std::wstring h1size;
	std::wstring h1font;
	std::wstring h1style;
	std::wstring h1weight;
	std::wstring h1underline;
	std::wstring h1strike;

	// anchor
	std::wstring acolor;
	std::wstring asize;
	std::wstring afont;
	std::wstring astyle;
	std::wstring aweight;
	std::wstring aunderline;
	std::wstring astrike;

	std::vector <std::wstring> cmd_params;
	std::vector <std::wstring> switch_table;
	std::map <std::wstring,std::wstring> user_params;

	std::list<std::wstring> input_paths;
};



class help  
{
public:
	help() {} ;
	virtual ~help() {} ;

};

// constant strings
	const std::wstring empty = L"";
	const std::wstring b_true = L"true";
	const std::wstring b_false = L"false";
	const std::wstring switch_i = L"-i";
	const std::wstring switch_o = L"-o";
	const std::wstring switch_p = L"-p";
	const std::wstring switch_t = L"-t";
	const std::wstring switch_h = L"-h";
	const std::wstring switch_w = L"-w";
	const std::wstring switch_ic = L"-ic";
	const std::wstring switch_css = L"-css";
	const std::wstring switch_nc = L"-nc";
	const std::wstring switch_nohtml = L"-nohtml";
	const std::wstring switch_onlyhtml = L"-onlyhtml";
	const std::wstring switch_query = L"-?";
	const std::wstring switch_nocaption = L"-nocaption";
	const std::wstring switch_notitle = L"-notitle";

	const std::wstring switch_watermark = L"-watermark";
	const std::wstring switch_wmpos = L"-wmpos";
	const std::wstring switch_wmalpha = L"-wmalpha";
	const std::wstring switch_wmscale = L"-wmscale";

	const std::wstring switch_hcolor = L"-hcolor";
	const std::wstring switch_hbcolor = L"-hbcolor";
	const std::wstring switch_hbimage = L"-hbimage";
	const std::wstring switch_hbimpos = L"-hbimpos";
	const std::wstring switch_hbimrep = L"-hbimrep";

	const std::wstring switch_banner = L"-banner";
	const std::wstring switch_mipp = L"-mipp";
	const std::wstring switch_recurse = L"-s";

	const std::wstring switch_h1color = L"-h1color";
	const std::wstring switch_h1size = L"-h1size";
	const std::wstring switch_h1font = L"-h1font";
	const std::wstring switch_h1style = L"-h1style";
	const std::wstring switch_h1weight = L"-h1weight";
	const std::wstring switch_h1underline = L"-h1underline";
	const std::wstring switch_h1strike = L"-h1strike";

	const std::wstring switch_acolor = L"-acolor";
	const std::wstring switch_asize = L"-asize";
	const std::wstring switch_afont = L"-afont";
	const std::wstring switch_astyle = L"-astyle";
	const std::wstring switch_aweight = L"-aweight";
	const std::wstring switch_aunderline = L"-aunderline";
	const std::wstring switch_astrike = L"-astrike";

	const std::wstring switch_verbose = L"-verbose";
	const std::wstring switch_diagnostic = L"-diagnostic";
	/*
	const std::wstring switch_ = L"";
*/



#endif // !defined(AFX_COMMANDLINE_H__00A40212_F8FC_46F6_A41E_6BC5E203D777__INCLUDED_)
