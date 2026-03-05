// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
#pragma warning (disable : 4793)
#pragma once
#include <Vcclr.h>


// TODO: reference additional headers your program requires here
#pragma managed(push, off)
#include <windows.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <gdiplus.h>
#include "utilities.h"
#include "CommandLine.h"
#include "ImageFileList.h"
#include "ImagePaths.h"
#include "FolderBuilder.h"
#include "ImageCopier.h"
#include "WaterMarker.h"
#include "ThumbCreator.h"
#include "WriteXMLFile.h"
#include "css_file.h"
#include "build_css.h"

extern bool diagnostic;

#pragma managed(pop)
