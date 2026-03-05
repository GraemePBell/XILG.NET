#if !defined(WRITEXMLFILE__INCLUDED_)
#define WRITEXMLFILE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "stdafx.h"
//#pragma warning(disable:4786)
#ifndef XILG_APP
#include "ThumbNailer.h"
#endif
#include "CommandLine.h"
#include "ImageFileList.h"


#import <msxml6.dll>
using namespace MSXML2;

inline void test_hr ( HRESULT _hr ) { if FAILED(_hr) throw(_hr); }


/////////////////////////////////////////////////////////////////////////////
class basic_xmlfile
{
public:
	basic_xmlfile();
	virtual ~basic_xmlfile();
	
	virtual bool build(const CommandLine& cl, const ImageFileList& ifl) = 0;
protected:
// functions
	virtual bool save(const std::wstring& filename, const CommandLine& cl);
	void xml_declaration();
	void write_processing_instruction(const std::wstring& s1, const std::wstring& s2, bool initial=false);
	void cr_indent(int il,MSXML2::IXMLDOMElementPtr ePtr);
//	data
	MSXML2::IXMLDOMDocumentPtr doc_ptr;
	std::wstring project_name;
private:
};
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
class xml_image_list : public basic_xmlfile
{
public:
	xml_image_list();
	virtual ~xml_image_list();

	virtual bool build(const CommandLine& cl, const ImageFileList& ifl);
	virtual bool buildrange(const CommandLine& cl, const ImageFileList& ifl, const unsigned int start, const unsigned int how_many);
	virtual bool buildone(const CommandLine& cl, const ImageFileList& ifl);
private:
	void xslinclude(const std::wstring& xsl_filename);
	void xslinclude(MSXML2::IXMLDOMDocumentPtr doc_ptr, const std::wstring& xsl_filename);
	void cr_indent(MSXML2::IXMLDOMDocumentPtr doc_ptr, int il, MSXML2::IXMLDOMElementPtr ePtr);
	bool save(MSXML2::IXMLDOMDocumentPtr doc_ptr, const std::wstring& filename, const CommandLine& cl);
	void write_processing_instruction(MSXML2::IXMLDOMDocumentPtr doc_ptr, BSTR s1, BSTR s2, bool initial=false);
	void xml_declaration(MSXML2::IXMLDOMDocumentPtr doc_ptr);
	void ImageListAttributes(	MSXML2::IXMLDOMDocumentPtr doc_ptr, 
								const CommandLine& cl, 
								MSXML2::IXMLDOMElementPtr ilp, 
								const unsigned int index, 
								const unsigned int max_pages);
};
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
class xsl_image_list : public basic_xmlfile
{
public:
	xsl_image_list();
	virtual ~xsl_image_list();

	virtual bool build(const CommandLine& cl, const ImageFileList& ifl);
private:
	bool internal_css;
	bool no_caption;
	std::wstring banner;
	unsigned int images_per_page;
//functions
	MSXML2::IXMLDOMElementPtr build_preamble();
	void css_declaration(MSXML2::IXMLDOMElementPtr head_ptr);
	void build_root_template(MSXML2::IXMLDOMElementPtr style_sheetPtr);
	void build_html_head(MSXML2::IXMLDOMElementPtr html_ptr);
	void build_html_body(MSXML2::IXMLDOMElementPtr html_ptr);
	void set_html_title(MSXML2::IXMLDOMElementPtr body_ptr);
	void applytemplates(MSXML2::IXMLDOMElementPtr e4ptr);
	void boilerplate(MSXML2::IXMLDOMElementPtr e4ptr);
	void format_list_template(MSXML2::IXMLDOMElementPtr e1ptr);
	void build_image_template(MSXML2::IXMLDOMElementPtr style_sheetPtr);
	void ImageCaption(MSXML2::IXMLDOMElementPtr e1ptr);
	void insert_links(MSXML2::IXMLDOMElementPtr e4ptr);
};
/////////////////////////////////////////////////////////////////////////////



class WebPageBuilder : public basic_xmlfile
{
public:
	WebPageBuilder();
	virtual ~WebPageBuilder();

	virtual bool build(const CommandLine& cl, const ImageFileList& ifl);
private:
//functions	
	bool internal_build(const CommandLine& cl);
	virtual bool save(const std::wstring& filename, const CommandLine& cl);
	bool load(const CommandLine& cl);
//data	
	MSXML2::IXMLDOMDocumentPtr xsl_ptr;
	MSXML2::IXMLDOMDocumentPtr xml_ptr;
	std::wstring xml_file; 
	std::wstring xsl_file; 
	std::wstring html_file; 
	std::wstring html;
	std::wstring css_file; 
	HRESULT hr;
};

#endif // !defined(WRITEXMLFILE__INCLUDED_)
