#include "stdafx.h"
#include "LocalisedNames.h"

using namespace System;

namespace LocalisedNames {

LocalNames::LocalNames()
{
    String^ userroot = "HKEY_CURRENT_USER";
    String^ subkey = "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders";
    String^ keyname = String::Concat(userroot, L"\\", subkey);

	String^ temp_desktop = safe_cast<String^>(Registry::GetValue(keyname,L"Desktop",L"\\Desktop"));
	String^ temp_my_documents = safe_cast<String^>(Registry::GetValue(keyname,L"Personal",L"\\My Documents"));
	String^ temp_my_pictures = safe_cast<String^>(Registry::GetValue(keyname,L"My Pictures", L"\\My Pictures"));

    subkey = "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Zones\\0";
    keyname = String::Concat(userroot, L"\\", subkey);

	String^ temp_my_computer = safe_cast<String^>(Registry::GetValue(keyname,L"DisplayName",L"\\My Computer"));

    userroot = "HKEY_CLASSES_ROOT";
    subkey = "\\CLSID\\{208D2C60-3AEA-1069-A2D7-08002B30309D}";
    keyname = String::Concat(userroot, L"\\", subkey);

	String^ temp_my_nethood = safe_cast<String^>(Registry::GetValue(keyname,L"default",L"\\My Network Places"));


	desktop = temp_desktop->Substring((temp_desktop->LastIndexOf(L'\\'))+1);
	my_documents = temp_my_documents->Substring((temp_my_documents->LastIndexOf(L'\\'))+1);
	my_pictures = temp_my_pictures->Substring((temp_my_pictures->LastIndexOf(L'\\'))+1);
	my_computer = temp_my_computer->Substring((temp_my_computer->LastIndexOf(L'\\'))+1);
	my_nethood = temp_my_nethood->Substring((temp_my_nethood->LastIndexOf(L'\\'))+1);
}


void LocalNames::Desktop(String^ d)
{
	desktop = d;
}

void LocalNames::MyDocuments(String^ md)
{
	my_documents = md;
}
void LocalNames::MyPictures(String^ mp)
{
	my_pictures = mp;
}

void LocalNames::MyComputer(String^ mc)
{
	my_computer = mc;
}

void LocalNames::MyNetHood(String^ mn)
{
	my_nethood = mn;
}

String^ LocalNames::Desktop()
{
	return desktop;
}

String^ LocalNames::MyDocuments()
{
	return my_documents;
}

String^ LocalNames::MyPictures()
{
	return my_pictures;
}

String^ LocalNames::MyComputer()
{
	return my_computer;
}

String^ LocalNames::MyNetHood()
{
	return my_nethood;
}

}