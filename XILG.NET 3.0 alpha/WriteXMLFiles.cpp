#include "stdafx.h"
//#pragma warning(disable:4786)
#include "WriteXMLFile.h"


//////////////////////////////////
// CLASS basic_xmlfile
//////////////////////////////////

basic_xmlfile::basic_xmlfile() 
{
	test_hr(doc_ptr.CreateInstance(L"Msxml2.DOMDocument"));
}


basic_xmlfile::~basic_xmlfile() {}


//////////////////// carriage return and indent ///////////////
void basic_xmlfile::cr_indent(int il, MSXML2::IXMLDOMElementPtr ePtr) 
{
	MSXML2::IXMLDOMTextPtr textPtr;
	std::wstring level = L"\n";
	
	for (int i = 0; i < il; i++)
	{
		level += L"\t";
	}
	
	textPtr = doc_ptr->createTextNode(level.c_str());
	ePtr->appendChild(textPtr);
}

//////////////////// save the file ////////////////////////////
bool basic_xmlfile::save(const std::wstring& filename, const CommandLine& cl)
{
	if (cl.PathCreate())
	{
		LPCTSTR dir_name = cl.OutputPath().c_str();
		
		if (!PathIsDirectory(dir_name))
		{		
			int success = CreateDirectory(dir_name,NULL);
		
			if (!success)
			{
				std::wstring xilgerr = L"Failed to create new folder ";
				xilgerr += dir_name;
				xilgerr += L" for ";
				xilgerr += filename;
				std::wstring xilgerr_line = stringer(__LINE__);
				std::wstring xilgerr_file = widen(__FILE__);
				throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
			}
		}
	}

	doc_ptr->save(filename.c_str());
	return 0;
}


//////////////////// create an XML PI //////////////////////////
void basic_xmlfile::write_processing_instruction(const std::wstring& s1, const std::wstring& s2, bool initial)
{
	MSXML2::IXMLDOMProcessingInstructionPtr pi = NULL;
	const _variant_t refChild;
	BSTR b1 = SysAllocString(s1.data());
	BSTR b2 = SysAllocString(s2.data());

	try {

		pi = doc_ptr->createProcessingInstruction(b1, b2);

		SysFreeString(b1);
		SysFreeString(b2);

		if (!initial)
			doc_ptr->appendChild(pi);
		else
			doc_ptr->insertBefore(pi, &refChild);

	}
	catch (...)
	{
		if (b1) SysFreeString(b1);
		if (b2) SysFreeString(b2);
		throw;
	}
}

/////////////////// standard XML Declaration
void basic_xmlfile::xml_declaration()
{
	write_processing_instruction(L"xml", L"version='1.0' ",true);
}


////////////////// XML IMAGE LIST DATABASE FILE /////////////////
/////////////////////////////////////////////////////////////////
// CLASS xml_image_list
/////////////////////////////////////////////////////////////////
xml_image_list::xml_image_list() {}
xml_image_list::~xml_image_list() {}

void xml_image_list::xslinclude(const std::wstring& xsl_filename)
{
	std::wstring second_arg = L"type=\"text/xsl\" href=\"" + xsl_filename + L"\"";
	BSTR temp = const_cast<BSTR>(second_arg.c_str());
	basic_xmlfile::write_processing_instruction(L"xml-stylesheet",temp);
}

void xml_image_list::xslinclude(MSXML2::IXMLDOMDocumentPtr doc_ptr, const std::wstring& xsl_filename)
{
	std::wstring first_arg = L"xml-stylesheet";
	std::wstring second_arg = L"type=\"text/xsl\" href=\"" + xsl_filename + L"\"";
	BSTR t2 = SysAllocString(second_arg.c_str());
	BSTR t1 = SysAllocString(first_arg.c_str());
	try {
		write_processing_instruction(doc_ptr, t1,t2,true);
	}
	catch (...)
	{
		SysFreeString(t1);
		SysFreeString(t2);
		throw;
	}
	SysFreeString(t1);
	SysFreeString(t2);
}

bool xml_image_list::build(const CommandLine& cl, const ImageFileList& ifl)
{
	size_t ipp = cl.ImagesPerPage();
	if (ipp)
	{
		buildrange(cl,ifl,0,ipp);
	}
	else
	{
		buildone(cl,ifl);
	}
	return true;
}

