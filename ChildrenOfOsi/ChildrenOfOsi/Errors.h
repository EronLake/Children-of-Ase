#pragma once

#include <string>
#include "windows.h"

#define DEBUG_BREAK			__asm { int 3 }

#undef assert
#undef ASSERT
#undef ERROR

inline void _error(std::string string, int line, char* file)
{
	char temp[512];
	OutputDebugStringA ("\n//----------------------------------------------------------------------------\n");
	sprintf_s( temp, 512, "// ERROR\n");
	OutputDebugStringA (temp);
	sprintf_s( temp, 512, "// Line %d\n", line);
	OutputDebugStringA (temp);
	sprintf_s( temp, 512, "// File %s\n", file);
	OutputDebugStringA (temp);
	sprintf_s(temp, 512, "// Message: %s\n", string.c_str());
	OutputDebugStringA (temp);
	OutputDebugStringA ("//----------------------------------------------------------------------------\n\n");
	DEBUG_BREAK;
}

inline void _assert(void* cond, std::string string, int line, char* file)
{
	if(!cond)
		_error(string, line, file);
}

inline void _assert(bool cond, std::string string, int line, char* file)
{
	if(!cond)
		_error(string, line, file);
}

inline void _assert(bool cond)
{
	if(!cond)
		_error("General assertion", 0, "");
}

#ifdef _DEBUG
#define ASSERT(COND, MEX)		(_assert(COND, MEX, __LINE__, __FILE__))
#define ERROR(MEX)				(_error(MEX, __LINE__, __FILE__))
#else
#define ASSERT(COND, MEX)
#define ERROR(MEX)
#endif
