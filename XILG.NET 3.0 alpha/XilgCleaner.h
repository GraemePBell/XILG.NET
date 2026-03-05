#pragma once
#include "stdafx.h"

class XilgCleaner
{
private:
	CommandLine& cl;
public:
	XilgCleaner(CommandLine& parameters) : cl(parameters) {}
	~XilgCleaner(void);
	void CleanUp();
};