bool xml_image_list::buildone(const CommandLine& cl, const ImageFileList& ifl)
{
	std::wcout << L"\nCreating the XML file";
	MSXML2::IXMLDOMElementPtr image_list_ptr;
	MSXML2::IXMLDOMElementPtr image_ptr;
	MSXML2::IXMLDOMTextPtr text_ptr;

	project_name = cl.ProjectName();
	path xsl_filename = project_name.wstring() + L"_xsl.xml";
	path xml_filename = cl.OutputPath() / project_name.replace_extension(L".xml");

	basic_xmlfile::xml_declaration();
	xslinclude(xsl_filename);

	image_list_ptr = doc_ptr->createElement(L"image-list");
	image_list_ptr->setAttribute(L"title",cl.PageTitle().c_str());
	image_list_ptr->setAttribute(L"project",project_name.c_str());
	doc_ptr->appendChild(image_list_ptr);

	std::list <ImageNames> i_names = ifl.RetrieveImageNames();

	std::list<ImageNames>::iterator first = i_names.begin();
	std::list<ImageNames>::size_type max_items = i_names.size();

	for (auto name : i_names)
	{
		std::wstring image_name;
		std::wstring thumb_name;
		std::wstring display_name;

		basic_xmlfile::cr_indent(1,image_list_ptr);
		image_ptr = doc_ptr->createElement(L"image");

		image_name = L"images" / name.GetLargeImageName();
		
		image_ptr->setAttribute(L"image-name",image_name.c_str());
		
		thumb_name = L"thumbs" / name.GetThumbnailImageName();
		image_ptr->setAttribute(L"thumb-name",thumb_name.c_str());

		display_name = name.GetOriginalName();
		image_ptr->setAttribute(L"display-name",display_name.c_str());

		image_list_ptr->appendChild(image_ptr);
	}
	basic_xmlfile::cr_indent(0, image_list_ptr);

	basic_xmlfile::save(xml_filename,cl);

	return true;
}


bool xml_image_list::buildrange(const CommandLine &cl, const ImageFileList &ifl, const size_t start, const size_t how_many)
{
	UNREFERENCED_PARAMETER(start);

	std::wcout << L"\nCreating the XML files";
	size_t num_pages = 1;
	project_name = cl.ProjectName();
	std::wstring xsl_filename = project_name.wstring() + L"_xsl.xml";

	std::list<ImageNames> i_names = ifl.RetrieveImageNames();
	std::list<ImageNames>::size_type total_items = i_names.size();
	std::list<ImageNames>::iterator i_names_iter1 = i_names.begin();
	std::list<ImageNames>::iterator i_names_iter2 = i_names.begin();


	num_pages = (total_items/how_many);
	if (total_items % how_many) num_pages++;

	const_cast<CommandLine&>(cl).NumberOfPages(num_pages);
	std::vector<std::list<ImageNames>> vector_of_imagelists(num_pages);
	std::vector<MSXML2::IXMLDOMDocumentPtr> multidocs(num_pages);
	
	unsigned int x = 0;
	for (unsigned int y = 0; y < num_pages; y++)
	{
		for (unsigned int z = 0; z < how_many; z++) 
		{
			if (x < total_items)
			{
				i_names_iter2++;
				x++;
			}
		}
		vector_of_imagelists[y].assign(i_names_iter1,i_names_iter2);
		i_names_iter1 = i_names_iter2;
		test_hr(multidocs[y].CreateInstance(L"Msxml2.DOMDocument"));
	}
	
	for(unsigned int i = 0; i < num_pages; i++)
	{
		MSXML2::IXMLDOMElementPtr image_list_ptr;
		MSXML2::IXMLDOMElementPtr image_ptr;
		MSXML2::IXMLDOMTextPtr text_ptr;

		xml_declaration(multidocs[i]);
		xslinclude(multidocs[i],xsl_filename);

		image_list_ptr = multidocs[i]->createElement(L"image-list");

		ImageListAttributes(multidocs[i], cl, image_list_ptr,i, num_pages);

		std::list<ImageNames>::iterator voi = vector_of_imagelists[i].begin();
		size_t size = vector_of_imagelists[i].size();

		for (std::list<ImageNames>::size_type count = 0; count < size; count++)
		{
				std::wstring image_name;
				std::wstring thumb_name;
				std::wstring display_name;

			image_name = L"images" / voi->GetLargeImageName();
			thumb_name = L"thumbs" / voi->GetThumbnailImageName();
			display_name = voi->GetOriginalName();

			cr_indent(multidocs[i],1,image_list_ptr);
				image_ptr = doc_ptr->createElement(L"image");

			image_ptr->setAttribute(L"image-name",image_name.c_str());
			image_ptr->setAttribute(L"thumb-name",thumb_name.c_str());
			image_ptr->setAttribute(L"display-name",display_name.c_str());

				image_list_ptr->appendChild(image_ptr);

			voi++;
			}
		cr_indent(multidocs[i],0, image_list_ptr);	

		std::wstring page = std::format(L"{}", i);
		std::wstring xml_filename = cl.OutputPath() / (project_name.wstring() + L"-" + page + L".xml"); // plus a numeric indicator of file number!!!

		save(multidocs[i],xml_filename,cl);
	}
	return true;
}

