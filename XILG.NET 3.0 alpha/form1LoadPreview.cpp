#include "stdafx.h"
#include "form1.h"


namespace XILGNET30alpha {


System::Void Form1::LoadPreview()
{
	if (caption_enabled)
	{
		caption1 = L"\n\t\t\t\t\t<p>thumb 1</p>";
		caption2 = L"\n\t\t\t\t\t<p>thumb 2</p>";
		caption3 = L"\n\t\t\t\t\t<p>thumb 3</p>";
		caption4 = L"\n\t\t\t\t\t<p>thumb 4</p>";
		caption5 = L"\n\t\t\t\t\t<p>thumb 5</p>";
		caption6 = L"\n\t\t\t\t\t<p>thumb 6</p>";
	}
	else
	{
		caption1 = String::Empty;
		caption2 = String::Empty;
		caption3 = String::Empty;
		caption4 = String::Empty;
		caption5 = String::Empty;
		caption6 = String::Empty;
	}
	if (header_enabled)
	{
		page_title_2 = page_title;
	}
	else
	{
		page_title_2 = String::Empty;
	}

	newpage = String::Empty;
	newpage +=
	L"<?xml version=\"1.0\" encoding=\"UTF-16\"?>\n"
	L"<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n"
	L"<html lang=\"en-GB\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:d=\"http://dvd-database\" xmlns=\"http://www.w3.org/1999/xhtml\">\n"
	L"\n\t<head>"
	L"\n\t\t<meta name=\"generator\" content=\"XILG 3.00 by Graeme P. Bell\" />"
	L"\n\t\t<title>" 
	+ project + 
	L"</title>"
	L"\n\t\t<style type=\"text/css\">"
	
	L"\n\t\t\thtml { color:"
	+ body_font_color +
	L"; background-color:" 
	+ body_color + 
	L"; margin-right:5%; " 
	
	+ image_background_settings +

	L"; font-family:" 
	+ body_font + 
	L"; font-weight:" 
	+ body_font_weight + 
	L"; font-style:"
	+ body_font_style + 
	L"; font-size:"
	+ body_font_size +
	L"; }"+

	L"\n\t\t\tdiv.banner { font-size:1pt; background-image:url("
	+ image_banner +
	L"); background-repeat:no-repeat; background-position:center; " 
	+ image_banner_settings +
	L"; }"+


	L"\n\t\t\th1 { text-align:center; color:" 
	+ header_font_color + 
	L"; font-family:" 
	+ header_font + 
	L"; font-weight:" 
	+ header_font_weight + 
	L"; font-style:"
	+ header_font_style + 
	L"; font-size:"
	+ header_font_size +
	L""
	+ h_text_decoration +
	L"; }"+

	L"\n\t\t\th2 { text-align:center; color:" 
	+ header_font_color + 
	L"; font-family:" 
	+ header_font + 
	L"; }"+
	
	L"\n\t\t\tp { text-align:center; color:" 
	+ body_font_color + 
	L"; font-family:" 
	+ body_font + 
	L""
	+ b_text_decoration +
	L"; }"

	L"\n\t\t\tp.boilerplate { font-size:xx-small; color:gray; }"
	L"\n\t\t\tdiv.float { float:left; margin:5px; width:150px; height:200px; }"
	L"\n\t\t\tdiv.container { text-align:center; margin-left:15%; margin-right:5%; }"
	L"\n\t\t\tdiv.spacer { clear:both; }"
	L"\n\t\t\ta { text-decoration:none; font-size:medium; font-weight:normal; font-style:normal; font-family:serif; }"
	L"\n\t\t\ta:link { color:blue; }"
	L"\n\t\t\ta:active { color:red; }"
	L"\n\t\t\ta:visited { color:purple; }"
	L"\n\t\t\ta:hover { color:red; }"
	L"\n\t\t\t.center { text-align:center; }"
	L"\n\t\t\t.link { width:50%; margin-left:25%; margin-right:25%; }"
	L"\n\t\t</style>"
	L"\n\t</head>"
	L"\n\t<body>" 
	
	+ image_banner_div +

	L"\n\t\t<h1>" 
	+ page_title_2 +
	L"</h1>\n\t\t<br/>" 
	L"\n\t\t<div class=\"center\">\n\t\t\t<div class=\"container\">"
	
	L"\n\t\t\t\t<div class=\"float\">"
	L"\n\t\t\t\t\t<img src="
	+ image_thumb1 +
	L" alt=\"thumb 1\" />" 
	+ caption1 +
	L"\n\t\t\t\t</div>"

	L"\n\t\t\t\t<div class=\"float\">"
	L"\n\t\t\t\t\t<img src="
	+ image_thumb2 +
	L" alt=\"thumb 2\" />" 
	+ caption2 +
	L"\n\t\t\t\t</div>"
	
	L"\n\t\t\t\t<div class=\"float\">"
	L"\n\t\t\t\t\t<img src="
	+ image_thumb3 +
	L" alt=\"thumb 3\" />"
	+ caption3 +
	L"\n\t\t\t\t</div>"
			
	L"\n\t\t\t\t<div class=\"float\">"
	L"\n\t\t\t\t\t<img src="
	+ image_thumb4 +
	L" alt=\"thumb 4\" />"
	+ caption4 +
	L"\n\t\t\t\t</div>"
	
	L"\n\t\t\t\t<div class=\"float\">"
	L"\n\t\t\t\t\t<img src="
	+ image_thumb5 +
	L" alt=\"thumb 5\" />"
	+ caption5 +
	L"\n\t\t\t\t</div>"
	
	L"\n\t\t\t\t<div class=\"float\">"
	L"\n\t\t\t\t\t<img src="
	+ image_thumb6 +
	L" alt=\"thumb 6\" />"
	+ caption6 +
	L"\n\t\t\t\t</div>"
	
	L"\n\t\t\t</div>\n\t\t</div>"
	L"\n\t</body>\n</html>";

	webBrowser1->DocumentText = newpage;
}

} // END OF NAMESPACE