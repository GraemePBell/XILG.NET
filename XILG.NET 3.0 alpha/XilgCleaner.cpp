#include "StdAfx.h"

XilgCleaner::~XilgCleaner(void)
{
}

void XilgCleaner::CleanUp()
{
//	SHFILEOPSTRUCT lpFileOp;
//	wchar_t buffer[MAX_PATH+1];
//	SecureZeroMemory(buffer,sizeof(wchar_t)*(MAX_PATH+1));
//	std::wstring temp = cl.OutputPath();
//	std::wstring::size_type p = temp.find_last_of(L"\\");
//	temp.erase(p);
//	temp.copy(buffer,temp.length());
//
//	/*
//    LPCTSTR pFrom;
//    LPCTSTR pTo;
//    FILEOP_FLAGS fFlags;
//    BOOL fAnyOperationsAborted;
//    LPVOID hNameMappings;
//    LPCTSTR lpszProgressTitle;
//*/
//	lpFileOp.hwnd = NULL;
//	lpFileOp.wFunc = FO_DELETE;
//	lpFileOp.pFrom = buffer;
//	lpFileOp.pTo = NULL;
//	lpFileOp.fFlags = FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT | FOF_NO_UI;
//
//	::SHFileOperation(&lpFileOp);
}