void xml_image_list::ImageListAttributes(MSXML2::IXMLDOMDocumentPtr doc_ptr, 
										 const CommandLine& cl, 
										 MSXML2::IXMLDOMElementPtr ilp, 
										 const size_t index,
										 const size_t max_pages)
{
	std::wstring att1;
	std::wstring att2;
	std::wstring att3;
	std::wstring att_temp;
	std::wstring ext;

	size_t  previous = index -1;
	if (previous <= 0) previous = max_pages-1;
	size_t  nex = index + 1;
	if (nex >= max_pages) nex = 1;
	size_t  current = index ;

	std::wstring pnum = std::format(L"{}", current);

	att_temp = L"";
	att1 = att_temp + pnum;

	if (cl.NoHTML())
		ext = L".xml";
	else
		ext = L".html";

	std::wstring prev = std::format(L"{}", previous);

	att2 = cl.ProjectName().wstring() + L"-" + prev + ext;

	std::wstring next = std::format(L"{}", nex);

	att3 = cl.ProjectName().wstring() + L"-" + next + ext;

	ilp->setAttribute(L"title",cl.PageTitle().c_str());
	ilp->setAttribute(L"project",project_name.c_str());
	ilp->setAttribute(L"page", att1.c_str());
	ilp->setAttribute(L"prev",att2.c_str());
	ilp->setAttribute(L"next",att3.c_str());

	doc_ptr->appendChild(ilp);
}


//////////////////// carriage return and indent ///////////////
void xml_image_list::cr_indent(MSXML2::IXMLDOMDocumentPtr doc_ptr, int il, MSXML2::IXMLDOMElementPtr ePtr) 
{
	MSXML2::IXMLDOMTextPtr textPtr;
	std::wstring level = L"\n";
	
	for (size_t  i = 0; i < il; i++)
	{
		level += L"\t";
	}
	
	textPtr = doc_ptr->createTextNode(level.c_str());
	ePtr->appendChild(textPtr);
}

//////////////////// save the file ////////////////////////////
bool xml_image_list::save(MSXML2::IXMLDOMDocumentPtr doc_ptr, const std::wstring& filename, const CommandLine& cl)
{
	if (cl.PathCreate())
	{
		LPCTSTR dir_name = cl.OutputPath().c_str();
		
		if (!PathIsDirectory(dir_name))
		{		
			int success = CreateDirectory(dir_name,NULL);
		
			if (!success)
			{
				std::wstring xilgerr;
				xilgerr = L"Failed to create new folder ";
				xilgerr += dir_name;
				xilgerr += L" for ";
				xilgerr += filename;
				std::wstring xilgerr_line = stringer(__LINE__);
				std::wstring xilgerr_file = widen(__FILE__);
				throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
			}
		}
	}

	doc_ptr->save(filename.c_str());
	return 0;
}


//////////////////// create an XML PI //////////////////////////
void xml_image_list::write_processing_instruction(MSXML2::IXMLDOMDocumentPtr doc_ptr, BSTR s1, BSTR s2, bool initial)
{
	MSXML2::IXMLDOMProcessingInstructionPtr pi = NULL;
	const _variant_t refChild;

	pi = doc_ptr->createProcessingInstruction(s1,s2);
	
	if (!initial)
		doc_ptr->appendChild(pi);
	else
		doc_ptr->insertBefore(pi,&refChild);
}

/////////////////// standard XML Declaration
void xml_image_list::xml_declaration(MSXML2::IXMLDOMDocumentPtr doc_ptr)
{
	const std::wstring xml = L"xml";
	const std::wstring ver = L"version='1.0' encoding='ISO-8859-1' ";

	BSTR s1 = SysAllocString(xml.c_str());
	BSTR s2 = SysAllocString(ver.c_str());

	try {
		write_processing_instruction(doc_ptr, s1, s2, true);
	}
	catch (...)
	{
		SysFreeString(s1);
		SysFreeString(s2);
		throw;
	}
	SysFreeString(s1);
	SysFreeString(s2);
}


////////////////////////////////////////////////////////////////
/////////////////// XSL TEMPLATE ///////////////////////////////
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
// XSL IMAGE LIST FILE
///////////////////////////////////////////////////////////////

xsl_image_list::xsl_image_list() {}
xsl_image_list::~xsl_image_list() {}

bool xsl_image_list::build(const CommandLine& cl, const ImageFileList& ifl)
{
	UNREFERENCED_PARAMETER(ifl);

	std::wcout << L"\nCreating the XSL file";
	project_name = cl.ProjectName();
	internal_css = cl.InternalCSS();
	no_caption = cl.NoCaption();
	banner = cl.BannerImage();
	images_per_page = cl.ImagesPerPage();

	MSXML2::IXMLDOMElementPtr style_sheetPtr = 0;
	xml_declaration();
	style_sheetPtr = build_preamble();

	cr_indent(0,style_sheetPtr);
	cr_indent(0,style_sheetPtr);

	build_root_template(style_sheetPtr);

	cr_indent(0,style_sheetPtr);
	cr_indent(0,style_sheetPtr);

	build_image_template(style_sheetPtr);

	cr_indent(0,style_sheetPtr);
	cr_indent(0,style_sheetPtr);
	
	std::wstring xsl_filename = cl.OutputPath() / (cl.ProjectName().wstring() + L"_xsl.xml");
	save(xsl_filename,cl);

	return true;
}


