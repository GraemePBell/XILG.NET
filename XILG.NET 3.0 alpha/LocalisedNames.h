#pragma once


using namespace System;
using namespace Microsoft::Win32;

namespace LocalisedNames {

public ref class LocalNames 
{
public:
	LocalNames();
    virtual ~LocalNames() {};

	String^ Desktop() ;
	String^ MyDocuments() ;
	String^ MyPictures() ;
	String^ MyComputer() ;
	String^ MyNetHood() ;

private:

	void Desktop(String^ d);
	void MyDocuments(String^ md);
	void MyPictures(String^ mp);
	void MyComputer(String^ mc);
	void MyNetHood(String^ mn);

	String^ desktop;
	String^ my_computer;
	String^ my_documents;
	String^ my_pictures;
	String^ my_nethood;

};

}