MSXML2::IXMLDOMElementPtr xsl_image_list::build_preamble()
{
	std::wstring pn = project_name;
	std::wstring css_doc_att = L"document(" + pn + L".css)"; 

	MSXML2::IXMLDOMElementPtr style_sheetPtr;
	MSXML2::IXMLDOMElementPtr output_ptr;
	MSXML2::IXMLDOMElementPtr variable_ptr;

	style_sheetPtr = doc_ptr->createElement(L"xsl:stylesheet");
	style_sheetPtr->setAttribute(L"xmlns:xsl",L"http://www.w3.org/1999/XSL/Transform");
	style_sheetPtr->setAttribute(L"version",L"1.0");
	style_sheetPtr->setAttribute(L"xmlns",L"http://www.w3.org/1999/xhtml");
	doc_ptr->appendChild(style_sheetPtr);

	cr_indent(0,style_sheetPtr);
	output_ptr = doc_ptr->createElement(L"xsl:output");
	output_ptr->setAttribute(L"method",L"xml");
	output_ptr->setAttribute(L"version",L"1.0");
	output_ptr->setAttribute(L"encoding",L"UTF-16");
	output_ptr->setAttribute(L"doctype-public",L"-//W3C//DTD XHTML 1.0 Strict//EN");
	output_ptr->setAttribute(L"doctype-system",L"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd");
	output_ptr->setAttribute(L"indent",L"yes");
	style_sheetPtr->appendChild(output_ptr);

	if (internal_css)
	{

		cr_indent(0,style_sheetPtr);
		cr_indent(0,style_sheetPtr);
		
		variable_ptr = doc_ptr->createElement(L"xsl:variable");
		variable_ptr->setAttribute(L"name",L"stylesheet");
		variable_ptr->setAttribute(L"select",css_doc_att.c_str());
		style_sheetPtr->appendChild(variable_ptr);
	}

	return style_sheetPtr;
}


void xsl_image_list::build_root_template(MSXML2::IXMLDOMElementPtr style_sheetPtr)
{
	MSXML2::IXMLDOMElementPtr template_ptr;
	MSXML2::IXMLDOMElementPtr html_ptr;

	template_ptr = doc_ptr->createElement(L"xsl:template");
	template_ptr->setAttribute(L"match",L"/");
	style_sheetPtr->appendChild(template_ptr);

	cr_indent(1,template_ptr);

	html_ptr = doc_ptr->createElement(L"html");

	html_ptr->setAttribute(L"lang",L"en-GB");
	template_ptr->appendChild(html_ptr);

	cr_indent(2,html_ptr);

	build_html_head(html_ptr);

	cr_indent(2,html_ptr);

	build_html_body(html_ptr);
	
	cr_indent(1,html_ptr);
	cr_indent(0,template_ptr);
}


void xsl_image_list::build_html_head(MSXML2::IXMLDOMElementPtr html_ptr)
{
	MSXML2::IXMLDOMElementPtr head_ptr;
	MSXML2::IXMLDOMElementPtr e4ptr;
	MSXML2::IXMLDOMElementPtr e5ptr;

	head_ptr = doc_ptr->createElement(L"head");
	html_ptr->appendChild(head_ptr);
	
	cr_indent(3,head_ptr);
	
	e4ptr = doc_ptr->createElement(L"meta");
	e4ptr->setAttribute(L"name",L"generator");
	e4ptr->setAttribute(L"content",L"XILG 3.00 by Graeme P. Bell");
	head_ptr->appendChild(e4ptr);

	cr_indent(3,head_ptr);
	
	e4ptr = doc_ptr->createElement(L"title");
	head_ptr->appendChild(e4ptr);

	cr_indent(4,e4ptr);
	
	e5ptr = doc_ptr->createElement(L"xsl:value-of");
	e5ptr->setAttribute(L"select",L"//@title");
	e4ptr->appendChild(e5ptr);
	
	cr_indent(3,e4ptr);
	cr_indent(3,head_ptr);

	css_declaration(head_ptr);

	cr_indent(2,head_ptr);
}

void xsl_image_list::css_declaration(MSXML2::IXMLDOMElementPtr head_ptr)
{
	MSXML2::IXMLDOMElementPtr e4ptr;
	MSXML2::IXMLDOMElementPtr e5ptr;
	MSXML2::IXMLDOMTextPtr text_ptr;

	if (internal_css)
	{
		e4ptr = doc_ptr->createElement(L"style");
		e4ptr->setAttribute(L"type",L"text/css");
		head_ptr->appendChild(e4ptr);

		cr_indent(4,e4ptr);

		e5ptr = doc_ptr->createElement(L"xsl:value-of");
		e5ptr->setAttribute(L"select",L"$stylesheet");
		e4ptr->appendChild(e5ptr);

		cr_indent(3,e4ptr);
	}
	else
	{
		std::wstring import = L"@import url('" + project_name.wstring() + L".css');";
		
		e4ptr = doc_ptr->createElement(L"style");
		e4ptr->setAttribute(L"type",L"text/css");
		head_ptr->appendChild(e4ptr);

		cr_indent(4,e4ptr);

		e5ptr = doc_ptr->createElement(L"xsl:text");
		e4ptr->appendChild(e5ptr);
		text_ptr  = doc_ptr->createTextNode(import.c_str());
		e5ptr->appendChild(text_ptr);

		cr_indent(3,e4ptr);
	}
}


void xsl_image_list::build_html_body(MSXML2::IXMLDOMElementPtr html_ptr)
{
	MSXML2::IXMLDOMElementPtr body_ptr;
	MSXML2::IXMLDOMElementPtr e4ptr;

	body_ptr = doc_ptr->createElement(L"body");
	html_ptr->appendChild(body_ptr);

	cr_indent(3,body_ptr);

	set_html_title(body_ptr);

	cr_indent(3,body_ptr);

	e4ptr = doc_ptr->createElement(L"div");
	body_ptr->appendChild(e4ptr);

	cr_indent(4,e4ptr);

	applytemplates(e4ptr);

	cr_indent(3,e4ptr);
	cr_indent(3,body_ptr);

	e4ptr = doc_ptr->createElement(L"div");
	body_ptr->appendChild(e4ptr);

	cr_indent(4,e4ptr);

	boilerplate(e4ptr);

	cr_indent(3,e4ptr);
	cr_indent(2,body_ptr);

}


void xsl_image_list::set_html_title(MSXML2::IXMLDOMElementPtr body_ptr)
{
	MSXML2::IXMLDOMElementPtr e4ptr;
	MSXML2::IXMLDOMElementPtr e5ptr;

	if (banner != empty)
	{
		MSXML2::IXMLDOMTextPtr text_ptr;

		e4ptr = doc_ptr->createElement(L"div");
		e4ptr->setAttribute(L"class",L"banner");
		body_ptr->appendChild(e4ptr);
		text_ptr = doc_ptr->createTextNode(L".");
		e4ptr->appendChild(text_ptr);
		cr_indent(3,body_ptr);
	}

	e4ptr = doc_ptr->createElement(L"h1");
	body_ptr->appendChild(e4ptr);

	cr_indent(4,e4ptr);

	e5ptr = doc_ptr->createElement(L"xsl:value-of");
	e5ptr->setAttribute(L"select",L"//@title");
	e4ptr->appendChild(e5ptr);

	if (images_per_page)
	{
		cr_indent(3,body_ptr);
		cr_indent(3,e4ptr);

		e4ptr = doc_ptr->createElement(L"h2");
		e4ptr->setAttribute(L"class",L"center");
		body_ptr->appendChild(e4ptr);
		
		cr_indent(4,e4ptr);

		e5ptr = doc_ptr->createElement(L"xsl:value-of");
		e5ptr->setAttribute(L"select",L"//@page");
		e4ptr->appendChild(e5ptr);
	}
	cr_indent(3,e4ptr);
}



void xsl_image_list::applytemplates(MSXML2::IXMLDOMElementPtr e4ptr)
{
	MSXML2::IXMLDOMElementPtr e5ptr;
	MSXML2::IXMLDOMElementPtr e6ptr;
	MSXML2::IXMLDOMTextPtr text_ptr;

	e5ptr = doc_ptr->createElement(L"xsl:attribute");
	e5ptr->setAttribute(L"name",L"class");
	e4ptr->appendChild(e5ptr);


	cr_indent(5,e5ptr);
	e6ptr = doc_ptr->createElement(L"xsl:text");
	e5ptr->appendChild(e6ptr);
	text_ptr = doc_ptr->createTextNode(L"container");
	e6ptr->appendChild(text_ptr);
	
	cr_indent(4,e5ptr);
	cr_indent(4,e4ptr);

	e5ptr = doc_ptr->createElement(L"xsl:apply-templates");
	e5ptr->setAttribute(L"select",L"/image-list/image");
	e4ptr->appendChild(e5ptr);
}

void xsl_image_list::insert_links(MSXML2::IXMLDOMElementPtr e4ptr)
{
	MSXML2::IXMLDOMElementPtr e5ptr;
	MSXML2::IXMLDOMElementPtr e6ptr;
	MSXML2::IXMLDOMElementPtr e7ptr;
	MSXML2::IXMLDOMElementPtr e8ptr;
	MSXML2::IXMLDOMElementPtr e9ptr;
	MSXML2::IXMLDOMElementPtr e10ptr;
	MSXML2::IXMLDOMTextPtr text_ptr;

//	cr_indent(4,e4ptr);

	e5ptr = doc_ptr->createElement(L"table");
	e5ptr->setAttribute(L"class",L"link");
	e4ptr->appendChild(e5ptr);
	e5ptr->setAttribute(L"summary",L"links");
	e4ptr->appendChild(e5ptr);

	cr_indent(5,e5ptr);
	
	e6ptr = doc_ptr->createElement(L"tr");
	e5ptr->appendChild(e6ptr);

	cr_indent(6,e6ptr);

	e7ptr = doc_ptr->createElement(L"td");
	e6ptr->appendChild(e7ptr);

	cr_indent(7,e7ptr);
//////////////////////////////////////////////
	e8ptr = doc_ptr->createElement(L"a");
	e7ptr->appendChild(e8ptr);

	cr_indent(8,e8ptr);

	e9ptr = doc_ptr->createElement(L"xsl:attribute");
	e9ptr->setAttribute(L"name",L"href");
	e8ptr->appendChild(e9ptr);

	cr_indent(9,e9ptr);

	e10ptr = doc_ptr->createElement(L"xsl:value-of");
	e10ptr->setAttribute(L"select",L"//@prev");
	e9ptr->appendChild(e10ptr);

	cr_indent(8,e9ptr);
	cr_indent(8,e8ptr);

	e9ptr = doc_ptr->createElement(L"xsl:text");
	e8ptr->appendChild(e9ptr);
	text_ptr = doc_ptr->createTextNode(L" PREV ");
	e9ptr->appendChild(text_ptr);
	cr_indent(7,e8ptr);

	cr_indent(6,e7ptr);
//////////////////////////////////
	cr_indent(6,e6ptr);

	e7ptr = doc_ptr->createElement(L"td");
	e6ptr->appendChild(e7ptr);

	cr_indent(7,e7ptr);
//////////////////////////////////////////////
	e8ptr = doc_ptr->createElement(L"a");
	e7ptr->appendChild(e8ptr);

	cr_indent(8,e8ptr);

	e9ptr = doc_ptr->createElement(L"xsl:attribute");
	e9ptr->setAttribute(L"name",L"href");
	e8ptr->appendChild(e9ptr);

	cr_indent(9,e9ptr);

	e10ptr = doc_ptr->createElement(L"xsl:value-of");
	e10ptr->setAttribute(L"select",L"//@next");
	e9ptr->appendChild(e10ptr);

	cr_indent(8,e9ptr);
	cr_indent(8,e8ptr);

	e9ptr = doc_ptr->createElement(L"xsl:text");
	e8ptr->appendChild(e9ptr);
	text_ptr = doc_ptr->createTextNode(L" NEXT ");
	e9ptr->appendChild(text_ptr);
	cr_indent(7,e8ptr);

	cr_indent(6,e7ptr);
//////////////////////////////////

//////////////////////////////////
	cr_indent(5,e6ptr);

	cr_indent(4,e5ptr);
	cr_indent(4,e4ptr);
}


void xsl_image_list::boilerplate(MSXML2::IXMLDOMElementPtr e4ptr)
{
	MSXML2::IXMLDOMElementPtr e5ptr;
	MSXML2::IXMLDOMElementPtr e6ptr;
	MSXML2::IXMLDOMElementPtr e7ptr;
	MSXML2::IXMLDOMElementPtr e8ptr;
	MSXML2::IXMLDOMTextPtr text_ptr;

	e5ptr = doc_ptr->createElement(L"xsl:attribute");
	e5ptr->setAttribute(L"name",L"class");
	e4ptr->appendChild(e5ptr);

	cr_indent(5,e5ptr);
	e6ptr = doc_ptr->createElement(L"xsl:text");
	e5ptr->appendChild(e6ptr);
	text_ptr = doc_ptr->createTextNode(L"spacer center");
	e6ptr->appendChild(text_ptr);

	cr_indent(4,e5ptr);
	cr_indent(4,e4ptr);

	if (images_per_page)
		insert_links(e4ptr);

	e5ptr = doc_ptr->createElement(L"hr");
	e4ptr->appendChild(e5ptr);

	cr_indent(4,e4ptr);
	
	e5ptr = doc_ptr->createElement(L"p");
	e5ptr->setAttribute(L"class",L"boilerplate");
	e4ptr->appendChild(e5ptr);

	// Old boilerplate //
	cr_indent(5,e5ptr);
	e6ptr = doc_ptr->createElement(L"xsl:text");
	e5ptr->appendChild(e6ptr);
	text_ptr = doc_ptr->createTextNode(L"Web Page created using XILG: The XML Image List Generator");
	e6ptr->appendChild(text_ptr);
	// Old boilerplate //

	cr_indent(4,e5ptr);
}




void xsl_image_list::format_list_template(MSXML2::IXMLDOMElementPtr e1ptr)
{
	MSXML2::IXMLDOMElementPtr e2ptr;
	MSXML2::IXMLDOMElementPtr e3ptr;
	MSXML2::IXMLDOMElementPtr e4ptr;
	MSXML2::IXMLDOMElementPtr e5ptr;
	MSXML2::IXMLDOMTextPtr text_ptr;

	cr_indent(2,e1ptr);

	e2ptr = doc_ptr->createElement(L"xsl:attribute");
	e2ptr->setAttribute(L"name",L"class");
	e1ptr->appendChild(e2ptr);

	cr_indent(3,e2ptr);

	e3ptr = doc_ptr->createElement(L"xsl:text");
	e2ptr->appendChild(e3ptr);
	text_ptr = doc_ptr->createTextNode(L"float");
	cr_indent(3,e2ptr);
	e3ptr->appendChild(text_ptr);

	cr_indent(2,e1ptr);

	e2ptr = doc_ptr->createElement(L"a");
	e1ptr->appendChild(e2ptr);

	cr_indent(3,e2ptr);

	e3ptr = doc_ptr->createElement(L"xsl:attribute");
	e3ptr->setAttribute(L"name",L"href");
	e2ptr->appendChild(e3ptr);

	cr_indent(4,e3ptr);

	e4ptr = doc_ptr->createElement(L"xsl:value-of");
	e4ptr->setAttribute(L"select",L"@image-name");
	e3ptr->appendChild(e4ptr);

	cr_indent(3,e3ptr);
	cr_indent(3,e2ptr);

	e3ptr = doc_ptr->createElement(L"img");
	e2ptr->appendChild(e3ptr);

	cr_indent(4,e3ptr);

	e4ptr = doc_ptr->createElement(L"xsl:attribute");
	e4ptr->setAttribute(L"name",L"src");
	e3ptr->appendChild(e4ptr);

	cr_indent(5,e4ptr);
	e5ptr = doc_ptr->createElement(L"xsl:value-of");
	e5ptr->setAttribute(L"select",L"@thumb-name");
	e4ptr->appendChild(e5ptr);


	cr_indent(4,e4ptr);

	cr_indent(4,e3ptr);

	e4ptr = doc_ptr->createElement(L"xsl:attribute");
	e4ptr->setAttribute(L"name",L"alt");
	e3ptr->appendChild(e4ptr);

/*	// Add Project Name to Image Name
	cr_indent(5,e4ptr);
	e5ptr = doc_ptr->createElement(L"xsl:value-of");
	e5ptr->setAttribute(L"select",L"//@project");
	e4ptr->appendChild(e5ptr);

	cr_indent(5,e4ptr);

	e5ptr = doc_ptr->createElement(L"xsl:text");
	e4ptr->appendChild(e5ptr);
	text_ptr = doc_ptr->createTextNode(L" ");
	e5ptr->appendChild(text_ptr);
*/

	cr_indent(5,e4ptr);
	e5ptr = doc_ptr->createElement(L"xsl:value-of");
	e5ptr->setAttribute(L"select",L"@display-name");
	e4ptr->appendChild(e5ptr);

	cr_indent(4,e4ptr);
	cr_indent(3,e3ptr);
	cr_indent(2,e2ptr);
}


void xsl_image_list::build_image_template(MSXML2::IXMLDOMElementPtr style_sheetPtr)
{
	MSXML2::IXMLDOMElementPtr template_ptr;
	MSXML2::IXMLDOMElementPtr e1ptr;

	template_ptr = doc_ptr->createElement(L"xsl:template");
	template_ptr->setAttribute(L"match",L"image");
	style_sheetPtr->appendChild(template_ptr);

	cr_indent(1,template_ptr);

	e1ptr = doc_ptr->createElement(L"div");
	template_ptr->appendChild(e1ptr);

	format_list_template(e1ptr);

	cr_indent(2,e1ptr);
	
	ImageCaption(e1ptr);

	cr_indent(1,e1ptr);
	cr_indent(0,template_ptr);
}

void xsl_image_list::ImageCaption(MSXML2::IXMLDOMElementPtr e1ptr)
{
	if (!no_caption)
	{
		MSXML2::IXMLDOMElementPtr e2ptr;
		MSXML2::IXMLDOMElementPtr e3ptr;
		MSXML2::IXMLDOMElementPtr e4ptr;
		MSXML2::IXMLDOMElementPtr e5ptr;

		e2ptr = doc_ptr->createElement(L"p");
		e1ptr->appendChild(e2ptr);

		cr_indent(3,e2ptr);
	
		e3ptr = doc_ptr->createElement(L"a");
		e2ptr->appendChild(e3ptr);

		cr_indent(4,e3ptr);

		e4ptr = doc_ptr->createElement(L"xsl:attribute");
		e4ptr->setAttribute(L"name",L"href");
		e3ptr->appendChild(e4ptr);

		cr_indent(5,e4ptr);


		e5ptr = doc_ptr->createElement(L"xsl:value-of");
		e5ptr->setAttribute(L"select",L"@image-name");
		e4ptr->appendChild(e5ptr);

		cr_indent(4,e4ptr);
		cr_indent(4,e3ptr);

		e4ptr = doc_ptr->createElement(L"xsl:value-of");
		e4ptr->setAttribute(L"select",L"@display-name");
		e3ptr->appendChild(e4ptr);

		cr_indent(3,e3ptr);
		cr_indent(2,e2ptr);
	}
}




//////////////////////////////////////////////////////////////////////
// WebPageBuilder Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


WebPageBuilder::WebPageBuilder() 
{
	test_hr(xml_ptr.CreateInstance(L"Msxml2.DOMDocument"));
	test_hr(xsl_ptr.CreateInstance(L"Msxml2.DOMDocument"));
}

WebPageBuilder::~WebPageBuilder(){}

////////////////////// load the various files ////////////////////////////
// Awful kludge!!!! //
//////////////////////////////////////////////////////////////////////////
//bool basic_xmlfile::load(const CommandLine& cl)
bool WebPageBuilder::load(const CommandLine& cl)
{
	UNREFERENCED_PARAMETER(cl);

	std::wstring xilgerr;

	if(PathFileExists(xml_file.c_str()))
	{
		xml_ptr->load(xml_file.c_str());
	}
	else
	{
		xilgerr = L"Couldn't find file: ";
		xilgerr += xml_file.c_str();
		std::wstring xilgerr_line = stringer(__LINE__);
		std::wstring xilgerr_file = widen(__FILE__);
		throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
	}
	if(PathFileExists(xsl_file.c_str()))
	{
		xsl_ptr->load(xsl_file.c_str());
	}
	else
	{
		xilgerr = L"Couldn't find file: ";
		xilgerr += xsl_file.c_str();
		std::wstring xilgerr_line = stringer(__LINE__);
		std::wstring xilgerr_file = widen(__FILE__);
		throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
	}
	return 0;
}

bool WebPageBuilder::build(const CommandLine& cl, const ImageFileList& ifl)
{
	UNREFERENCED_PARAMETER(ifl);
	
	std::wcout << L"\nCreating your website!\n";
	project_name = cl.OutputPath()/cl.ProjectName();
	xsl_file = project_name.wstring() + L"_xsl.xml";
	css_file = project_name.wstring() + L".css";

	size_t total_pages = cl.NumberOfPages();
	
	for (size_t count = 0; count < total_pages; count++)
	{
		std::wstring page_num = empty;
		if (total_pages > 1)
		{
			std::wstring page = std::format(L"{}", count);
			page_num = L"-";
			page_num += page;
		}
		xml_file = project_name.wstring() + (page_num + L".xml");
		html_file = project_name.wstring() + (page_num + L".html");

		internal_build(cl);
	}
	if (cl.OnlyHTML())
	{
		DeleteFile(xsl_file.c_str());
		if (cl.InternalCSS())
		{
			DeleteFile(css_file.c_str());
		}
	}
	return true;
}

bool WebPageBuilder::internal_build(const CommandLine& cl)
{
	std::wstring xilgerr;

	load(cl);

	wchar_t BOM = 0xFEFF;
	html = BOM;

	try {

	html += xml_ptr->transformNode(xsl_ptr);

	}
	catch (...)
	{
		xilgerr = L"transformNode threw an exception";
		std::wstring xilgerr_line = stringer(__LINE__);
		std::wstring xilgerr_file = widen(__FILE__);
		throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
	}
	save(html_file.c_str(),cl);

	if (cl.OnlyHTML())
	{
		DeleteFile(xml_file.c_str());
	}
	return true;
}


//////////////////// save the file ////////////////////////////
bool WebPageBuilder::save(const std::wstring& filename, const CommandLine& cl)
{
	UNREFERENCED_PARAMETER(cl);	

	HANDLE hFile; 
	std::wstring xilgerr;
 
	hFile = CreateFile(filename.c_str(),GENERIC_WRITE,FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

	if (hFile == INVALID_HANDLE_VALUE) 
	{ 
		xilgerr = L"Could not create file: ";
		xilgerr += filename;
		std::wstring xilgerr_line = stringer(__LINE__);
		std::wstring xilgerr_file = widen(__FILE__);
		throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
	}
	
	DWORD BytesToWrite = static_cast<DWORD>(html.length() * sizeof(wchar_t));
	DWORD BytesWritten;
	
	BOOL success = WriteFile(hFile,html.c_str(),BytesToWrite,&BytesWritten,NULL);

	if (!success)
	{
		DWORD err = GetLastError();
		wchar_t buffer[0x10];
		_itow_s(err,buffer,0x10,10);

		xilgerr = L" WriteFile failed!: ";
		xilgerr += filename;
		xilgerr += L"\nGetLastError returned: ";
		xilgerr += buffer;
		
		CloseHandle(hFile);

		std::wstring xilgerr_line = stringer(__LINE__);
		std::wstring xilgerr_file = widen(__FILE__);
		throw (xilg_error(xilgerr,xilgerr_file,xilgerr_line));
	}

	CloseHandle(hFile);
	
	return true;
}

